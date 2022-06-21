// System includes
#include <cstdlib>
#include <iostream>

// Expression includes
#include <expression/expression.hpp>

int main(int /*argc*/, char** /*argv*/) {
  using Expr = expression::Expression<uint32_t, 4>;

  const uint32_t numeric_value = 5U;

  Expr a(numeric_value);
  Expr b(std::string("b"));

  std::cout << a << std::endl;
  std::cout << b << std::endl;

  return EXIT_SUCCESS;
}
