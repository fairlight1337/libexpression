#include <catch2/catch_test_macros.hpp>

#include <expression/expression.hpp>

TEST_CASE("And'ing numerical values yields the correct result", "[numerical_values]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const uint32_t numeric_value_3 = 3U;
  const uint32_t numeric_value_5 = 5U;

  Expr lhs(numeric_value_3);
  Expr rhs(numeric_value_5);
  Expr result = lhs & rhs;

  REQUIRE(static_cast<uint32_t>(result) == (numeric_value_3 & numeric_value_5));
}
