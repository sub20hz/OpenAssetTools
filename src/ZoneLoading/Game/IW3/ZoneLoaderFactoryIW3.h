#pragma once

#include "Loading/IZoneLoaderFactory.h"
#include <string>

namespace IW3
{
    class ZoneLoaderFactory final : public IZoneLoaderFactory
    {
        class Impl;

    public:
        ZoneLoader* CreateLoaderForHeader(ZoneHeader& header, std::string& fileName) override;
    };
}
