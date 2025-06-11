#ifndef EXPRESSION_TYPES_HPP_
#define EXPRESSION_TYPES_HPP_

#include <string>
#include <cstdint>

namespace expression {

enum class State : uint32_t {
  // The value state is neither True nor False and has to be decided via solver inference.
  Unbound = 0,
  // The value is bound to be logically true.
  True = 1,
  // The value is bound to be logically false.
  False = 2
};

std::string to_string(expression::State state);

}  // namespace expression

#endif  // EXPRESSION_TYPES_HPP_
