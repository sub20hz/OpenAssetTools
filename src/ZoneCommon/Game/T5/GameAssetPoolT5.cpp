#include "GameAssetPoolT5.h"

#include <cassert>
#include <type_traits>

#include "Pool/AssetPoolStatic.h"
#include "Pool/AssetPoolDynamic.h"

using namespace T5;

const char* GameAssetPoolT5::ASSET_TYPE_NAMES[]
{
    "xmodelpieces",
    "physpreset",
    "physconstraints",
    "destructibledef",
    "xanim",
    "xmodel",
    "material",
    "techniqueset",
    "image",
    "soundbank",
    "soundpatch",
    "clipmap",
    "clipmap",
    "comworld",
    "gameworldsp",
    "gameworldmp",
    "mapents",
    "gfxworld",
    "gfxlightdef",
    "uimap",
    "font",
    "menulist",
    "menu",
    "localize",
    "weapon",
    "weapondef",
    "weaponvariant",
    "snddriverglobals",
    "fx",
    "fximpacttable",
    "aitype",
    "mptype",
    "mpbody",
    "mphead",
    "character",
    "xmodelalias",
    "rawfile",
    "stringtable",
    "packindex",
    "xglobals",
    "ddl",
    "glasses",
    "emblemset"
};

GameAssetPoolT5::GameAssetPoolT5(Zone* zone, const int priority)
    : ZoneAssetPools(zone),
    m_priority(priority)
{
    assert(std::extent<decltype(ASSET_TYPE_NAMES)>::value == ASSET_TYPE_COUNT);
}

void GameAssetPoolT5::InitPoolStatic(const asset_type_t type, const size_t capacity)
{
#define CASE_INIT_POOL_STATIC(assetType, poolName, poolType) \
    case assetType: \
    { \
        if((poolName) == nullptr && capacity > 0)  \
        { \
            (poolName) = std::make_unique<AssetPoolStatic<poolType>>(capacity, m_priority, (assetType)); \
        } \
        break; \
    }

    switch (type)
    {
        CASE_INIT_POOL_STATIC(ASSET_TYPE_PHYSPRESET, m_phys_preset, PhysPreset);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_PHYSCONSTRAINTS, m_phys_constraints, PhysConstraints);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_DESTRUCTIBLEDEF, m_destructible_def, DestructibleDef);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_XANIMPARTS, m_xanim_parts, XAnimParts);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_XMODEL, m_xmodel, XModel);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_MATERIAL, m_material, Material);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_TECHNIQUE_SET, m_technique_set, MaterialTechniqueSet);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_IMAGE, m_image, GfxImage);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_SOUND, m_sound_bank, SndBank);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_SOUND_PATCH, m_sound_patch, SndPatch);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_CLIPMAP, m_clip_map, clipMap_t);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_CLIPMAP_PVS, m_clip_map, clipMap_t);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_COMWORLD, m_com_world, ComWorld);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_GAMEWORLD_SP, m_game_world_sp, GameWorldSp);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_GAMEWORLD_MP, m_game_world_mp, GameWorldMp);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_MAP_ENTS, m_map_ents, MapEnts);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_GFXWORLD, m_gfx_world, GfxWorld);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_LIGHT_DEF, m_gfx_light_def, GfxLightDef);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_FONT, m_font, Font_s);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_MENULIST, m_menu_list, MenuList);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_MENU, m_menu_def, menuDef_t);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_LOCALIZE_ENTRY, m_localize, LocalizeEntry);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_WEAPON, m_weapon, WeaponVariantDef);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_SNDDRIVER_GLOBALS, m_snd_driver_globals, SndDriverGlobals);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_FX, m_fx, FxEffectDef);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_IMPACT_FX, m_fx_impact_table, FxImpactTable);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_RAWFILE, m_raw_file, RawFile);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_STRINGTABLE, m_string_table, StringTable);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_PACK_INDEX, m_pack_index, PackIndex);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_XGLOBALS, m_xglobals, XGlobals);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_DDL, m_ddl, ddlRoot_t);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_GLASSES, m_glasses, Glasses);
        CASE_INIT_POOL_STATIC(ASSET_TYPE_EMBLEMSET, m_emblem_set, EmblemSet);

    default:
        assert(type >= 0 && type < ASSET_TYPE_COUNT);
        break;
    }

