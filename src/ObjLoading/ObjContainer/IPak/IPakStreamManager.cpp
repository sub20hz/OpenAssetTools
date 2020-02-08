#include "IPakStreamManager.h"
#include "IPakEntryReadStream.h"
#include "ObjContainer/IPak/IPakTypes.h"
#include <vector>

using namespace ipak_consts;

class IPakStreamManager::Impl final : public IPakStreamManagerActions
{
    static constexpr int CHUNK_BUFFER_COUNT_IDLE_LIMIT = 3;

    class ChunkBuffer
    {
    public:
        IPakEntryReadStream* m_using_stream = nullptr;
        uint8_t m_buffer[IPAK_CHUNK_SIZE * IPAK_CHUNK_COUNT_PER_READ]{};
    };

    class ManagedStream
    {
    public:
        IPakEntryReadStream* m_stream;
        ChunkBuffer* m_chunk_buffer;

        ManagedStream(IPakEntryReadStream* stream, ChunkBuffer* chunkBuffer)
        {
            m_stream = stream;
            m_chunk_buffer = chunkBuffer;
        }
    };

    FileAPI::IFile* m_file;

    std::mutex m_read_mutex;
    std::mutex m_stream_mutex;

    std::vector<ManagedStream> m_open_streams;
    std::vector<ChunkBuffer*> m_chunk_buffers;

public:
    explicit Impl(FileAPI::IFile* file)
    {
        m_file = file;

        m_chunk_buffers.push_back(new ChunkBuffer());
    }

    Impl(const Impl& other) = delete;
    Impl(Impl&& other) noexcept = delete;

    virtual ~Impl()
    {
        m_stream_mutex.lock();

        for (const auto& openStream : m_open_streams)
        {
            openStream.m_stream->Close();
        }
        m_open_streams.clear();

        m_stream_mutex.unlock();
    }

    Impl& operator=(const Impl& other) = delete;
    Impl& operator=(Impl&& other) noexcept = delete;

    FileAPI::IFile* OpenStream(const int64_t startPosition, const size_t length)
    {
        m_stream_mutex.lock();

        ChunkBuffer* reservedChunkBuffer;
        const auto freeChunkBuffer = std::find_if(m_chunk_buffers.begin(), m_chunk_buffers.end(),
                                               [](ChunkBuffer* chunkBuffer)
                                               {
                                                   return chunkBuffer->m_using_stream == nullptr;
                                               });

        if (freeChunkBuffer == m_chunk_buffers.end())
        {
            reservedChunkBuffer = new ChunkBuffer();
            m_chunk_buffers.push_back(reservedChunkBuffer);
        }
        else
            reservedChunkBuffer = *freeChunkBuffer;

        auto* stream = new IPakEntryReadStream(m_file, this, reservedChunkBuffer->m_buffer, startPosition, length);

        reservedChunkBuffer->m_using_stream = stream;

        m_open_streams.emplace_back(stream, reservedChunkBuffer);

        m_stream_mutex.unlock();

        return stream;
    }

    void StartReading() override
    {
        m_read_mutex.lock();
    }

    void StopReading() override
    {
        m_read_mutex.unlock();
    }

    void CloseStream(FileAPI::IFile* stream) override
    {
        m_stream_mutex.lock();

        const auto openStreamEntry = std::find_if(m_open_streams.begin(), m_open_streams.end(),
                                               [stream](const ManagedStream& managedStream)
                                               {
                                                   return managedStream.m_stream == stream;
                                               });

        if (openStreamEntry != m_open_streams.end())
        {
            auto* chunkBuffer = openStreamEntry->m_chunk_buffer;
            m_open_streams.erase(openStreamEntry);
            chunkBuffer->m_using_stream = nullptr;

            // Only keep previously allocated chunk buffer if we did not get over the limit of idle chunk buffers
            if (m_chunk_buffers.size() > CHUNK_BUFFER_COUNT_IDLE_LIMIT)
            {
                const auto chunkBufferEntry = std::find(m_chunk_buffers.begin(), m_chunk_buffers.end(), chunkBuffer);

                if (chunkBufferEntry != m_chunk_buffers.end())
                {
                    m_chunk_buffers.erase(chunkBufferEntry);
                    delete chunkBuffer;
                }
            }
        }

        m_stream_mutex.unlock();
    }
};

IPakStreamManager::IPakStreamManager(FileAPI::IFile* file)
{
    m_impl = new Impl(file);
}

IPakStreamManager::~IPakStreamManager()
{
    delete m_impl;
    m_impl = nullptr;
}

FileAPI::IFile* IPakStreamManager::OpenStream(const int64_t startPosition, const size_t length) const
{
    return m_impl->OpenStream(startPosition, length);
}
