#pragma once

#include "core/Containers/vector.h"

TEST_CASE("gueepo::vector", "[gueepo::vector]") {

    SECTION("empty vector") {
        gueepo::vector<int> myIntVector;
        REQUIRE(myIntVector.size() == 0);
    }

    SECTION("creating and adding elements to a vector") {
        gueepo::vector<int> myIntVector;
        myIntVector.add(3);
        myIntVector.add(4);
        myIntVector.add(5);
        REQUIRE(myIntVector.size() == 3);
        REQUIRE(myIntVector[0] == 3);
        REQUIRE(myIntVector[1] == 4);
        REQUIRE(myIntVector[2] == 5);
    }

    SECTION("inserting one more element") {
        gueepo::vector<int> myIntVector;
        myIntVector.add(3);
        myIntVector.add(4);
        myIntVector.add(5);

        myIntVector.add(10);
        REQUIRE(myIntVector[3] == 10);
        REQUIRE(myIntVector.size() == 4);
    }

    SECTION("insert at position 0") {
        gueepo::vector<int> myIntVector;
        myIntVector.add(3);
        myIntVector.add(4);
        myIntVector.add(5);
        myIntVector.add(10);

        // testing the insert function
        myIntVector.insert(0, 55);
        REQUIRE(myIntVector.size() == 5);
        REQUIRE(myIntVector[0] == 55);
        REQUIRE(myIntVector[1] == 3);
        REQUIRE(myIntVector[2] == 4);
        REQUIRE(myIntVector[3] == 5);
        REQUIRE(myIntVector[4] == 10);
    }

    SECTION("insert in the middle") {
        gueepo::vector<int> myIntVector;
        myIntVector.add(3);
        myIntVector.add(4);
        myIntVector.add(5);
        myIntVector.add(10);
        myIntVector.insert(0, 55);

        myIntVector.insert(2, 23);
        REQUIRE(myIntVector.size() == 6);
        REQUIRE(myIntVector[0] == 55);
        REQUIRE(myIntVector[1] == 3);
        REQUIRE(myIntVector[2] == 23);
        REQUIRE(myIntVector[3] == 4);
        REQUIRE(myIntVector[4] == 5);
        REQUIRE(myIntVector[5] == 10);
    }
}