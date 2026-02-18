#include <catch2/catch_test_macros.hpp>
#include "validation/validation.h"
#include "constants.h"

TEST_CASE("Validate Binary Input") {
    CHECK(validateBinary("1010") == ALL_OK);
}
