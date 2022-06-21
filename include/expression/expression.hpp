#ifndef EXPRESSION_EXPRESSION_HPP_
#define EXPRESSION_EXPRESSION_HPP_

#include <climits>
#include <iostream>
#include <string>

#include <expression/array_entity.hpp>
#include <expression/constant_entity.hpp>
#include <expression/variable_entity.hpp>

namespace expression {

template<typename TDataType, uint32_t BitWidth = sizeof(TDataType) * CHAR_BIT>
class Expression {
 public:
  explicit Expression(TDataType value)
    : entity_{std::make_shared<ArrayEntity<TDataType, BitWidth>>(value)} {}
  explicit Expression(const std::string& symbol)
    : entity_{std::make_shared<ArrayEntity<TDataType, BitWidth>>()} {
    for (uint32_t idx = 0; idx < BitWidth; ++idx) {
      entity_->operator[](BitWidth - 1 - idx) = std::make_shared<VariableEntity>(symbol, idx);
    }
  }
  explicit Expression(std::string&& symbol)
    : entity_{std::make_shared<ArrayEntity<TDataType, BitWidth>>()} {
    for (uint32_t idx = 0; idx < BitWidth; ++idx) {
      entity_->operator[](BitWidth - 1 - idx) = std::make_shared<VariableEntity>(symbol, idx);
    }
  }
  explicit Expression(std::shared_ptr<ArrayEntity<TDataType, BitWidth>>&& entity)
    : entity_{std::move(entity)} {}
  explicit Expression(const std::shared_ptr<ArrayEntity<TDataType, BitWidth>>& entity) : entity_{entity} {}
  Expression(const Expression<TDataType, BitWidth>& expr) : entity_{expr.entity_} {}
  Expression(Expression<TDataType, BitWidth>&& expr) noexcept : entity_{std::move(expr.entity_)} {}

  template<typename TOtherDataType, uint32_t OtherBitWidth>
  explicit Expression(const Expression<TOtherDataType, OtherBitWidth>& expr)
    : entity_{std::make_shared<ArrayEntity<TDataType, BitWidth>>()} {
    for (uint32_t idx = 0; idx < BitWidth; ++idx) {
      if (idx < OtherBitWidth) {
        entity_->operator[](BitWidth - 1 - idx) =
          expr.entity()->operator[](OtherBitWidth - 1 - idx);
      } else {
        entity_->operator[](BitWidth - 1 - idx) = std::make_shared<ConstantEntity>(State::False);
      }
    }
  }

  ~Expression() = default;

  explicit operator std::string() const {
    return entity_->operator std::string();
  }

  template<typename TOtherDataType, unsigned int OtherBitWidth>
  Expression& operator=(const Expression<TOtherDataType, OtherBitWidth>& expr) {
    for (int idx = 0; idx < BitWidth; ++idx) {
      if (idx < OtherBitWidth) {
        entity_->operator[](BitWidth - 1 - idx) = expr.entity_->operator[](OtherBitWidth - 1 - idx);
      } else {
        entity_->operator[](BitWidth - 1 - idx) = std::make_shared<ConstantEntity>(State::False);
      }
    }
    return *this;
  }

  Expression& operator=(const Expression& expr) noexcept {
    if (this == &expr) {
      return *this;
    }
    entity_ = expr.entity_;
    return *this;
  }

  template<typename TOtherDataType, unsigned int OtherBitWidth>
  Expression& operator=(Expression<TOtherDataType, OtherBitWidth>&& expr) {
    for (int idx = 0; idx < BitWidth; ++idx) {
      if (idx < OtherBitWidth) {
        entity_->operator[](BitWidth - 1 - idx) =
            std::move(expr.entity_->operator[](OtherBitWidth - 1 - idx));
      } else {
        entity_->operator[](BitWidth - 1 - idx) = std::make_shared<ConstantEntity>(State::False);
      }
    }
    return *this;
  }

  // Returns the width of the contained structure, in bits.
  static unsigned int getWidth() { return BitWidth; }

  Expression& operator=(Expression&& expr) noexcept {
    entity_ = std::move(expr.entity_);
    return *this;
  }

  Expression& operator=(TDataType value) {
    entity_ = std::make_shared<ArrayEntity<TDataType, BitWidth>>(value);
    return *this;
  }

  Expression& operator=(TDataType&& value) {
    entity_ = std::make_shared<ArrayEntity<TDataType, BitWidth>>(std::move(value));
    return *this;
  }

  Expression& operator=(const std::string& symbol) {
    entity_ = std::make_shared<ArrayEntity<TDataType, BitWidth>>();
    for (int idx = 0; idx < BitWidth; ++idx) {
      entity_->operator[](BitWidth - 1 - idx) = std::make_shared<VariableEntity>(symbol, idx);
    }
    return *this;
  }

  Expression& operator=(std::string&& symbol) {
    entity_ = std::make_shared<ArrayEntity<TDataType, BitWidth>>();
    for (int idx = 0; idx < BitWidth; ++idx) {
      entity_->operator[](BitWidth - 1 - idx) = std::make_shared<VariableEntity>(symbol, idx);
    }
    return *this;
  }

  bool operator==(const Expression& expr) const {
    if (entity_ == expr.entity_) { return true; }
    for (size_t idx = 0; idx < entity_->size(); ++idx) {
      if (entity_->operator[](idx) == expr.entity_->operator[](idx)) { continue; }
      if (!static_cast<bool>(entity_->operator[](idx)->operator==(expr.entity_->operator[](idx)))) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Expression& expr) const {
    if (entity_ == expr.entity_) { return false; }
    for (size_t idx = 0; idx < entity_->size(); ++idx) {
      if (static_cast<bool>(entity_->operator[](idx)->operator!=(expr.entity_->operator[](idx)))) {
        return true;
      }
    }
    return false;
  }

  template<unsigned int Length>
  Expression<TDataType, Length> range(unsigned int offset) const {
    if (offset + Length > BitWidth) { throw std::runtime_error("Length too big for source type."); }
    auto array_entity = std::make_shared<ArrayEntity<TDataType, Length>>();
    for (int idx = 0; idx < Length; ++idx) {
      array_entity->operator[](idx) = entity_->operator[](offset + idx);
    }
    return Expression<TDataType, Length>(std::move(array_entity));
  }

  [[nodiscard]] bool isNumericalValue() const {
    return entity_->allBoundConstants();
  }

  explicit operator TDataType() const {
    auto maybe_numeric_value = entity_->getNumericValue();
    if (!maybe_numeric_value) { throw std::runtime_error("Unable to resolve numeric value"); }
    return *maybe_numeric_value;
  }

  [[nodiscard]] std::shared_ptr<ArrayEntity<TDataType, BitWidth>> entity() { return entity_; }

 private:
  std::shared_ptr<ArrayEntity<TDataType, BitWidth>> entity_ {std::make_shared<ArrayEntity<TDataType, BitWidth>>()};
};

}  // namespace expression

template<typename TDataType, uint32_t BitWidth>
std::ostream& operator<<(
    std::ostream& stream, const expression::Expression<TDataType, BitWidth>& expression) {
  stream << expression.operator std::string();
  return stream;
}

#endif  // EXPRESSION_EXPRESSION_HPP_
