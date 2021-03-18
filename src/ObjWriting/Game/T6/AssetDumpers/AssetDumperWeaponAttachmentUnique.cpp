#include "AssetDumperWeaponAttachmentUnique.h"

#include <cassert>
#include <sstream>
#include <type_traits>
#include <cstring>

#include "Game/T6/CommonT6.h"
#include "Game/T6/InfoStringT6.h"

using namespace T6;

cspField_t AssetDumperWeaponAttachmentUnique::attachment_unique_fields[]
{
    {"attachmentType", offsetof(WeaponAttachmentUniqueFull, attachment.attachmentType), AUFT_ATTACHMENTTYPE},
    {"locNone", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_NONE]), CSPFT_FLOAT},
    {"locHelmet", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_HELMET]), CSPFT_FLOAT},
    {"locHead", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_HEAD]), CSPFT_FLOAT},
    {"locNeck", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_NECK]), CSPFT_FLOAT},
    {"locTorsoUpper", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_TORSO_UPR]), CSPFT_FLOAT},
    {"locTorsoMid", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_TORSO_MID]), CSPFT_FLOAT},
    {"locTorsoLower", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_TORSO_LWR]), CSPFT_FLOAT},
    {"locRightArmUpper", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_R_ARM_UPR]), CSPFT_FLOAT},
    {"locRightArmLower", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_R_ARM_LWR]), CSPFT_FLOAT},
    {"locRightHand", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_R_HAND]), CSPFT_FLOAT},
    {"locLeftArmUpper", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_L_ARM_UPR]), CSPFT_FLOAT},
    {"locLeftArmLower", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_L_ARM_LWR]), CSPFT_FLOAT},
    {"locLeftHand", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_L_HAND]), CSPFT_FLOAT},
    {"locRightLegUpper", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_R_LEG_UPR]), CSPFT_FLOAT},
    {"locRightLegLower", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_R_LEG_LWR]), CSPFT_FLOAT},
    {"locRightFoot", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_R_FOOT]), CSPFT_FLOAT},
    {"locLeftLegUpper", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_L_LEG_UPR]), CSPFT_FLOAT},
    {"locLeftLegLower", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_L_LEG_LWR]), CSPFT_FLOAT},
    {"locLeftFoot", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_L_FOOT]), CSPFT_FLOAT},
    {"locGun", offsetof(WeaponAttachmentUniqueFull, locationDamageMultipliers[HITLOC_GUN]), CSPFT_FLOAT},
    {"viewModel", offsetof(WeaponAttachmentUniqueFull, attachment.viewModel), CSPFT_XMODEL},
    {"viewModelAdditional", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelAdditional), CSPFT_XMODEL},
    {"viewModelADS", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelADS), CSPFT_XMODEL},
    {"worldModel", offsetof(WeaponAttachmentUniqueFull, attachment.worldModel), CSPFT_XMODEL},
    {"worldModelAdditional", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelAdditional), CSPFT_XMODEL},
    {"viewModelTag", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelTag), CSPFT_STRING},
    {"worldModelTag", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelTag), CSPFT_STRING},
    {"viewModelOffsetX", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelOffsets.x), CSPFT_FLOAT},
    {"viewModelOffsetY", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelOffsets.y), CSPFT_FLOAT},
    {"viewModelOffsetZ", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelOffsets.z), CSPFT_FLOAT},
    {"viewModelOffsetPitch", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelRotations.x), CSPFT_FLOAT},
    {"viewModelOffsetYaw", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelRotations.y), CSPFT_FLOAT},
    {"viewModelOffsetRoll", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelRotations.z), CSPFT_FLOAT},
    {"worldModelOffsetX", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelOffsets.x), CSPFT_FLOAT},
    {"worldModelOffsetY", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelOffsets.y), CSPFT_FLOAT},
    {"worldModelOffsetZ", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelOffsets.z), CSPFT_FLOAT},
    {"worldModelOffsetPitch", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelRotations.x), CSPFT_FLOAT},
    {"worldModelOffsetYaw", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelRotations.y), CSPFT_FLOAT},
    {"worldModelOffsetRoll", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelRotations.z), CSPFT_FLOAT},
    {"viewModelAddOffsetX", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelAddOffsets.x), CSPFT_FLOAT},
    {"viewModelAddOffsetY", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelAddOffsets.y), CSPFT_FLOAT},
    {"viewModelAddOffsetZ", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelAddOffsets.z), CSPFT_FLOAT},
    {"viewModelAddOffsetPitch", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelAddRotations.x), CSPFT_FLOAT},
    {"viewModelAddOffsetYaw", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelAddRotations.y), CSPFT_FLOAT},
    {"viewModelAddOffsetRoll", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelAddRotations.z), CSPFT_FLOAT},
    {"worldModelAddOffsetX", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelAddOffsets.x), CSPFT_FLOAT},
    {"worldModelAddOffsetY", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelAddOffsets.y), CSPFT_FLOAT},
    {"worldModelAddOffsetZ", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelAddOffsets.z), CSPFT_FLOAT},
    {"worldModelAddOffsetPitch", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelAddRotations.x), CSPFT_FLOAT},
    {"worldModelAddOffsetYaw", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelAddRotations.y), CSPFT_FLOAT},
    {"worldModelAddOffsetRoll", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelAddRotations.z), CSPFT_FLOAT},
    {"hideTags", offsetof(WeaponAttachmentUniqueFull, hideTags), AUFT_HIDETAGS},
    {"camo", offsetof(WeaponAttachmentUniqueFull, attachment.weaponCamo), AUFT_CAMO},
    {"disableBaseWeaponAttachment", offsetof(WeaponAttachmentUniqueFull, attachment.disableBaseWeaponAttachment), CSPFT_BOOL},
    {"disableBaseWeaponClip", offsetof(WeaponAttachmentUniqueFull, attachment.disableBaseWeaponClip), CSPFT_BOOL},
    {"overrideBaseWeaponAttachmentOffsets", offsetof(WeaponAttachmentUniqueFull, attachment.overrideBaseWeaponAttachmentOffsets), CSPFT_BOOL},
    {"viewModelOffsetBaseAttachmentX", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelOffsetBaseAttachment.x), CSPFT_FLOAT},
    {"viewModelOffsetBaseAttachmentY", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelOffsetBaseAttachment.y), CSPFT_FLOAT},
    {"viewModelOffsetBaseAttachmentZ", offsetof(WeaponAttachmentUniqueFull, attachment.viewModelOffsetBaseAttachment.z), CSPFT_FLOAT},
    {"worldModelOffsetBaseAttachmentX", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelOffsetBaseAttachment.x), CSPFT_FLOAT},
    {"worldModelOffsetBaseAttachmentY", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelOffsetBaseAttachment.y), CSPFT_FLOAT},
    {"worldModelOffsetBaseAttachmentZ", offsetof(WeaponAttachmentUniqueFull, attachment.worldModelOffsetBaseAttachment.z), CSPFT_FLOAT},
    {"altWeapon", offsetof(WeaponAttachmentUniqueFull, attachment.szAltWeaponName), CSPFT_STRING},
    {"DualWieldWeapon", offsetof(WeaponAttachmentUniqueFull, attachment.szDualWieldWeaponName), CSPFT_STRING},
    {"adsOverlayShader", offsetof(WeaponAttachmentUniqueFull, attachment.overlayMaterial), CSPFT_MATERIAL_STREAM},
    {"adsOverlayShaderLowRes", offsetof(WeaponAttachmentUniqueFull, attachment.overlayMaterialLowRes), CSPFT_MATERIAL_STREAM},
    {"adsOverlayReticle", offsetof(WeaponAttachmentUniqueFull, attachment.overlayReticle), AUFT_OVERLAYRETICLE},
    {"firstRaiseTime", offsetof(WeaponAttachmentUniqueFull, attachment.iFirstRaiseTime), CSPFT_MILLISECONDS},
    {"altRaiseTime", offsetof(WeaponAttachmentUniqueFull, attachment.iAltRaiseTime), CSPFT_MILLISECONDS},
    {"altDropTime", offsetof(WeaponAttachmentUniqueFull, attachment.iAltDropTime), CSPFT_MILLISECONDS},
    {"reloadAmmoAdd", offsetof(WeaponAttachmentUniqueFull, attachment.iReloadAmmoAdd), CSPFT_INT},
    {"reloadStartAdd", offsetof(WeaponAttachmentUniqueFull, attachment.iReloadStartAdd), CSPFT_INT},
    {"segmentedReload", offsetof(WeaponAttachmentUniqueFull, attachment.bSegmentedReload), CSPFT_BOOL},
    {"idleAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_IDLE]), CSPFT_STRING},
    {"idleAnimLeft", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_IDLE_LEFT]), CSPFT_STRING},
    {"emptyIdleAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_EMPTY_IDLE]), CSPFT_STRING},
    {"emptyIdleAnimLeft", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_EMPTY_IDLE_LEFT]), CSPFT_STRING},
    {"fireIntroAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_FIRE_INTRO]), CSPFT_STRING},
    {"fireAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_FIRE]), CSPFT_STRING},
    {"fireAnimLeft", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_FIRE_LEFT]), CSPFT_STRING},
    {"holdFireAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_HOLD_FIRE]), CSPFT_STRING},
    {"lastShotAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_LASTSHOT]), CSPFT_STRING},
    {"lastShotAnimLeft", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_LASTSHOT_LEFT]), CSPFT_STRING},
    {"flourishAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_FINALSHOT]), CSPFT_STRING},
    {"flourishAnimLeft", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_FINALSHOT_LEFT]), CSPFT_STRING},
    {"detonateAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DETONATE]), CSPFT_STRING},
    {"rechamberAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RECHAMBER]), CSPFT_STRING},
    {"meleeAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MELEE]), CSPFT_STRING},
    {"meleeAnimEmpty", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MELEE_EMPTY]), CSPFT_STRING},
    {"meleeAnim1", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MELEE1]), CSPFT_STRING},
    {"meleeAnim2", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MELEE2]), CSPFT_STRING},
    {"meleeAnim3", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MELEE3]), CSPFT_STRING},
    {"meleeChargeAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MELEE_CHARGE]), CSPFT_STRING},
    {"meleeChargeAnimEmpty", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MELEE_CHARGE_EMPTY]), CSPFT_STRING},
    {"reloadAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD]), CSPFT_STRING},
    {"reloadAnimRight", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_RIGHT]), CSPFT_STRING},
    {"reloadAnimLeft", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_LEFT]), CSPFT_STRING},
    {"reloadEmptyAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_EMPTY]), CSPFT_STRING},
    {"reloadEmptyAnimLeft", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_EMPTY_LEFT]), CSPFT_STRING},
    {"reloadStartAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_START]), CSPFT_STRING},
    {"reloadEndAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_END]), CSPFT_STRING},
    {"reloadQuickAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_QUICK]), CSPFT_STRING},
    {"reloadQuickEmptyAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RELOAD_QUICK_EMPTY]), CSPFT_STRING},
    {"raiseAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_RAISE]), CSPFT_STRING},
    {"dropAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DROP]), CSPFT_STRING},
    {"firstRaiseAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_FIRST_RAISE]), CSPFT_STRING},
    {"altRaiseAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ALT_RAISE]), CSPFT_STRING},
    {"altDropAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ALT_DROP]), CSPFT_STRING},
    {"quickRaiseAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_QUICK_RAISE]), CSPFT_STRING},
    {"quickDropAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_QUICK_DROP]), CSPFT_STRING},
    {"emptyRaiseAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_EMPTY_RAISE]), CSPFT_STRING},
    {"emptyDropAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_EMPTY_DROP]), CSPFT_STRING},
    {"sprintInAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_SPRINT_IN]), CSPFT_STRING},
    {"sprintLoopAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_SPRINT_LOOP]), CSPFT_STRING},
    {"sprintOutAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_SPRINT_OUT]), CSPFT_STRING},
    {"sprintInEmptyAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_SPRINT_EMPTY_IN]), CSPFT_STRING},
    {"sprintLoopEmptyAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_SPRINT_EMPTY_LOOP]), CSPFT_STRING},
    {"sprintOutEmptyAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_SPRINT_EMPTY_OUT]), CSPFT_STRING},
    {"lowReadyInAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_LOWREADY_IN]), CSPFT_STRING},
    {"lowReadyLoopAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_LOWREADY_LOOP]), CSPFT_STRING},
    {"lowReadyOutAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_LOWREADY_OUT]), CSPFT_STRING},
    {"contFireInAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CONT_FIRE_IN]), CSPFT_STRING},
    {"contFireLoopAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CONT_FIRE_LOOP]), CSPFT_STRING},
    {"contFireOutAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CONT_FIRE_OUT]), CSPFT_STRING},
    {"crawlInAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_IN]), CSPFT_STRING},
    {"crawlForwardAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_FORWARD]), CSPFT_STRING},
    {"crawlBackAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_BACK]), CSPFT_STRING},
    {"crawlRightAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_RIGHT]), CSPFT_STRING},
    {"crawlLeftAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_LEFT]), CSPFT_STRING},
    {"crawlOutAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_OUT]), CSPFT_STRING},
    {"crawlEmptyInAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_EMPTY_IN]), CSPFT_STRING},
    {"crawlEmptyForwardAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_EMPTY_FORWARD]), CSPFT_STRING},
    {"crawlEmptyBackAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_EMPTY_BACK]), CSPFT_STRING},
    {"crawlEmptyRightAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_EMPTY_RIGHT]), CSPFT_STRING},
    {"crawlEmptyLeftAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_EMPTY_LEFT]), CSPFT_STRING},
    {"crawlEmptyOutAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CRAWL_EMPTY_OUT]), CSPFT_STRING},
    {"deployAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DEPLOY]), CSPFT_STRING},
    {"breakdownAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_BREAKDOWN]), CSPFT_STRING},
    {"nightVisionWearAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_NIGHTVISION_WEAR]), CSPFT_STRING},
    {"nightVisionRemoveAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_NIGHTVISION_REMOVE]), CSPFT_STRING},
    {"adsFireAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ADS_FIRE]), CSPFT_STRING},
    {"adsLastShotAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ADS_LASTSHOT]), CSPFT_STRING},
    {"adsRechamberAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ADS_RECHAMBER]), CSPFT_STRING},
    {"adsUpAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ADS_UP]), CSPFT_STRING},
    {"adsDownAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ADS_DOWN]), CSPFT_STRING},
    {"adsUpOtherScopeAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ADS_UP_OTHER_SCOPE]), CSPFT_STRING},
    {"adsFireIntroAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_ADS_FIRE_INTRO]), CSPFT_STRING},
    {"dtp_in", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DTP_IN]), CSPFT_STRING},
    {"dtp_loop", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DTP_LOOP]), CSPFT_STRING},
    {"dtp_out", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DTP_OUT]), CSPFT_STRING},
    {"dtp_empty_in", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DTP_EMPTY_IN]), CSPFT_STRING},
    {"dtp_empty_loop", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DTP_EMPTY_LOOP]), CSPFT_STRING},
    {"dtp_empty_out", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_DTP_EMPTY_OUT]), CSPFT_STRING},
    {"slide_in", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_SLIDE_IN]), CSPFT_STRING},
    {"mantleAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_MANTLE]), CSPFT_STRING},
    {"sprintCameraAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CAMERA_SPRINT_LOOP]), CSPFT_STRING},
    {"dtpInCameraAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CAMERA_DTP_IN]), CSPFT_STRING},
    {"dtpLoopCameraAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CAMERA_DTP_LOOP]), CSPFT_STRING},
    {"dtpOutCameraAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CAMERA_DTP_OUT]), CSPFT_STRING},
    {"mantleCameraAnim", offsetof(WeaponAttachmentUniqueFull, szXAnims[WEAP_ANIM_CAMERA_MANTLE]), CSPFT_STRING},
    {"fireSound", offsetof(WeaponAttachmentUniqueFull, attachment.fireSound), CSPFT_STRING},
    {"fireSoundPlayer", offsetof(WeaponAttachmentUniqueFull, attachment.fireSoundPlayer), CSPFT_STRING},
    {"loopFireSound", offsetof(WeaponAttachmentUniqueFull, attachment.fireLoopSound), CSPFT_STRING},
    {"loopFireSoundPlayer", offsetof(WeaponAttachmentUniqueFull, attachment.fireLoopSoundPlayer), CSPFT_STRING},
    {"loopFireEndSound", offsetof(WeaponAttachmentUniqueFull, attachment.fireLoopEndSound), CSPFT_STRING},
    {"loopFireEndSoundPlayer", offsetof(WeaponAttachmentUniqueFull, attachment.fireLoopEndSoundPlayer), CSPFT_STRING},
    {"startFireSound", offsetof(WeaponAttachmentUniqueFull, attachment.fireStartSound), CSPFT_STRING},
    {"stopFireSound", offsetof(WeaponAttachmentUniqueFull, attachment.fireStopSound), CSPFT_STRING},
    {"startFireSoundPlayer", offsetof(WeaponAttachmentUniqueFull, attachment.fireStartSoundPlayer), CSPFT_STRING},
    {"stopFireSoundPlayer", offsetof(WeaponAttachmentUniqueFull, attachment.fireStopSoundPlayer), CSPFT_STRING},
    {"lastShotSound", offsetof(WeaponAttachmentUniqueFull, attachment.fireLastSound), CSPFT_STRING},
    {"lastShotSoundPlayer", offsetof(WeaponAttachmentUniqueFull, attachment.fireLastSoundPlayer), CSPFT_STRING},
    {"killcamStartFireSound", offsetof(WeaponAttachmentUniqueFull, attachment.fireKillcamSound), CSPFT_STRING},
    {"killcamStartFireSoundPlayer", offsetof(WeaponAttachmentUniqueFull, attachment.fireKillcamSoundPlayer), CSPFT_STRING},
    {"viewFlashEffect", offsetof(WeaponAttachmentUniqueFull, attachment.viewFlashEffect), CSPFT_FX},
    {"worldFlashEffect", offsetof(WeaponAttachmentUniqueFull, attachment.worldFlashEffect), CSPFT_FX},
    {"tracerType", offsetof(WeaponAttachmentUniqueFull, attachment.tracerType), CSPFT_TRACER},
    {"enemyTracerType", offsetof(WeaponAttachmentUniqueFull, attachment.enemyTracerType), CSPFT_TRACER},
    {"adsDofStart", offsetof(WeaponAttachmentUniqueFull, attachment.adsDofStart), CSPFT_FLOAT},
    {"adsDofEnd", offsetof(WeaponAttachmentUniqueFull, attachment.adsDofEnd), CSPFT_FLOAT},
    {"overrideLeftHandIK", offsetof(WeaponAttachmentUniqueFull, attachment.bOverrideLeftHandIK), CSPFT_BOOL},
    {"overrideLeftHandProneIK", offsetof(WeaponAttachmentUniqueFull, attachment.bOverrideLeftHandProneIK), CSPFT_BOOL},
    {"ikLeftHandOffsetF", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandOffset.x), CSPFT_FLOAT},
    {"ikLeftHandOffsetR", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandOffset.y), CSPFT_FLOAT},
    {"ikLeftHandOffsetU", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandOffset.z), CSPFT_FLOAT},
    {"ikLeftHandRotationP", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandRotation.x), CSPFT_FLOAT},
    {"ikLeftHandRotationY", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandRotation.y), CSPFT_FLOAT},
    {"ikLeftHandRotationR", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandRotation.z), CSPFT_FLOAT},
    {"ikLeftHandProneOffsetF", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandProneOffset.x), CSPFT_FLOAT},
    {"ikLeftHandProneOffsetR", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandProneOffset.y), CSPFT_FLOAT},
    {"ikLeftHandProneOffsetU", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandProneOffset.z), CSPFT_FLOAT},
    {"ikLeftHandProneRotationP", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandProneRotation.x), CSPFT_FLOAT},
    {"ikLeftHandProneRotationY", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandProneRotation.y), CSPFT_FLOAT},
    {"ikLeftHandProneRotationR", offsetof(WeaponAttachmentUniqueFull, attachment.ikLeftHandProneRotation.z), CSPFT_FLOAT},
    {"customFloat0", offsetof(WeaponAttachmentUniqueFull, attachment.customFloat0), CSPFT_FLOAT},
    {"customFloat1", offsetof(WeaponAttachmentUniqueFull, attachment.customFloat1), CSPFT_FLOAT},
    {"customFloat2", offsetof(WeaponAttachmentUniqueFull, attachment.customFloat2), CSPFT_FLOAT},
    {"customBool0", offsetof(WeaponAttachmentUniqueFull, attachment.customBool0), CSPFT_BOOL},
    {"customBool1", offsetof(WeaponAttachmentUniqueFull, attachment.customBool1), CSPFT_BOOL},
    {"customBool2", offsetof(WeaponAttachmentUniqueFull, attachment.customBool2), CSPFT_BOOL}
};

namespace T6
{
    class InfoStringFromWeaponAttachmentUniqueConverter final : public InfoStringFromStructConverter
    {
    protected:
        void FillFromExtensionField(const cspField_t& field) override
        {
            switch (static_cast<attachmentUniqueFieldType_t>(field.iFieldType))
            {
            case AUFT_ATTACHMENTTYPE:
                FillFromEnumInt(std::string(field.szName), field.iOffset, szAttachmentTypeNames, std::extent<decltype(szAttachmentTypeNames)>::value);
                break;

            case AUFT_HIDETAGS:
                {
                    const auto* hideTags = reinterpret_cast<scr_string_t*>(reinterpret_cast<uintptr_t>(m_structure) + field.iOffset);
                    std::stringstream ss;
                    auto first = true;

                    for (auto i = 0u; i < std::extent<decltype(WeaponFullDef::hideTags)>::value; i++)
                    {
                        const auto& str = m_get_scr_string(hideTags[i]);
                        if (!str.empty())
                        {
                            if (!first)
                                ss << "\n";
                            else
                                first = false;

                            ss << str;
                        }
                    }

                    m_info_string.SetValueForKey(std::string(field.szName), ss.str());
                    break;
                }

            case AUFT_OVERLAYRETICLE:
                FillFromEnumInt(std::string(field.szName), field.iOffset, szWeapOverlayReticleNames, std::extent<decltype(szWeapOverlayReticleNames)>::value);
                break;

            case AUFT_CAMO:
                {
                    const auto* camo = *reinterpret_cast<WeaponCamo**>(reinterpret_cast<uintptr_t>(m_structure) + field
                        .iOffset);

                    if (camo)
                        m_info_string.SetValueForKey(std::string(field.szName), std::string(AssetName(camo->name)));
                    else
                        m_info_string.SetValueForKey(std::string(field.szName), "");
                    break;
                }

            default:
                assert(false);
                break;
            }
        }

    public:
        InfoStringFromWeaponAttachmentUniqueConverter(const WeaponAttachmentUniqueFull* structure, const cspField_t* fields, const size_t fieldCount,
                                                      std::function<std::string(scr_string_t)> scriptStringValueCallback)
            : InfoStringFromStructConverter(structure, fields, fieldCount, std::move(scriptStringValueCallback))
        {
        }
    };
}

void AssetDumperWeaponAttachmentUnique::CopyToFullDef(const WeaponAttachmentUnique* attachment, WeaponAttachmentUniqueFull* fullDef)
{
    fullDef->attachment = *attachment;

    if (attachment->szXAnims)
    {
        assert(sizeof(WeaponAttachmentUniqueFull::szXAnims) >= sizeof(void*) * NUM_WEAP_ANIMS);
        memcpy(fullDef->szXAnims, attachment->szXAnims, sizeof(void*) * NUM_WEAP_ANIMS);
        fullDef->attachment.szXAnims = fullDef->szXAnims;
    }

    if (attachment->hideTags)
    {
        assert(sizeof(WeaponAttachmentUniqueFull::hideTags) >= sizeof(scr_string_t) * std::extent<decltype(WeaponAttachmentUniqueFull::hideTags)>::value);
        memcpy(fullDef->hideTags, attachment->hideTags, sizeof(scr_string_t) * std::extent<decltype(WeaponAttachmentUniqueFull::hideTags)>::value);
        fullDef->attachment.hideTags = fullDef->hideTags;
    }

    if (attachment->locationDamageMultipliers)
    {
        assert(sizeof(WeaponAttachmentUniqueFull::locationDamageMultipliers) >= sizeof(float) * HITLOC_NUM);
        memcpy(fullDef->locationDamageMultipliers, attachment->locationDamageMultipliers, sizeof(float) * HITLOC_NUM);
        fullDef->attachment.locationDamageMultipliers = fullDef->locationDamageMultipliers;
    }
}

InfoString AssetDumperWeaponAttachmentUnique::CreateInfoString(XAssetInfo<WeaponAttachmentUnique>* asset)
{
    const auto fullDef = std::make_unique<WeaponAttachmentUniqueFull>();
    memset(fullDef.get(), 0, sizeof(WeaponAttachmentUniqueFull));
    CopyToFullDef(asset->Asset(), fullDef.get());

    InfoStringFromWeaponAttachmentUniqueConverter converter(
        fullDef.get(), attachment_unique_fields, std::extent<decltype(attachment_unique_fields)>::value,
        [asset](const scr_string_t scrStr) -> std::string
        {
            assert(scrStr < asset->m_zone->m_script_strings.Count());
            if (scrStr >= asset->m_zone->m_script_strings.Count())
                return "";

            return asset->m_zone->m_script_strings[scrStr];
        });

    return converter.Convert();
}

bool AssetDumperWeaponAttachmentUnique::ShouldDump(XAssetInfo<WeaponAttachmentUnique>* asset)
{
    return true;
}

bool AssetDumperWeaponAttachmentUnique::CanDumpAsRaw()
{
    return true;
}

bool AssetDumperWeaponAttachmentUnique::CanDumpAsGdtEntry()
{
    return true;
}

std::string AssetDumperWeaponAttachmentUnique::GetFileNameForAsset(Zone* zone, XAssetInfo<WeaponAttachmentUnique>* asset)
{
    return "attachmentunique/" + asset->m_name;
}

GdtEntry AssetDumperWeaponAttachmentUnique::DumpGdtEntry(AssetDumpingContext& context, XAssetInfo<WeaponAttachmentUnique>* asset)
{
    const auto infoString = CreateInfoString(asset);
    GdtEntry gdtEntry(asset->m_name, GDF_NAME);
    infoString.ToGdtProperties(FILE_TYPE_STR, gdtEntry);

    return gdtEntry;
}

void AssetDumperWeaponAttachmentUnique::DumpRaw(AssetDumpingContext& context, XAssetInfo<WeaponAttachmentUnique>* asset, std::ostream& stream)
{
    const auto infoString = CreateInfoString(asset);
    const auto stringValue = infoString.ToString(FILE_TYPE_STR);
    stream.write(stringValue.c_str(), stringValue.size());
}
