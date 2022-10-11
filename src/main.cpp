// System includes
#include <cstdlib>
#include <iostream>

// Expression includes
#include <expression/expression.hpp>

int main(int /*argc*/, char** /*argv*/) {
  using Expr = expression::Expression<uint32_t, 4>;

  const uint32_t numeric_value_5 = 5U;
  const uint32_t numeric_value_4 = 4U;
  const uint32_t numeric_value_3 = 3U;

  Expr a(numeric_value_5);
  Expr b(std::string("b"));
  Expr c = a & b;
  Expr d(numeric_value_4);
  Expr e = c & d;

  Expr a1(numeric_value_3);
  Expr a2(numeric_value_5);
  Expr a3 = a1 & a2;
  std::cout << a1 << " & " << a2 << " = " << a3 << std::endl;

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  std::cout << d << std::endl;
  std::cout << e << std::endl;

  std::cout << static_cast<uint32_t>(a) << std::endl;

  return EXIT_SUCCESS;
}
