#include "ObjLoaderT6.h"

#include <sstream>

#include "Game/T6/GameT6.h"
#include "Game/T6/GameAssetPoolT6.h"
#include "ObjContainer/IPak/IPak.h"
#include "ObjLoading.h"
#include "AssetLoaders/AssetLoaderFontIcon.h"
#include "AssetLoaders/AssetLoaderLocalizeEntry.h"
#include "AssetLoaders/AssetLoaderPhysConstraints.h"
#include "AssetLoaders/AssetLoaderPhysPreset.h"
#include "AssetLoaders/AssetLoaderQdb.h"
#include "AssetLoaders/AssetLoaderRawFile.h"
#include "AssetLoaders/AssetLoaderScriptParseTree.h"
#include "AssetLoaders/AssetLoaderSlug.h"
#include "AssetLoaders/AssetLoaderStringTable.h"
#include "AssetLoaders/AssetLoaderTracer.h"
#include "AssetLoaders/AssetLoaderVehicle.h"
#include "AssetLoaders/AssetLoaderWeapon.h"
#include "AssetLoaders/AssetLoaderWeaponAttachment.h"
#include "AssetLoaders/AssetLoaderWeaponAttachmentUnique.h"
#include "AssetLoaders/AssetLoaderZBarrier.h"
#include "AssetLoading/AssetLoadingManager.h"
#include "Image/Texture.h"
#include "Image/IwiLoader.h"
#include "Game/T6/CommonT6.h"
#include "Image/Dx12TextureLoader.h"
#include "Image/IwiTypes.h"

namespace T6
{
    const int ObjLoader::IPAK_READ_HASH = Common::Com_HashKey("ipak_read", 64);
    const int ObjLoader::GLOBAL_HASH = Common::Com_HashKey("GLOBAL", 64);

    ObjLoader::ObjLoader()
    {
#define REGISTER_ASSET_LOADER(t) {auto l = std::make_unique<t>(); m_asset_loaders_by_type[l->GetHandlingAssetType()] = std::move(l);}
#define BASIC_LOADER(assetType, assetClass) BasicAssetLoader<assetType, assetClass>

        REGISTER_ASSET_LOADER(AssetLoaderPhysPreset)
        REGISTER_ASSET_LOADER(AssetLoaderPhysConstraints)
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_DESTRUCTIBLEDEF, DestructibleDef))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_XANIMPARTS, XAnimParts))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_XMODEL, XModel))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_MATERIAL, Material))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_TECHNIQUE_SET, MaterialTechniqueSet))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_IMAGE, GfxImage))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_SOUND, SndBank))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_SOUND_PATCH, SndPatch))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_CLIPMAP, clipMap_t))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_CLIPMAP_PVS, clipMap_t))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_COMWORLD, ComWorld))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_GAMEWORLD_SP, GameWorldSp))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_GAMEWORLD_MP, GameWorldMp))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_MAP_ENTS, MapEnts))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_GFXWORLD, GfxWorld))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_LIGHT_DEF, GfxLightDef))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_FONT, Font_s))
        REGISTER_ASSET_LOADER(AssetLoaderFontIcon)
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_MENULIST, MenuList))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_MENU, menuDef_t))
        REGISTER_ASSET_LOADER(AssetLoaderLocalizeEntry)
        REGISTER_ASSET_LOADER(AssetLoaderWeapon)
        REGISTER_ASSET_LOADER(AssetLoaderWeaponAttachment)
        REGISTER_ASSET_LOADER(AssetLoaderWeaponAttachmentUnique)
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_WEAPON_CAMO, WeaponCamo))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_SNDDRIVER_GLOBALS, SndDriverGlobals))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_FX, FxEffectDef))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_IMPACT_FX, FxImpactTable))
        REGISTER_ASSET_LOADER(AssetLoaderRawFile)
        REGISTER_ASSET_LOADER(AssetLoaderStringTable)
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_LEADERBOARD, LeaderboardDef))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_XGLOBALS, XGlobals))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_DDL, ddlRoot_t))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_GLASSES, Glasses))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_EMBLEMSET, EmblemSet))
        REGISTER_ASSET_LOADER(AssetLoaderScriptParseTree)
        REGISTER_ASSET_LOADER(AssetLoaderVehicle)
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_MEMORYBLOCK, MemoryBlock))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_ADDON_MAP_ENTS, AddonMapEnts))
        REGISTER_ASSET_LOADER(AssetLoaderTracer)
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_SKINNEDVERTS, SkinnedVertsDef))
        REGISTER_ASSET_LOADER(AssetLoaderQdb)
        REGISTER_ASSET_LOADER(AssetLoaderSlug)
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_FOOTSTEP_TABLE, FootstepTableDef))
        REGISTER_ASSET_LOADER(BASIC_LOADER(ASSET_TYPE_FOOTSTEPFX_TABLE, FootstepFXTableDef))
        REGISTER_ASSET_LOADER(AssetLoaderZBarrier)

