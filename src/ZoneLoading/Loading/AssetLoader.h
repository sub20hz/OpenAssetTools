#pragma once
#include "ContentLoader.h"
#include "IZoneScriptStringProvider.h"
#include "Zone/XAssetDependency.h"

class AssetLoader : public ContentLoader
{
    asset_type_t m_asset_type;

    std::vector<std::string> m_used_script_strings;

    std::vector<XAssetDependency> m_dependencies;

protected:
    IZoneScriptStringProvider* m_script_string_provider;

    scr_string_t* varScriptString;

    AssetLoader(asset_type_t assetType, IZoneScriptStringProvider* scriptStringProvider, Zone* zone, IZoneInputStream* stream);
    
    void AddDependency(asset_type_t type, std::string& name);

    scr_string_t UseScriptString(scr_string_t scrString);
    void LoadScriptStringArray(bool atStreamStart, size_t count);

    void* LinkAsset(std::string name, void* asset);
};
