#ifndef EXPRESSION_TYPES_HPP_
#define EXPRESSION_TYPES_HPP_

#include <string>

namespace expression {

enum class State {
  // The value state is neither True nor False and has to be decided via solver inference.
  Unbound,
  // The value is bound to be logically true.
  True,
  // The value is bound to be logically false.
  False
};

}  // namespace expression

std::ostream& operator<<(std::ostream& stream, const expression::State state);

#endif  // EXPRESSION_TYPES_HPP_