#undef BASIC_LOADER
#undef REGISTER_ASSET_LOADER
    }

    bool ObjLoader::SupportsZone(Zone* zone) const
    {
        return zone->m_game == &g_GameT6;
    }

    bool ObjLoader::VerifySoundBankChecksum(const SoundBank* soundBank, const SndRuntimeAssetBank& sndRuntimeAssetBank)
    {
        SoundAssetBankChecksum checksum{};
        static_assert(sizeof(SoundAssetBankChecksum::checksumBytes) == sizeof(SndRuntimeAssetBank::linkTimeChecksum));
        for (auto i = 0u; i < sizeof(SoundAssetBankChecksum::checksumBytes); i++)
            checksum.checksumBytes[i] = sndRuntimeAssetBank.linkTimeChecksum[i];

        return soundBank->VerifyChecksum(checksum);
    }

    SoundBank* ObjLoader::LoadSoundBankForZone(ISearchPath* searchPath, const std::string& soundBankFileName, Zone* zone)
    {
        if (ObjLoading::Configuration.Verbose)
            std::cout << "Trying to load sound bank '" << soundBankFileName << "' for zone '" << zone->m_name << "'" << std::endl;

        auto* existingSoundBank = SoundBank::Repository.GetContainerByName(soundBankFileName);
        if (existingSoundBank != nullptr)
        {
            if (ObjLoading::Configuration.Verbose)
                std::cout << "Referencing loaded sound bank '" << soundBankFileName << "'." << std::endl;

            SoundBank::Repository.AddContainerReference(existingSoundBank, zone);
            return existingSoundBank;
        }

        auto file = searchPath->Open(soundBankFileName);
        if (file.IsOpen())
        {
            auto sndBank = std::make_unique<SoundBank>(soundBankFileName, std::move(file.m_stream), file.m_length);
            auto* sndBankPtr = sndBank.get();

            if (!sndBank->Initialize())
            {
                std::cout << "Failed to load sound bank '" << soundBankFileName << "'" << std::endl;
                return nullptr;
            }

            SoundBank::Repository.AddContainer(std::move(sndBank), zone);

            if (ObjLoading::Configuration.Verbose)
                std::cout << "Found and loaded sound bank '" << soundBankFileName << "'" << std::endl;

            return sndBankPtr;
        }

        std::cout << "Failed to load sound bank '" << soundBankFileName << "'" << std::endl;
        return nullptr;
    }

    void ObjLoader::LoadSoundBankFromLinkedInfo(ISearchPath* searchPath, const std::string& soundBankFileName, const SndRuntimeAssetBank* sndBankLinkedInfo, Zone* zone,
                                                std::set<std::string>& loadedBanksForZone, std::stack<std::string>& dependenciesToLoad)
    {
        if (loadedBanksForZone.find(soundBankFileName) == loadedBanksForZone.end())
        {
            auto* soundBank = LoadSoundBankForZone(searchPath, soundBankFileName, zone);

            if (soundBank)
            {
                if (!VerifySoundBankChecksum(soundBank, *sndBankLinkedInfo))
                {
                    std::cout << "Checksum of sound bank does not match link time checksum for '" << soundBankFileName << "'" << std::endl;
                }
                loadedBanksForZone.emplace(soundBankFileName);

                for (const auto& dependency : soundBank->GetDependencies())
                {
                    dependenciesToLoad.emplace(dependency);
                }
            }
        }
    }

    void ObjLoader::LoadSoundBanksFromAsset(ISearchPath* searchPath, const SndBank* sndBank, Zone* zone, std::set<std::string>& loadedBanksForZone)
    {
        std::stack<std::string> dependenciesToLoad;

        if (sndBank->streamAssetBank.zone)
        {
            const auto soundBankFileName = SoundBank::GetFileNameForDefinition(true, sndBank->streamAssetBank.zone, sndBank->streamAssetBank.language);
            LoadSoundBankFromLinkedInfo(searchPath, soundBankFileName, &sndBank->streamAssetBank, zone, loadedBanksForZone, dependenciesToLoad);
        }

        if (sndBank->runtimeAssetLoad && sndBank->loadAssetBank.zone)
        {
            const auto soundBankFileName = SoundBank::GetFileNameForDefinition(false, sndBank->loadAssetBank.zone, sndBank->loadAssetBank.language);
            LoadSoundBankFromLinkedInfo(searchPath, soundBankFileName, &sndBank->loadAssetBank, zone, loadedBanksForZone, dependenciesToLoad);
        }

        while (!dependenciesToLoad.empty())
        {
            auto dependencyFileName = dependenciesToLoad.top();
            dependenciesToLoad.pop();

            if (loadedBanksForZone.find(dependencyFileName) == loadedBanksForZone.end())
            {
                auto* soundBank = LoadSoundBankForZone(searchPath, dependencyFileName, zone);

                if (soundBank)
                {
                    loadedBanksForZone.emplace(dependencyFileName);

                    for (const auto& dependency : soundBank->GetDependencies())
                    {
                        dependenciesToLoad.emplace(dependency);
                    }
                }
            }
        }
    }

    void ObjLoader::LoadIPakForZone(ISearchPath* searchPath, const std::string& ipakName, Zone* zone)
    {
        if (ObjLoading::Configuration.Verbose)
            printf("Trying to load ipak '%s' for zone '%s'\n", ipakName.c_str(), zone->m_name.c_str());

        auto* existingIPak = IPak::Repository.GetContainerByName(ipakName);
        if (existingIPak != nullptr)
        {
            if (ObjLoading::Configuration.Verbose)
                printf("Referencing loaded ipak '%s'.\n", ipakName.c_str());

            IPak::Repository.AddContainerReference(existingIPak, zone);
            return;
        }

        const auto ipakFilename = ipakName + ".ipak";

        auto file = searchPath->Open(ipakFilename);
        if (file.IsOpen())
        {
            auto ipak = std::make_unique<IPak>(ipakFilename, std::move(file.m_stream));

            if (ipak->Initialize())
            {
                IPak::Repository.AddContainer(std::move(ipak), zone);

                if (ObjLoading::Configuration.Verbose)
                    printf("Found and loaded ipak '%s'.\n", ipakFilename.c_str());
            }
            else
            {
                printf("Failed to load ipak '%s'!\n", ipakFilename.c_str());
            }
        }
    }

    bool ObjLoader::IsMpZone(Zone* zone)
    {
        return zone->m_name.compare(0, 3, "mp_") == 0
            || zone->m_name.compare(zone->m_name.length() - 3, 3, "_mp") == 0;
    }

    bool ObjLoader::IsZmZone(Zone* zone)
    {
        return zone->m_name.compare(0, 3, "zm_") == 0
            || zone->m_name.compare(zone->m_name.length() - 3, 3, "_zm") == 0;
    }

    void ObjLoader::LoadCommonIPaks(ISearchPath* searchPath, Zone* zone)
    {
        if (ObjLoading::Configuration.Verbose)
            printf("Loading common ipaks for zone \"%s\"\n", zone->m_name.c_str());

        LoadIPakForZone(searchPath, "base", zone);
        auto languagePrefixes = g_GameT6.GetLanguagePrefixes();
        for (const auto& languagePrefix : languagePrefixes)
        {
            LoadIPakForZone(searchPath, languagePrefix.m_prefix + "base", zone);
        }

        if (IsMpZone(zone))
        {
            if (ObjLoading::Configuration.Verbose)
                printf("Loading multiplayer ipaks for zone \"%s\"\n", zone->m_name.c_str());

            LoadIPakForZone(searchPath, "mp", zone);
            LoadIPakForZone(searchPath, "so", zone);
        }
        else if (IsZmZone(zone))
        {
            if (ObjLoading::Configuration.Verbose)
                printf("Loading zombie ipak for zone \"%s\"\n", zone->m_name.c_str());

            LoadIPakForZone(searchPath, "zm", zone);
        }
        else
        {
            if (ObjLoading::Configuration.Verbose)
                printf("Loading singleplayer ipak for zone \"%s\"\n", zone->m_name.c_str());

            LoadIPakForZone(searchPath, "sp", zone);
        }
    }

    void ObjLoader::LoadReferencedContainersForZone(ISearchPath* searchPath, Zone* zone) const
    {
        auto* assetPoolT6 = dynamic_cast<GameAssetPoolT6*>(zone->m_pools.get());
        const auto zoneNameHash = Common::Com_HashKey(zone->m_name.c_str(), 64);

        LoadCommonIPaks(searchPath, zone);

        if (assetPoolT6->m_key_value_pairs != nullptr)
        {
            for (auto* keyValuePairsEntry : *assetPoolT6->m_key_value_pairs)
            {
                auto* keyValuePairs = keyValuePairsEntry->Asset();
                for (auto variableIndex = 0; variableIndex < keyValuePairs->numVariables; variableIndex++)
                {
                    auto* variable = &keyValuePairs->keyValuePairs[variableIndex];

                    if (variable->namespaceHash == zoneNameHash && variable->keyHash == IPAK_READ_HASH)
                    {
                        LoadIPakForZone(searchPath, variable->value, zone);
                    }
                }
            }
        }

        if (assetPoolT6->m_sound_bank != nullptr)
        {
            std::set<std::string> loadedSoundBanksForZone;

            for (auto* sndBankAssetInfo : *assetPoolT6->m_sound_bank)
            {
                LoadSoundBanksFromAsset(searchPath, sndBankAssetInfo->Asset(), zone, loadedSoundBanksForZone);
            }
        }
    }

    void ObjLoader::UnloadContainersOfZone(Zone* zone) const
    {
        IPak::Repository.RemoveContainerReferences(zone);
    }

    void ObjLoader::LoadImageFromLoadDef(GfxImage* image, Zone* zone)
    {
        const auto* loadDef = image->texture.loadDef;
        Dx12TextureLoader textureLoader(zone->GetMemory());

        textureLoader.Width(image->width).Height(image->height).Depth(image->depth);

        if (loadDef->flags & iwi27::IMG_FLAG_VOLMAP)
            textureLoader.Type(TextureType::T_3D);
        else if (loadDef->flags & iwi27::IMG_FLAG_CUBEMAP)
            textureLoader.Type(TextureType::T_CUBE);
        else
            textureLoader.Type(TextureType::T_2D);

        textureLoader.Format(static_cast<DXGI_FORMAT>(loadDef->format));
        textureLoader.HasMipMaps(!(loadDef->flags & iwi27::IMG_FLAG_NOMIPMAPS));
        Texture* loadedTexture = textureLoader.LoadTexture(image->texture.loadDef->data);

        if (loadedTexture != nullptr)
        {
            image->texture.texture = loadedTexture;
            image->loadedSize = 0;

            const auto textureMipCount = loadedTexture->GetMipMapCount();
            for (auto mipLevel = 0; mipLevel < textureMipCount; mipLevel++)
                image->loadedSize += static_cast<int>(loadedTexture->GetSizeOfMipLevel(mipLevel) * loadedTexture->GetFaceCount());
        }
    }

    void ObjLoader::LoadImageFromIwi(GfxImage* image, ISearchPath* searchPath, Zone* zone)
    {
        Texture* loadedTexture = nullptr;
        IwiLoader loader(zone->GetMemory());

        if (image->streamedPartCount > 0)
        {
            for (auto* ipak : IPak::Repository)
            {
                auto ipakStream = ipak->GetEntryStream(image->hash, image->streamedParts[0].hash);

                if (ipakStream)
                {
                    loadedTexture = loader.LoadIwi(*ipakStream);

                    ipakStream->close();

                    if (loadedTexture != nullptr)
                    {
                        break;
                    }
                }
            }
        }

        if (loadedTexture == nullptr)
        {
            const auto imageFileName = "images/" + std::string(image->name) + ".iwi";

            {
                const auto filePathImage = searchPath->Open(imageFileName);
                if (filePathImage.IsOpen())
                {
                    loadedTexture = loader.LoadIwi(*filePathImage.m_stream);
                }
            }
        }

        if (loadedTexture != nullptr)
        {
            image->texture.texture = loadedTexture;
            image->loadedSize = 0;

            const auto textureMipCount = loadedTexture->GetMipMapCount();
            for (auto mipLevel = 0; mipLevel < textureMipCount; mipLevel++)
                image->loadedSize += loadedTexture->GetSizeOfMipLevel(mipLevel) * loadedTexture->GetFaceCount();
        }
        else
        {
            printf("Could not find data for image \"%s\"\n", image->name);
        }
    }

    void ObjLoader::LoadImageData(ISearchPath* searchPath, Zone* zone)
    {
        auto* assetPoolT6 = dynamic_cast<GameAssetPoolT6*>(zone->m_pools.get());

        if (assetPoolT6 && assetPoolT6->m_image != nullptr)
        {
            for (auto* imageEntry : *assetPoolT6->m_image)
            {
                auto* image = imageEntry->Asset();

                if (image->loadedSize > 0)
                {
                    continue;
                }

                // Do not load linked assets
                if (image->name && image->name[0] == ',')
                {
                    continue;
                }

                if (image->texture.loadDef && image->texture.loadDef->resourceSize > 0)
                {
                    LoadImageFromLoadDef(image, zone);
                }
                else
                {
                    LoadImageFromIwi(image, searchPath, zone);
                }
            }
        }
    }

    void ObjLoader::LoadObjDataForZone(ISearchPath* searchPath, Zone* zone) const
    {
        LoadImageData(searchPath, zone);
    }

    bool ObjLoader::LoadAssetForZone(AssetLoadingContext* context, const asset_type_t assetType, const std::string& assetName) const
    {
        AssetLoadingManager assetLoadingManager(m_asset_loaders_by_type, *context);
        return assetLoadingManager.LoadAssetFromLoader(assetType, assetName);
    }

    void ObjLoader::FinalizeAssetsForZone(AssetLoadingContext* context) const
    {
        for (const auto& [type, loader] : m_asset_loaders_by_type)
            loader->FinalizeAssetsForZone(context);
    }
}
