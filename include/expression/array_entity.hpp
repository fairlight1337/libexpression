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

template<typename TDataType, uint32_t BitWidth = sizeof(TDataType) * CHAR_BIT>
class ArrayEntity : public Entity {
 public:
  ArrayEntity() : entities_{BitWidth} {
    for (uint32_t idx = 0; idx < BitWidth; ++idx) {
      entities_[idx] = std::make_shared<ConstantEntity>(State::Unbound);
    }
  }

  explicit ArrayEntity(TDataType value) : entities_{BitWidth} {
    for (uint32_t idx = 0; idx < BitWidth; ++idx) {
      const State state = value >> (BitWidth - idx - 1U) & 1U ? State::True : State::False;
      entities_[idx] = std::make_shared<ConstantEntity>(state);
    }
  }

  explicit ArrayEntity(std::vector<std::shared_ptr<Entity>> entities) : entities_{std::move(entities)} {}
  explicit ArrayEntity(std::vector<std::shared_ptr<Entity>>&& entities) : entities_{std::move(entities)} {}

  explicit operator std::string() const override {
    std::string out;
    for (const std::shared_ptr<Entity>& entity : entities_) {
      if (!out.empty()) { out += ", "; }
      out += entity->operator std::string();
    }
    return "[" + out + "]";
  }

  std::shared_ptr<Entity>& operator[](uint32_t index) {
    if (index > entities_.size() - 1) { throw std::runtime_error("Index out of bounds."); }
    return entities_[index];
  }

  const std::shared_ptr<Entity>& operator[](uint32_t index) const {
    if (index > entities_.size() - 1) { throw std::runtime_error("Index out of bounds."); }
    return entities_[index];
  }

  [[nodiscard]] size_t size() const override { return entities_.size(); }

  [[nodiscard]] bool allBoundConstants() const {
    for (const std::shared_ptr<Entity>& entity : entities_) {
      auto constant = std::dynamic_pointer_cast<ConstantEntity>(entity);
      if (constant == nullptr || constant->state() == State::Unbound) { return false; }
    }
    return true;
  }

  [[nodiscard]] std::optional<TDataType> getNumericValue() const {
    if (!allBoundConstants()) {
      return std::nullopt;
    }

    TDataType value = TDataType();
    for (uint32_t idx = 0; idx < BitWidth; ++idx) {
      const State state = std::dynamic_pointer_cast<ConstantEntity>(entities_[idx])->state();
      if (state == State::False) { continue; }
      value |= (1U << (BitWidth - idx - 1U));
    }
    return value;
  }

  bool operator==(const std::shared_ptr<Entity>& entity) const override {
    if (auto array = std::dynamic_pointer_cast<ArrayEntity<TDataType, BitWidth>>(entity)) {
      for (size_t idx = 0; idx < entities_.size(); ++idx) {
        if (!static_cast<bool>(entities_[idx]->operator==(array->operator[](idx)))) { return false; }
      }
    }
    return true;
  }

 protected:
  [[nodiscard]] std::vector<std::shared_ptr<Entity>>& getEntities() { return entities_; }

  [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getEntities() const { return entities_; }

 private:
  std::vector<std::shared_ptr<Entity>> entities_;
};

}  // namespace expression

#endif  // EXPRESSION_ARRAY_ENTITY_HPP_
