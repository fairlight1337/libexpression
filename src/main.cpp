// System includes
#include <cstdlib>
#include <iostream>

// Expression includes
#include <expression/expression.hpp>

int main(int argc, char** argv) {
  using Expr = expression::Expression<uint32_t, 1>;

  Expr a;

  std::cout << a << std::endl;

  return EXIT_SUCCESS;
}
