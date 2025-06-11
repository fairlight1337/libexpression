#ifndef EXPRESSION_OR_OPERATOR_HPP_
#define EXPRESSION_OR_OPERATOR_HPP_

#include "expression/operator.hpp"

namespace expression {

template<typename TDataType, uint32_t BitWidth = sizeof(TDataType) * CHAR_BIT>
class OrOperator : public Operator<TDataType, 2, BitWidth> {
 public:
  OrOperator(std::shared_ptr<Entity> lhs, std::shared_ptr<Entity> rhs)
      : Operator<TDataType, 2, BitWidth>("|") {
    std::vector<std::shared_ptr<Entity>>& entities = this->getEntities();
    entities[0] = std::move(lhs);
    entities[1] = std::move(rhs);
  }
};

}  // namespace expression

#endif  // EXPRESSION_OR_OPERATOR_HPP_
