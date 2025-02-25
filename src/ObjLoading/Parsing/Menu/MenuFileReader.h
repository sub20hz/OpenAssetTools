#pragma once

#include <memory>
#include <string>
#include <vector>

#include "MenuFileParserState.h"
#include "Domain/MenuFeatureLevel.h"
#include "Domain/MenuParsingResult.h"
#include "Parsing/IParserLineStream.h"
#include "MenuAssetZoneState.h"

namespace menu
{
    class MenuFileReader
    {
    public:
        using include_callback_t = std::function<std::unique_ptr<std::istream>(const std::string& filename, const std::string& sourceFile)>;

    private:
        const FeatureLevel m_feature_level;
        const std::string m_file_name;

        IParserLineStream* m_stream;
        std::vector<std::unique_ptr<IParserLineStream>> m_open_streams;

        const MenuAssetZoneState* m_zone_state;
        bool m_permissive_mode;

        bool OpenBaseStream(std::istream& stream, include_callback_t includeCallback);
        void SetupDefinesProxy();
        void SetupStreamProxies();

        bool IsValidEndState(const MenuFileParserState* state) const;
        std::unique_ptr<ParsingResult> CreateParsingResult(MenuFileParserState* state) const;

    public:
        MenuFileReader(std::istream& stream, std::string fileName, FeatureLevel featureLevel);
        MenuFileReader(std::istream& stream, std::string fileName, FeatureLevel featureLevel, include_callback_t includeCallback);

        void IncludeZoneState(const MenuAssetZoneState* zoneState);
        void SetPermissiveMode(bool usePermissiveMode);

        std::unique_ptr<ParsingResult> ReadMenuFile();
    };
}
