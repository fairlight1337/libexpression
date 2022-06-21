#ifndef EXPRESSION_CONSTANT_ENTITY_HPP_
#define EXPRESSION_CONSTANT_ENTITY_HPP_

#include <expression/entity.hpp>
#include <expression/types.hpp>

namespace expression {

class ConstantEntity : public Entity {
 public:
  explicit ConstantEntity(State state) : state_{state} {}

  // Returns the state of this constant entity.
  [[nodiscard]] State state() const { return state_; }

  explicit operator std::string() const override {
    return to_string(state_);
  }

  bool operator==(const std::shared_ptr<Entity>& entity) const override {
    if (auto constant = std::dynamic_pointer_cast<ConstantEntity>(entity)) {
      return constant->state() == state_;
    }
    return false;
  }

  [[nodiscard]] size_t size() const override { return 1; }

 private:
  const State state_;
};

}  // namespace expression

#endif  // EXPRESSION_CONSTANT_ENTITY_HPP_
