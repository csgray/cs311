// skiplist_test_suites.cpp
// Corey S. Gray
// 2 Dec 2017
//
// For CS 311 Fall 2017
// Tests for class Cuber: test suites
// For Assignment 8, Exercise B
// Uses the "Catch" unit-testing framework
// Requires skiplist_test_main.cpp, catch.hpp, skiplist.h

// Includes for code to be tested
#include "skiplist.h"         // For class Cuber
#include "skiplist.h"         // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
// Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE("SkipList Invariants",
	"[invariants]")
{
	SECTION("New empty list.")
	{
		SkipList testList = SkipList();
		{
			INFO("Head is as close to negative infinity as possible.");
			REQUIRE(testList._head->_value == std::numeric_limits<int>::min());
		}
		{
			INFO("Head is as close to positive infinity as possible.");
			REQUIRE(testList._tail->_value == std::numeric_limits<int>::max());
		}
		{
			INFO("Head is linked to tail.");
			REQUIRE(testList._head->_right == testList._tail);
		}
		{
			INFO("Tail is linked to head.");
			REQUIRE(testList._tail->_left == testList._head);
		}
		{
			INFO("List has height 1.");
			REQUIRE(testList._height == 1);
		}
	}

	SECTION("Insert one item.")
	{
		SkipList testList = SkipList();
		testList.insert(0);
		testList.print();
	}

	SECTION("Insert 10 items.")
	{
		SkipList testList = SkipList();
		testList.insert(0);
		testList.insert(-37);
		testList.insert(42);
		testList.insert(178);
		testList.insert(91);
		testList.insert(-9999);
		testList.insert(777);
		testList.insert(9999);
		testList.insert(3);
		testList.insert(400);
		testList.print();
	}
}
