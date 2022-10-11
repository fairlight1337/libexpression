#ifndef EXPRESSION_OPERATOR_HPP_
#define EXPRESSION_OPERATOR_HPP_

#include "expression/array_entity.hpp"

namespace expression {

template<typename TDataType, uint32_t NumOperands, uint32_t BitWidth = sizeof(TDataType) * CHAR_BIT>
class Operator : public ArrayEntity<TDataType, NumOperands> {
 public:
  explicit Operator(std::string symbol)
      : symbol_{std::move(symbol)} {
    std::vector<std::shared_ptr<Entity>>& entities = this->getEntities();
    for (uint32_t idx = 0; idx < NumOperands; ++idx) {
      entities[idx] = std::make_shared<ConstantEntity>(State::Unbound);
    }
  }

  explicit operator std::string() const override {
    const std::vector<std::shared_ptr<Entity>>& entities = this->getEntities();
    std::string out;
    for (const std::shared_ptr<Entity>& entity : entities) {
      if (!out.empty()) { out += ", "; }
      out += entity->operator std::string();
    }
    return symbol_ + "(" + out + ")";
  }

 private:
  std::string symbol_;
};

}  // namespace expression

#endif  // EXPRESSION_OPERATOR_HPP_
