#ifndef EXPRESSION_EXPRESSION_HPP_
#define EXPRESSION_EXPRESSION_HPP_

#include <climits>
#include <iostream>
#include <string>

#include <expression/array_entity.hpp>

namespace expression {

template<typename TDataType, uint32_t BitWidth = sizeof(TDataType) * CHAR_BIT>
class Expression {
 public:
  Expression() : entity_{std::make_shared<ArrayEntity<TDataType, BitWidth>>()} {}

  operator std::string() const {
    return entity_->operator std::string();
  }

 private:
  std::shared_ptr<ArrayEntity<TDataType, BitWidth>> entity_;
};

}  // namespace expression

template<typename TDataType, uint32_t BitWidth>
std::ostream& operator<<(
    std::ostream& stream, const expression::Expression<TDataType, BitWidth>& expression) {
  stream << expression.operator std::string();
  return stream;
}

#endif  // EXPRESSION_EXPRESSION_HPP_
