#ifndef EXPRESSION_ARRAY_ENTITY_HPP_
#define EXPRESSION_ARRAY_ENTITY_HPP_

#include <climits>
#include <deque>
#include <optional>
#include <string>
#include <vector>

#include "expression/constant_entity.hpp"
#include "expression/entity.hpp"
#include "expression/types.hpp"

namespace expression {

template<typename TDataType, unsigned int BitWidth = sizeof(TDataType) * CHAR_BIT>
class ArrayEntity : public Entity {
 public:
  ArrayEntity() : entities_{BitWidth} {
    for (int idx = 0; idx < BitWidth; ++idx) {
      entities_[idx] = std::make_shared<ConstantEntity>(State::Unbound);
    }
  }

  ArrayEntity(TDataType value) : entities_{BitWidth} {
    for (int idx = 0; idx < BitWidth; ++idx) {
      const State state = value >> (BitWidth - idx - 1) & 0x1 ? State::True : State::False;
      entities_[idx] = std::make_shared<ConstantEntity>(state);
    }
  }

  ArrayEntity(const std::vector<std::shared_ptr<Entity>>& entities) : entities_{entities} {}
  ArrayEntity(std::vector<std::shared_ptr<Entity>>&& entities) : entities_{std::move(entities)} {}

  operator std::string() const override {
    std::string out;
    for (const std::shared_ptr<Entity>& entity : entities_) {
      if (out != "") { out += ", "; }
      out += entity->operator std::string();
    }
    return "[" + out + "]";
  }

  std::shared_ptr<Entity>& operator[](unsigned int index) {
    if (index > entities_.size() - 1) { throw std::runtime_error("Index out of bounds."); }
    return entities_[index];
  }

  const std::shared_ptr<Entity>& operator[](unsigned int index) const {
    if (index > entities_.size() - 1) { throw std::runtime_error("Index out of bounds."); }
    return entities_[index];
  }

  size_t size() const override { return entities_.size(); }

  bool allBoundConstants() const {
    for (const std::shared_ptr<Entity>& entity : entities_) {
      auto constant = std::dynamic_pointer_cast<ConstantEntity>(entity);
      if (constant == nullptr || constant->state() == State::Unbound) { return false; }
    }
    return true;
  }

  std::optional<TDataType> getNumericValue() const {
    if (!allBoundConstants()) {
      return std::nullopt;
    }

    TDataType value = TDataType();
    for (int idx = 0; idx < BitWidth; ++idx) {
      const State state = std::dynamic_pointer_cast<ConstantEntity>(entities_[idx])->state();
      if (state == State::False) { continue; }
      value |= (0x1 << (BitWidth - idx - 1));
    }
    return value;
  }

  bool operator==(std::shared_ptr<Entity> entity) const override {
    if (auto array = std::dynamic_pointer_cast<ArrayEntity<TDataType, BitWidth>>(entity)) {
      for (size_t idx = 0; idx < entities_.size(); ++idx) {
        if (entities_[idx]->operator==(array->operator[](idx)) == false) { return false; }
      }
    }
    return true;
  }

 protected:
  std::vector<std::shared_ptr<Entity>> entities_;
};

}  // namespace expression

#endif  // EXPRESSION_ARRAY_ENTITY_HPP_
