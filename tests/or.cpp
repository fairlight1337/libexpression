#include <catch2/catch_test_macros.hpp>

#include <expression/expression.hpp>

TEST_CASE("Or'ing numerical values yields the correct result", "[numerical_values]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const uint32_t numeric_value_3 = 3U;
  const uint32_t numeric_value_5 = 5U;

  Expr lhs(numeric_value_3);
  Expr rhs(numeric_value_5);
  Expr result = lhs | rhs;

  REQUIRE(static_cast<uint32_t>(result) == (numeric_value_3 | numeric_value_5));
}

TEST_CASE("Comparing two equal ordered OR expressions yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const std::string variable_name_a = "a";
  const std::string variable_name_b = "b";

  Expr a(variable_name_a);
  Expr b(variable_name_b);

  Expr lhs = a | b;
  Expr rhs = a | b;

  REQUIRE(lhs == rhs);
  REQUIRE(rhs == lhs);
}

TEST_CASE("Comparing two equal unordered OR expressions yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const std::string variable_name_a = "a";
  const std::string variable_name_b = "b";

  Expr a(variable_name_a);
  Expr b(variable_name_b);

  Expr lhs = a | b;
  Expr rhs = b | a;

  REQUIRE(lhs == rhs);
  REQUIRE(rhs == lhs);
}

TEST_CASE("Comparing two unequal OR expressions yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const std::string variable_name_a = "a";
  const std::string variable_name_b = "b";
  const std::string variable_name_c = "c";

  Expr a(variable_name_a);
  Expr b(variable_name_b);
  Expr c(variable_name_c);

  Expr lhs = a | b;
  Expr rhs = a | c;

  REQUIRE(lhs != rhs);
  REQUIRE(rhs != lhs);
}
