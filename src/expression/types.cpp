#include <expression/types.hpp>

#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& stream, const expression::State state) {
  switch (state) {
  case expression::State::Unbound: stream << "u"; break;
  case expression::State::True: stream << "t"; break;
  case expression::State::False: stream << "f"; break;
  default: stream << "<UNDEF " << static_cast<int>(state) << ">"; break;
  }
  return stream;
}
