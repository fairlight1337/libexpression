#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <expression/expression.hpp>

TEST_CASE("Comparing two equal numerical values yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const uint32_t numeric_value = 3U;

  Expr lhs(numeric_value);
  Expr rhs(numeric_value);

  REQUIRE(lhs == rhs);
  REQUIRE(rhs == lhs);
}

TEST_CASE("Comparing two unequal numerical values yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const uint32_t numeric_value_3 = 3U;
  const uint32_t numeric_value_5 = 5U;

  Expr lhs(numeric_value_3);
  Expr rhs(numeric_value_5);

  REQUIRE(lhs != rhs);
  REQUIRE(rhs != lhs);
}

TEST_CASE("Comparing two equal variable values yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const std::string variable_name = "a";

  Expr lhs(variable_name);
  Expr rhs(variable_name);

  REQUIRE(lhs == rhs);
  REQUIRE(rhs == lhs);
}

TEST_CASE("Comparing two unequal variable values yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const std::string variable_name_a = "a";
  const std::string variable_name_b = "b";

  Expr lhs(variable_name_a);
  Expr rhs(variable_name_b);

  REQUIRE(lhs != rhs);
  REQUIRE(rhs != lhs);
}

TEST_CASE("Comparing a numerical and a variable values yields the correct result", "[equality]") {
  using Expr = expression::Expression<uint32_t, 4>;

  const std::string variable_name = "a";
  const uint32_t numeric_value = 3U;

  Expr lhs(variable_name);
  Expr rhs(numeric_value);

  REQUIRE(lhs != rhs);
  REQUIRE(rhs != lhs);
}