#undef CASE_INIT_POOL_STATIC
}

void GameAssetPoolT5::InitPoolDynamic(const asset_type_t type)
{
#define CASE_INIT_POOL_DYNAMIC(assetType, poolName, poolType) \
    case assetType: \
    { \
        if((poolName) == nullptr) \
        { \
            (poolName) = std::make_unique<AssetPoolDynamic<poolType>>(m_priority, (assetType)); \
        } \
        break; \
    }

    switch (type)
    {
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_PHYSPRESET, m_phys_preset, PhysPreset);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_PHYSCONSTRAINTS, m_phys_constraints, PhysConstraints);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_DESTRUCTIBLEDEF, m_destructible_def, DestructibleDef);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_XANIMPARTS, m_xanim_parts, XAnimParts);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_XMODEL, m_xmodel, XModel);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_MATERIAL, m_material, Material);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_TECHNIQUE_SET, m_technique_set, MaterialTechniqueSet);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_IMAGE, m_image, GfxImage);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_SOUND, m_sound_bank, SndBank);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_SOUND_PATCH, m_sound_patch, SndPatch);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_CLIPMAP, m_clip_map, clipMap_t);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_CLIPMAP_PVS, m_clip_map, clipMap_t);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_COMWORLD, m_com_world, ComWorld);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_GAMEWORLD_SP, m_game_world_sp, GameWorldSp);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_GAMEWORLD_MP, m_game_world_mp, GameWorldMp);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_MAP_ENTS, m_map_ents, MapEnts);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_GFXWORLD, m_gfx_world, GfxWorld);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_LIGHT_DEF, m_gfx_light_def, GfxLightDef);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_FONT, m_font, Font_s);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_MENULIST, m_menu_list, MenuList);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_MENU, m_menu_def, menuDef_t);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_LOCALIZE_ENTRY, m_localize, LocalizeEntry);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_WEAPON, m_weapon, WeaponVariantDef);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_SNDDRIVER_GLOBALS, m_snd_driver_globals, SndDriverGlobals);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_FX, m_fx, FxEffectDef);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_IMPACT_FX, m_fx_impact_table, FxImpactTable);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_RAWFILE, m_raw_file, RawFile);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_STRINGTABLE, m_string_table, StringTable);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_PACK_INDEX, m_pack_index, PackIndex);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_XGLOBALS, m_xglobals, XGlobals);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_DDL, m_ddl, ddlRoot_t);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_GLASSES, m_glasses, Glasses);
        CASE_INIT_POOL_DYNAMIC(ASSET_TYPE_EMBLEMSET, m_emblem_set, EmblemSet);

    default:
        assert(type >= 0 && type < ASSET_TYPE_COUNT);
        break;
    }

#undef CASE_INIT_POOL_STATIC
}

