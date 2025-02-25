#include "AssetLoaderStringTable.h"

#include <cstring>

#include "ObjLoading.h"
#include "Csv/CsvStream.h"
#include "Game/IW5/CommonIW5.h"
#include "Game/IW5/IW5.h"
#include "Pool/GlobalAssetPool.h"

using namespace IW5;

void* AssetLoaderStringTable::CreateEmptyAsset(const std::string& assetName, MemoryManager* memory)
{
    auto* stringTable = memory->Create<StringTable>();
    memset(stringTable, 0, sizeof(StringTable));
    stringTable->name = memory->Dup(assetName.c_str());
    return stringTable;
}

bool AssetLoaderStringTable::CanLoadFromRaw() const
{
    return true;
}

bool AssetLoaderStringTable::LoadFromRaw(const std::string& assetName, ISearchPath* searchPath, MemoryManager* memory, IAssetLoadingManager* manager, Zone* zone) const
{
    const auto file = searchPath->Open(assetName);
    if (!file.IsOpen())
        return false;

    auto* stringTable = memory->Create<StringTable>();
    stringTable->name = memory->Dup(assetName.c_str());

    std::vector<std::vector<std::string>> csvLines;
    std::vector<std::string> currentLine;
    auto maxCols = 0u;
    const CsvInputStream csv(*file.m_stream);

    while (csv.NextRow(currentLine))
    {
        if (currentLine.size() > maxCols)
            maxCols = currentLine.size();
        csvLines.emplace_back(std::move(currentLine));
        currentLine = std::vector<std::string>();
    }

    stringTable->columnCount = static_cast<int>(maxCols);
    stringTable->rowCount = static_cast<int>(csvLines.size());
    const auto cellCount = static_cast<unsigned>(stringTable->rowCount) * static_cast<unsigned>(stringTable->columnCount);

    if (cellCount)
    {
        stringTable->values = static_cast<StringTableCell*>(memory->Alloc(sizeof(StringTableCell) * cellCount));

        for (auto row = 0u; row < csvLines.size(); row++)
        {
            const auto& rowValues = csvLines[row];
            for (auto col = 0u; col < maxCols; col++)
            {
                auto& cell = stringTable->values[row * maxCols + col];
                if (col >= rowValues.size() || rowValues[col].empty())
                    cell.string = "";
                else
                    cell.string = memory->Dup(rowValues[col].c_str());

                cell.hash = Common::StringTable_HashString(cell.string);
            }
        }
    }
    else
    {
        stringTable->values = nullptr;
    }

    manager->AddAsset(ASSET_TYPE_STRINGTABLE, assetName, stringTable);

    return true;
}
