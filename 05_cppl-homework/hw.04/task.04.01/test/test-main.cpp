#include <iostream>
#include "LinkedList.h"

#include "Catch2/catch_test_macros.hpp"
#include "Catch2/catch_session.hpp"

TEST_CASE("Testing LinkedList", "[list]")
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

int main()
{
    return Catch::Session().run();
}