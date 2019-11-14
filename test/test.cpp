//
// Created by Alex Mcbean on 13/10/2019.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE activities02_unit_test

#include <boost/test/unit_test.hpp>
#include "../binarySearchTree.h"

//TODO fix this

BOOST_AUTO_TEST_SUITE(activities02_test)

    binarySearchTree<int, std::string> newTree;

    BOOST_AUTO_TEST_CASE(lookup_null) {
        BOOST_CHECK_EQUAL(newTree.lookup(3), nullptr);
    }

    BOOST_AUTO_TEST_CASE(lookup_test){
        newTree.insert(10, "Test 10");
        newTree.insert(11, "Test 11");
        newTree.insert(2, "Test 2");
        newTree.insert(3, "Test 3");
        newTree.insert(14, "Test 14");
        BOOST_TEST (*newTree.lookup(3) == "Test 3");

    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(actitivites02_copy)
    BOOST_AUTO_TEST_CASE(deep_copy) {
        binarySearchTree<int, std::string> t1;
        t1.insert(2,"Will");
        binarySearchTree<int, std::string> t2 = t1;
        t1.insert(22,"Mary");
        t2.insert(2, "George");
        BOOST_TEST(*t1.lookup(2) == "Will");
    }

BOOST_AUTO_TEST_SUITE_END()

