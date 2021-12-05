#include "SimpleExpressionConditionalOperator.h"

SimpleExpressionConditionalOperator::SimpleExpressionConditionalOperator()
= default;

SimpleExpressionConditionalOperator::SimpleExpressionConditionalOperator(std::unique_ptr<ISimpleExpression> condition, std::unique_ptr<ISimpleExpression> trueExpression,
                                                                         std::unique_ptr<ISimpleExpression> falseExpression)
    : m_condition(std::move(condition)),
      m_true_value(std::move(trueExpression)),
      m_false_value(std::move(falseExpression))
{
}

bool SimpleExpressionConditionalOperator::IsStatic() const
{
    return m_condition->IsStatic() && m_true_value->IsStatic() && m_false_value->IsStatic();
}

SimpleExpressionValue SimpleExpressionConditionalOperator::Evaluate() const
{
    return m_condition->Evaluate().IsTruthy() ? m_true_value->Evaluate() : m_false_value->Evaluate();
}
