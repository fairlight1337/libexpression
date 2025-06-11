#ifndef EXPRESSION_EXPRESSION_HPP_
#define EXPRESSION_EXPRESSION_HPP_

// Standard
#include <climits>
#include <iostream>
#include <string>

// Entities
#include <expression/array_entity.hpp>
#include <expression/constant_entity.hpp>
#include <expression/variable_entity.hpp>

// Operators
#include <expression/and_operator.hpp>
#include <expression/or_operator.hpp>
#include <expression/xor_operator.hpp>

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

  Expression operator&(const Expression& expr) const {
    Expression<TDataType, BitWidth> and_expr(0);
    for (size_t idx = 0; idx < entity_->size(); ++idx) {
      const std::shared_ptr<ConstantEntity> lhs_const =
          std::dynamic_pointer_cast<ConstantEntity>(entity_->operator[](idx));
      const std::shared_ptr<ConstantEntity> rhs_const =
          std::dynamic_pointer_cast<ConstantEntity>(expr.entity_->operator[](idx));
      const State lhs_state = lhs_const ? lhs_const->state() : State::False;
      const State rhs_state = rhs_const ? rhs_const->state() : State::False;

      if ((lhs_const && lhs_state == State::False) || (rhs_const && rhs_state == State::False)) {
        and_expr.entity_->operator[](idx) = std::make_shared<ConstantEntity>(State::False);
      } else if (lhs_const && rhs_const && lhs_state == State::True && rhs_state == State::True) {
        and_expr.entity_->operator[](idx) = std::make_shared<ConstantEntity>(State::True);
      } else if (lhs_const && lhs_state == State::True && !rhs_const) {
        and_expr.entity_->operator[](idx) = expr.entity_->operator[](idx);
      } else if (!lhs_const && rhs_const && rhs_state == State::True) {
        and_expr.entity_->operator[](idx) = entity_->operator[](idx);
      } else {
        and_expr.entity_->operator[](idx) =
            std::make_shared<AndOperator<TDataType, BitWidth>>(
                entity_->operator[](idx), expr.entity_->operator[](idx));
      }
    }

    return and_expr;
  }

  Expression operator|(const Expression& expr) const {
    Expression<TDataType, BitWidth> or_expr(0);
    for (size_t idx = 0; idx < entity_->size(); ++idx) {
      const std::shared_ptr<ConstantEntity> lhs_const =
          std::dynamic_pointer_cast<ConstantEntity>(entity_->operator[](idx));
      const std::shared_ptr<ConstantEntity> rhs_const =
          std::dynamic_pointer_cast<ConstantEntity>(expr.entity_->operator[](idx));
      const State lhs_state = lhs_const ? lhs_const->state() : State::False;
      const State rhs_state = rhs_const ? rhs_const->state() : State::False;

      if ((lhs_const && lhs_state == State::True) || (rhs_const && rhs_state == State::True)) {
        or_expr.entity_->operator[](idx) = std::make_shared<ConstantEntity>(State::True);
      } else if (lhs_const && rhs_const && lhs_state == State::False && rhs_state == State::False) {
        or_expr.entity_->operator[](idx) = std::make_shared<ConstantEntity>(State::False);
      } else if (lhs_const && lhs_state == State::False && !rhs_const) {
        or_expr.entity_->operator[](idx) = expr.entity_->operator[](idx);
      } else if (!lhs_const && rhs_const && rhs_state == State::False) {
        or_expr.entity_->operator[](idx) = entity_->operator[](idx);
      } else {
        or_expr.entity_->operator[](idx) =
            std::make_shared<OrOperator<TDataType, BitWidth>>(
                entity_->operator[](idx), expr.entity_->operator[](idx));
      }
    }

    return or_expr;
  }

  Expression operator^(const Expression& expr) const {
    Expression<TDataType, BitWidth> xor_expr(0);
    for (size_t idx = 0; idx < entity_->size(); ++idx) {
      const std::shared_ptr<ConstantEntity> lhs_const =
          std::dynamic_pointer_cast<ConstantEntity>(entity_->operator[](idx));
      const std::shared_ptr<ConstantEntity> rhs_const =
          std::dynamic_pointer_cast<ConstantEntity>(expr.entity_->operator[](idx));
      const State lhs_state = lhs_const ? lhs_const->state() : State::False;
      const State rhs_state = rhs_const ? rhs_const->state() : State::False;

      if (lhs_const && rhs_const) {
        const bool res = (lhs_state == State::True) != (rhs_state == State::True);
        xor_expr.entity_->operator[](idx) =
            std::make_shared<ConstantEntity>(res ? State::True : State::False);
      } else if (lhs_const && lhs_state == State::False) {
        xor_expr.entity_->operator[](idx) = expr.entity_->operator[](idx);
      } else if (rhs_const && rhs_state == State::False) {
        xor_expr.entity_->operator[](idx) = entity_->operator[](idx);
      } else {
        xor_expr.entity_->operator[](idx) =
            std::make_shared<XorOperator<TDataType, BitWidth>>(
                entity_->operator[](idx), expr.entity_->operator[](idx));
      }
    }

    return xor_expr;
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
