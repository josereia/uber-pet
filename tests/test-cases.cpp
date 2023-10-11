#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <core/utils/utils.hpp>
#include <cstdint>

TEST_CASE("Value discounts are computed", "[calc_val_discount]")
{
  REQUIRE(Utils::calc_val_discount("70", "10") == "60,00");
  REQUIRE(Utils::calc_val_discount("10", "10") == "0,00");
  REQUIRE(Utils::calc_val_discount("100", "50") == "50,00");
  REQUIRE(Utils::calc_val_discount("24", "10") == "14,00");
  REQUIRE(Utils::calc_val_discount("42,90", "12,24") == "30,66");
}

TEST_CASE("Percentual discounts are computed", "[calc_percent_discount]")
{
  REQUIRE(Utils::calc_percent_discount("70", "10") == "63,00");
  REQUIRE(Utils::calc_percent_discount("10", "10") == "9,00");
  REQUIRE(Utils::calc_percent_discount("100", "50") == "50,00");
  REQUIRE(Utils::calc_percent_discount("24", "10") == "21,60");
  REQUIRE(Utils::calc_percent_discount("42,90", "12,24") == "37,65");
}