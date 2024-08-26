#include <iostream>
#include "LinkedList.h"

#include "Catch2/catch_test_macros.hpp"
#include "Catch2/catch_session.hpp"

TEST_CASE("Testing LinkedList Values", "[list]")
{
    List list;
    SECTION("Size") {
        CHECK(list.Size() == 0);
        list.PushFront(1);
        list.PushFront(0);
        list.PushBack(2);
        CHECK(list.Size() == 3);
    }
    SECTION("Empty") {
        list.Size() == 0;
        CHECK(list.Empty() == true);
        list.PushFront(1);
        list.PushBack(2);
        CHECK(list.Empty() == false);
    }
    SECTION("Clear") {
        list.Clear();
        CHECK(list.Size() == 0);
    }
}

TEST_CASE("Testing LinkedList Methods", "[list]")
{
    List list;
    SECTION("PushBack") {
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        CHECK(list.PopBack() == 3);
        CHECK(list.PopBack() == 2);
    }
    SECTION("PushFront") {
        list.PushFront(3);
        list.PushFront(2);
        list.PushFront(1);
        CHECK(list.PopFront() == 1);
        CHECK(list.PopFront() == 2);
    }
    SECTION("PopBack") {
        list.PushBack(1);
        CHECK(list.PopBack() == 1);
        list.PushBack(4);
        list.PushBack(3);
        list.PushFront(5);
        CHECK(list.PopBack() == 3);
    }
    SECTION("PopFront") {
        list.PushBack(1);
        CHECK(list.PopFront() == 1);
        list.PushFront(4);
        list.PushFront(5);
        list.PushBack(3);
        CHECK(list.PopFront() == 5);
    }
    SECTION("Throws Exceptions") {
        list.Clear();
        CHECK_THROWS(list.PopBack());
        CHECK_THROWS(list.PopFront());
    }
}

int main()
{
    return Catch::Session().run();
}