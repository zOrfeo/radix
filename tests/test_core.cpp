#include <catch2/catch_test_macros.hpp>
#include "core/core.h"
#include "base.h"

TEST_CASE("Build Prefix", "[core][prefix]") {
    CHECK(buildPrefix(Base::BIN) == "0b");
    CHECK(buildPrefix(Base::OCT) == "0o");
    CHECK(buildPrefix(Base::DEC) == "");
    CHECK(buildPrefix(Base::HEX) == "0x");
    CHECK(buildPrefix(Base::UNKNOWN) == "");
}
