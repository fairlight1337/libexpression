#include <expression/types.hpp>

#include <iostream>
#include <string>

namespace expression {

std::string to_string(expression::State state) {
  switch (state) {
  case expression::State::Unbound:
    return "u";
  case expression::State::True:
    return "t";
  case expression::State::False:
    return "f";
  default:
    return "<UNDEF " + std::to_string(static_cast<uint32_t>(state)) + ">";
  }
}

}  // namespace expression
