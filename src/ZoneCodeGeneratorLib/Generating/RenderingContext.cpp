#include "RenderingContext.h"

#include "Domain/Computations/MemberComputations.h"
#include "Domain/Computations/StructureComputations.h"

RenderingUsedType::RenderingUsedType(const DataDefinition* type, StructureInformation* info)
    : m_members_loaded(false),
      m_type(type),
      m_info(info),
      m_is_context_asset(false),
      m_non_runtime_reference_exists(false),
      m_non_embedded_reference_exists(false),
      m_array_reference_exists(false),
      m_pointer_array_reference_exists(false),
      m_pointer_array_reference_is_reusable(false)
{
}

RenderingContext::RenderingContext(std::string game, std::vector<const FastFileBlock*> fastFileBlocks)
    : m_game(std::move(game)),
      m_blocks(std::move(fastFileBlocks)),
      m_asset(nullptr),
      m_has_actions(false),
      m_default_normal_block(nullptr),
      m_default_temp_block(nullptr)
{
    for (const auto* block : m_blocks)
    {
        if (block->m_is_default)
        {
            if (block->m_type == FastFileBlockType::NORMAL && m_default_normal_block == nullptr)
                m_default_normal_block = block;
            else if (block->m_type == FastFileBlockType::TEMP && m_default_temp_block == nullptr)
                m_default_temp_block = block;
        }
    }
}

RenderingUsedType* RenderingContext::GetBaseType(RenderingUsedType* usedType)
{
    if(usedType->m_type->GetType() == DataDefinitionType::TYPEDEF)
    {
        const auto* typedefDefinition = dynamic_cast<const TypedefDefinition*>(usedType->m_type);

        while(typedefDefinition->m_type_declaration->m_type->GetType() == DataDefinitionType::TYPEDEF)
            typedefDefinition = dynamic_cast<const TypedefDefinition*>(typedefDefinition->m_type_declaration->m_type);

        const auto foundUsedType = m_used_types_lookup.find(typedefDefinition);
        if(foundUsedType == m_used_types_lookup.end())
        {
            auto usedTypePtr = std::make_unique<RenderingUsedType>(typedefDefinition->m_type_declaration->m_type, nullptr);
            auto* result = usedTypePtr.get();
            m_used_types_lookup.emplace(std::make_pair(usedTypePtr->m_type, std::move(usedTypePtr)));

            return result;
        }

        return foundUsedType->second.get();
    }

    return nullptr;
}

void RenderingContext::AddMembersToContext(StructureInformation* info)
{
    for(const auto& member : info->m_ordered_members)
    {
        MemberComputations computations(member.get());

        if(computations.ShouldIgnore())
            continue;

        RenderingUsedType* usedType;
        const auto existingUsedType = m_used_types_lookup.find(member->m_member->m_type_declaration->m_type);
        if(existingUsedType == m_used_types_lookup.end())
        {
            auto usedTypePtr = std::make_unique<RenderingUsedType>(member->m_member->m_type_declaration->m_type, member->m_type);
            usedType = usedTypePtr.get();
            m_used_types_lookup.emplace(std::make_pair(usedTypePtr->m_type, std::move(usedTypePtr)));
        }
        else
        {
            usedType = existingUsedType->second.get();
        }

        auto* baseUsedType = GetBaseType(usedType);

        if(!computations.IsInRuntimeBlock())
        {
            usedType->m_non_runtime_reference_exists = true;

            if (baseUsedType != nullptr)
                baseUsedType->m_non_runtime_reference_exists = true;
        }

        if (computations.ContainsNonEmbeddedReference())
            usedType->m_non_embedded_reference_exists = true;

        if (computations.ContainsArrayPointerReference() || computations.ContainsArrayReference())
            usedType->m_array_reference_exists = true;

        if(computations.ContainsPointerArrayReference() && !member->m_is_string)
        {
            usedType->m_pointer_array_reference_exists = true;

            if (member->m_is_reusable)
                usedType->m_pointer_array_reference_is_reusable = true;
        }

        if(usedType->m_info != nullptr && StructureComputations(usedType->m_info).IsAsset() && !computations.IsInRuntimeBlock() && !usedType->m_members_loaded)
        {
            usedType->m_members_loaded = true;
            AddMembersToContext(usedType->m_info);
        }
    }
}

void RenderingContext::MakeAsset(StructureInformation* asset)
{
    m_asset = asset;
    auto assetUsedType = std::make_unique<RenderingUsedType>(asset->m_definition, asset);
    assetUsedType->m_is_context_asset = true;
    m_used_types_lookup.emplace(std::make_pair(asset->m_definition, std::move(assetUsedType)));

    AddMembersToContext(asset);
}

void RenderingContext::CreateUsedTypeCollections()
{
    for(const auto& [dataDef, usedType] : m_used_types_lookup)
    {
        m_used_types.push_back(usedType.get());

        if (usedType->m_info != nullptr)
        {
            StructureComputations computations(usedType->m_info);

            if(usedType->m_info->m_definition == dataDef)
                m_used_structures.push_back(usedType.get());

            if(computations.IsAsset() && usedType->m_info != m_asset)
                m_referenced_assets.push_back(usedType.get());

            if (!m_has_actions)
            {
                if ((!computations.IsAsset() || usedType->m_is_context_asset)
                    && usedType->m_non_runtime_reference_exists
                    && usedType->m_info->m_post_load_action)
                {
                    m_has_actions = true;
                }
            }
        }

    }
}

std::unique_ptr<RenderingContext> RenderingContext::BuildContext(const IDataRepository* repository, StructureInformation* asset)
{
    auto context = std::make_unique<RenderingContext>(RenderingContext(repository->GetGameName(), repository->GetAllFastFileBlocks()));

    context->MakeAsset(asset);
    context->CreateUsedTypeCollections();

    return std::move(context);
}
