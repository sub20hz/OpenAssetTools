#pragma once

#include <memory>
#include <vector>

#include "Utils/ClassUtils.h"
#include "CommonStructuredDataEnum.h"
#include "CommonStructuredDataStruct.h"

class CommonStructuredDataDef
{
public:
    std::vector<std::unique_ptr<CommonStructuredDataEnum>> m_enums;
    std::vector<std::unique_ptr<CommonStructuredDataStruct>> m_structs;
    std::vector<CommonStructuredDataIndexedArray> m_indexed_arrays;
    std::vector<CommonStructuredDataEnumedArray> m_enumed_arrays;

    int m_version;
    size_t m_checksum;
    CommonStructuredDataType m_root_type;
    size_t m_size_in_byte;

    CommonStructuredDataDef();
    explicit CommonStructuredDataDef(int version);

    _NODISCARD uint32_t CalculateChecksum() const;
};
