#pragma once

#include "Utils/ClassUtils.h"
#include "Zone/Zone.h"
#include "Zone/ZoneTypes.h"
#include "Pool/XAssetInfo.h"
#include "ContentWriterBase.h"

class AssetWriter : public ContentWriterBase
{
protected:
    XAssetInfoGeneric* m_asset;

    scr_string_t* varScriptString;
    scr_string_t* varScriptStringWritten;

    AssetWriter(XAssetInfoGeneric* asset, Zone* zone, IZoneOutputStream* stream);

    _NODISCARD scr_string_t UseScriptString(scr_string_t scrString) const;
    void WriteScriptStringArray(bool atStreamStart, size_t count);
};
