#pragma once

#include <unordered_map>

#include "Utils/ClassUtils.h"
#include "Image/D3DFormat.h"
#include "Utils/MemoryManager.h"
#include "Image/Texture.h"

class Dx9TextureLoader
{
    MemoryManager* m_memory_manager;
    D3DFORMAT m_format;
    TextureType m_type;
    bool m_has_mip_maps;
    size_t m_width;
    size_t m_height;
    size_t m_depth;

    _NODISCARD const ImageFormat* GetFormatForDx9Format() const;

public:
    explicit Dx9TextureLoader(MemoryManager* memoryManager);

    Dx9TextureLoader& Format(D3DFORMAT format);
    Dx9TextureLoader& Type(TextureType textureType);
    Dx9TextureLoader& HasMipMaps(bool hasMipMaps);
    Dx9TextureLoader& Width(size_t width);
    Dx9TextureLoader& Height(size_t height);
    Dx9TextureLoader& Depth(size_t depth);

    Texture* LoadTexture(const void* data);
};