XAssetInfoGeneric* GameAssetPoolT5::AddAssetToPool(asset_type_t type, std::string name, void* asset, std::vector<XAssetInfoGeneric*> dependencies, std::vector<scr_string_t> usedScriptStrings,
    Zone* zone)
{
    XAsset xAsset{};

    xAsset.type = static_cast<XAssetType>(type);
    xAsset.header.data = asset;

#define CASE_ADD_TO_POOL(assetType, poolName, headerName) \
    case assetType: \
    { \
        assert((poolName) != nullptr); \
        return (poolName)->AddAsset(std::move(name), xAsset.header.headerName, zone, std::move(dependencies), std::move(usedScriptStrings)); \
    }

    switch (xAsset.type)
    {
        CASE_ADD_TO_POOL(ASSET_TYPE_PHYSPRESET, m_phys_preset, physPreset);
        CASE_ADD_TO_POOL(ASSET_TYPE_PHYSCONSTRAINTS, m_phys_constraints, physConstraints);
        CASE_ADD_TO_POOL(ASSET_TYPE_DESTRUCTIBLEDEF, m_destructible_def, destructibleDef);
        CASE_ADD_TO_POOL(ASSET_TYPE_XANIMPARTS, m_xanim_parts, parts);
        CASE_ADD_TO_POOL(ASSET_TYPE_XMODEL, m_xmodel, model);
        CASE_ADD_TO_POOL(ASSET_TYPE_MATERIAL, m_material, material);
        CASE_ADD_TO_POOL(ASSET_TYPE_TECHNIQUE_SET, m_technique_set, techniqueSet);
        CASE_ADD_TO_POOL(ASSET_TYPE_IMAGE, m_image, image);
        CASE_ADD_TO_POOL(ASSET_TYPE_SOUND, m_sound_bank, sound);
        CASE_ADD_TO_POOL(ASSET_TYPE_SOUND_PATCH, m_sound_patch, soundPatch);
        CASE_ADD_TO_POOL(ASSET_TYPE_CLIPMAP, m_clip_map, clipMap);
        CASE_ADD_TO_POOL(ASSET_TYPE_CLIPMAP_PVS, m_clip_map, clipMap);
        CASE_ADD_TO_POOL(ASSET_TYPE_COMWORLD, m_com_world, comWorld);
        CASE_ADD_TO_POOL(ASSET_TYPE_GAMEWORLD_SP, m_game_world_sp, gameWorldSp);
        CASE_ADD_TO_POOL(ASSET_TYPE_GAMEWORLD_MP, m_game_world_mp, gameWorldMp);
        CASE_ADD_TO_POOL(ASSET_TYPE_MAP_ENTS, m_map_ents, mapEnts);
        CASE_ADD_TO_POOL(ASSET_TYPE_GFXWORLD, m_gfx_world, gfxWorld);
        CASE_ADD_TO_POOL(ASSET_TYPE_LIGHT_DEF, m_gfx_light_def, lightDef);
        CASE_ADD_TO_POOL(ASSET_TYPE_FONT, m_font, font);
        CASE_ADD_TO_POOL(ASSET_TYPE_MENULIST, m_menu_list, menuList);
        CASE_ADD_TO_POOL(ASSET_TYPE_MENU, m_menu_def, menu);
        CASE_ADD_TO_POOL(ASSET_TYPE_LOCALIZE_ENTRY, m_localize, localize);
        CASE_ADD_TO_POOL(ASSET_TYPE_WEAPON, m_weapon, weapon);
        CASE_ADD_TO_POOL(ASSET_TYPE_SNDDRIVER_GLOBALS, m_snd_driver_globals, sndDriverGlobals);
        CASE_ADD_TO_POOL(ASSET_TYPE_FX, m_fx, fx);
        CASE_ADD_TO_POOL(ASSET_TYPE_IMPACT_FX, m_fx_impact_table, impactFx);
        CASE_ADD_TO_POOL(ASSET_TYPE_RAWFILE, m_raw_file, rawfile);
        CASE_ADD_TO_POOL(ASSET_TYPE_STRINGTABLE, m_string_table, stringTable);
        CASE_ADD_TO_POOL(ASSET_TYPE_PACK_INDEX, m_pack_index, packIndex);
        CASE_ADD_TO_POOL(ASSET_TYPE_XGLOBALS, m_xglobals, xGlobals);
        CASE_ADD_TO_POOL(ASSET_TYPE_DDL, m_ddl, ddlRoot);
        CASE_ADD_TO_POOL(ASSET_TYPE_GLASSES, m_glasses, glasses);
        CASE_ADD_TO_POOL(ASSET_TYPE_EMBLEMSET, m_emblem_set, emblemSet);

    default:
        assert(false);
        break;
    }

    return nullptr;

#undef CASE_ADD_TO_POOL
}

