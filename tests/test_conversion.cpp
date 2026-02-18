#include <catch2/catch_test_macros.hpp>
#include "conversion/conversion.h"
#include "base.h"

TEST_CASE("Convert from Decimal") {
    CHECK(convertFromBase("123", Base::DEC) == 123);
}
