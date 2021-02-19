#pragma once

#include <limits>
#include <memory>

#include "Domain/Evaluation/IEvaluation.h"
#include "Parsing/Commands/Impl/CommandsParserState.h"
#include "Parsing/Commands/Impl/CommandsParserValue.h"
#include "Parsing/Matcher/AbstractMatcher.h"
#include "Parsing/Matcher/MatcherLabel.h"
#include "Parsing/Sequence/SequenceResult.h"

class CommandsCommonMatchers
{
public:
    typedef AbstractMatcher<CommandsParserValue> matcher_t;
    typedef IMatcherForLabelSupplier<CommandsParserValue> supplier_t;

    static constexpr int LABEL_TYPENAME = std::numeric_limits<int>::max() - 1;
    static constexpr int LABEL_ARRAY_DEF = std::numeric_limits<int>::max() - 2;
    static constexpr int LABEL_EVALUATION = std::numeric_limits<int>::max() - 3;
    
    static std::unique_ptr<matcher_t> Typename(const supplier_t* labelSupplier);
    static std::unique_ptr<matcher_t> ArrayDef(const supplier_t* labelSupplier);

private:
    static std::unique_ptr<matcher_t> OperandArray(const supplier_t* labelSupplier);
    static std::unique_ptr<matcher_t> Operand(const supplier_t* labelSupplier);
    static std::unique_ptr<matcher_t> OperationType(const supplier_t* labelSupplier);

public:
    static std::unique_ptr<matcher_t> Evaluation(const supplier_t* labelSupplier);
    static std::unique_ptr<IEvaluation> ParseEvaluation(CommandsParserState* state, SequenceResult<CommandsParserValue>& result);
};
