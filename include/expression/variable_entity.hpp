#ifndef EXPRESSION_VARIABLE_ENTITY_HPP_
#define EXPRESSION_VARIABLE_ENTITY_HPP_

#include <expression/constant_entity.hpp>
#include <expression/entity.hpp>

namespace expression {

class VariableEntity : public Entity {
 public:
  VariableEntity(std::string symbol, uint32_t index)
    : symbol_{std::move(symbol)}, index_{index} {}

  // Returns the state of this constant entity.
  [[nodiscard]] const std::string& symbol() const { return symbol_; }

  [[nodiscard]] uint32_t index() const { return index_; }

  explicit operator std::string() const override {
    return symbol_ + std::to_string(index_);
  }

  bool operator==(const std::shared_ptr<Entity>& entity) const override {
    if (auto variable = std::dynamic_pointer_cast<VariableEntity>(entity)) {
      return variable->symbol() == symbol_ && variable->index() == index_;
    }
    return false;
  }

  [[nodiscard]] size_t size() const override { return 1U; }

 private:
  const std::string symbol_;
  const uint32_t index_;
};

}  // namespace expression

#endif  // EXPRESSION_VARIABLE_ENTITY_HPP_
