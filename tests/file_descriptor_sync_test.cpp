#include <deque>
#include <filesystem>
#include <vector>

#include "catch2/catch_all.hpp"
#include "fd/sync/file_descriptor.hpp"
#include "fmt/core.h"

TEST_CASE("file_descriptor read", "[file_descriptor_sync]")
{
    const auto path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "test_file.txt");

    SECTION("Read the first four characters into vector<char>")
    {
        fd::sync::file_descriptor file{ path, fd::flags::rdonly };
        std::vector<char> vec{ 4 };

        file.read(vec, 4);

        REQUIRE(vec[0] == 't');
        REQUIRE(vec[1] == 'e');
        REQUIRE(vec[2] == 's');
        REQUIRE(vec[3] == 't');
    }

    SECTION("Read the first four characters into std::array<char, 4>")
    {
        fd::sync::file_descriptor file{ path, fd::flags::rdonly };
        std::array<char, 4> arr{ 4 };

        file.read(arr, 4);

        REQUIRE(arr[0] == 't');
        REQUIRE(arr[1] == 'e');
        REQUIRE(arr[2] == 's');
        REQUIRE(arr[3] == 't');
    }

    SECTION("Read the first four characters into char[4]")
    {
        fd::sync::file_descriptor file{ path, fd::flags::rdonly };
        char arr[4];  // NOLINT

        file.read(arr, 4);

        REQUIRE(arr[0] == 't');
        REQUIRE(arr[1] == 'e');
        REQUIRE(arr[2] == 's');
        REQUIRE(arr[3] == 't');
    }
}

TEST_CASE("file_descriptor write", "[file_descriptor_sync]")
{
    const auto path = fmt::format("{}/{}", TEST_RESOURCE_DIR, "new_file.txt");

    SECTION("Write the four characters into vector<char>")
    {
        fd::sync::file_descriptor file{ path, fd::flags::wronly | fd::flags::creat, fd::modes::iwusr };  // NOLINT
        std::vector<char> vec{ 'd', 'a', 't', 'a' };

        REQUIRE(file.write(vec) == 4);
        REQUIRE(file.write(std::vector<char>{ 'd', 'a', 't', 'a' }) == 4);
    }

    SECTION("Write the four characters into std::array<char, 4>")
    {
        fd::sync::file_descriptor file{ path, fd::flags::wronly | fd::flags::creat, fd::modes::iwusr };  // NOLINT
        std::array<char, 4> arr{ 'd', 'a', 't', 'a' };

        REQUIRE(file.write(arr) == 4);
    }

    SECTION("Write the four characters into char[4]")
    {
        fd::sync::file_descriptor file{ path, fd::flags::wronly | fd::flags::creat, fd::modes::iwusr };  // NOLINT
        char arr[4]{ 'd', 'a', 't', 'a' };                                                               // NOLINT

        REQUIRE(file.write(arr) == 4);
    }

    std::filesystem::remove(path);
}