XAssetInfoGeneric* GameAssetPoolT5::GetAsset(const asset_type_t type, std::string name) const
{
#define CASE_GET_ASSET(assetType, poolName) \
    case assetType: \
    { \
        if((poolName) != nullptr) \
            return (poolName)->GetAsset(std::move(name)); \
        break; \
    }

    switch (type)
    {
        CASE_GET_ASSET(ASSET_TYPE_PHYSPRESET, m_phys_preset);
        CASE_GET_ASSET(ASSET_TYPE_PHYSCONSTRAINTS, m_phys_constraints);
        CASE_GET_ASSET(ASSET_TYPE_DESTRUCTIBLEDEF, m_destructible_def);
        CASE_GET_ASSET(ASSET_TYPE_XANIMPARTS, m_xanim_parts);
        CASE_GET_ASSET(ASSET_TYPE_XMODEL, m_xmodel);
        CASE_GET_ASSET(ASSET_TYPE_MATERIAL, m_material);
        CASE_GET_ASSET(ASSET_TYPE_TECHNIQUE_SET, m_technique_set);
        CASE_GET_ASSET(ASSET_TYPE_IMAGE, m_image);
        CASE_GET_ASSET(ASSET_TYPE_SOUND, m_sound_bank);
        CASE_GET_ASSET(ASSET_TYPE_SOUND_PATCH, m_sound_patch);
        CASE_GET_ASSET(ASSET_TYPE_CLIPMAP, m_clip_map);
        CASE_GET_ASSET(ASSET_TYPE_CLIPMAP_PVS, m_clip_map);
        CASE_GET_ASSET(ASSET_TYPE_COMWORLD, m_com_world);
        CASE_GET_ASSET(ASSET_TYPE_GAMEWORLD_SP, m_game_world_sp);
        CASE_GET_ASSET(ASSET_TYPE_GAMEWORLD_MP, m_game_world_mp);
        CASE_GET_ASSET(ASSET_TYPE_MAP_ENTS, m_map_ents);
        CASE_GET_ASSET(ASSET_TYPE_GFXWORLD, m_gfx_world);
        CASE_GET_ASSET(ASSET_TYPE_LIGHT_DEF, m_gfx_light_def);
        CASE_GET_ASSET(ASSET_TYPE_FONT, m_font);
        CASE_GET_ASSET(ASSET_TYPE_MENULIST, m_menu_list);
        CASE_GET_ASSET(ASSET_TYPE_MENU, m_menu_def);
        CASE_GET_ASSET(ASSET_TYPE_LOCALIZE_ENTRY, m_localize);
        CASE_GET_ASSET(ASSET_TYPE_WEAPON, m_weapon);
        CASE_GET_ASSET(ASSET_TYPE_SNDDRIVER_GLOBALS, m_snd_driver_globals);
        CASE_GET_ASSET(ASSET_TYPE_FX, m_fx);
        CASE_GET_ASSET(ASSET_TYPE_IMPACT_FX, m_fx_impact_table);
        CASE_GET_ASSET(ASSET_TYPE_RAWFILE, m_raw_file);
        CASE_GET_ASSET(ASSET_TYPE_STRINGTABLE, m_string_table);
        CASE_GET_ASSET(ASSET_TYPE_PACK_INDEX, m_pack_index);
        CASE_GET_ASSET(ASSET_TYPE_XGLOBALS, m_xglobals);
        CASE_GET_ASSET(ASSET_TYPE_DDL, m_ddl);
        CASE_GET_ASSET(ASSET_TYPE_GLASSES, m_glasses);
        CASE_GET_ASSET(ASSET_TYPE_EMBLEMSET, m_emblem_set);

    default:
        assert(false);
        break;
    }

    return nullptr;

#undef CASE_GET_ASSET
}

const char* GameAssetPoolT5::AssetTypeNameByType(asset_type_t assetType)
{
    if (assetType >= 0 && assetType < static_cast<int>(std::extent<decltype(ASSET_TYPE_NAMES)>::value))
        return ASSET_TYPE_NAMES[assetType];

    return ASSET_TYPE_INVALID;
}

const char* GameAssetPoolT5::GetAssetTypeName(const asset_type_t assetType) const
{
    return AssetTypeNameByType(assetType);
}

asset_type_t GameAssetPoolT5::AssetTypeCount()
{
    return ASSET_TYPE_COUNT;
}

asset_type_t GameAssetPoolT5::GetAssetTypeCount() const
{
    return AssetTypeCount();
}
