#include "fd/fd.hpp"

#include "catch2/catch_all.hpp"

TEST_CASE("foo", "[fd]") { REQUIRE(fd::foo() == 42); }