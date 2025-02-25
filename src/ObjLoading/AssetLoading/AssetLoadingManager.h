#pragma once
#include <map>

#include "AssetLoadingContext.h"
#include "IAssetLoader.h"
#include "IAssetLoadingManager.h"

class AssetLoadingManager final : public IAssetLoadingManager
{
    const std::map<asset_type_t, std::unique_ptr<IAssetLoader>>& m_asset_loaders_by_type;
    AssetLoadingContext& m_context;
    XAssetInfoGeneric* m_last_dependency_loaded;

    XAssetInfoGeneric* LoadIgnoredDependency(asset_type_t assetType, const std::string& assetName, IAssetLoader* loader);
    XAssetInfoGeneric* LoadAssetDependency(asset_type_t assetType, const std::string& assetName, IAssetLoader* loader);

    XAssetInfoGeneric* AddAsset(asset_type_t assetType, const std::string& assetName, void* asset, std::vector<XAssetInfoGeneric*> dependencies, std::vector<scr_string_t> usedScriptStrings, Zone* zone);

public:
    AssetLoadingManager(const std::map<asset_type_t, std::unique_ptr<IAssetLoader>>& assetLoadersByType, AssetLoadingContext& context);

    bool LoadAssetFromLoader(asset_type_t assetType, const std::string& assetName);

    _NODISCARD AssetLoadingContext* GetAssetLoadingContext() const override;

    XAssetInfoGeneric* AddAsset(asset_type_t assetType, const std::string& assetName, void* asset, std::vector<XAssetInfoGeneric*> dependencies, std::vector<scr_string_t> usedScriptStrings) override;
    XAssetInfoGeneric* LoadDependency(asset_type_t assetType, const std::string& assetName) override;
};
