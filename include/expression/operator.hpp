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

  bool operator==(const std::shared_ptr<Entity>& entity) const override {
    if (auto op = std::dynamic_pointer_cast<Operator<TDataType, NumOperands, BitWidth>>(entity)) {
      if (op->getSymbol() != this->getSymbol()) {
        return false;
      }
      if (op->size() != this->size()) {
        return false;
      }

      std::vector<std::shared_ptr<Entity>> other_entities = op->getEntities();
      const std::vector<std::shared_ptr<Entity>> own_entities = this->getEntities();

      for (const std::shared_ptr<Entity>& own_entity : own_entities) {
        for (auto it = other_entities.begin();
             it != other_entities.end(); ++it) {
          if (static_cast<bool>(own_entity->operator==(*it))) {
            other_entities.erase(it);
            break;
          }
        }
      }

      if (!other_entities.empty()) {
        return false;
      }
    }
    return true;
  }

  [[nodiscard]] const std::string& getSymbol() const {
    return symbol_;
  }

 private:
  std::string symbol_;
};

}  // namespace expression

#endif  // EXPRESSION_OPERATOR_HPP_
