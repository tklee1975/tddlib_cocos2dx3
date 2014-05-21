#ifdef ENABLE_TDD
//
//  ExampleTest.m
//	TDD Framework 
//
//
#include "ExampleTest.h"
#include "TDDHelper.h"

void ExampleTest::setUp()
{
	log("TDD Setup is called");
	log("Please write somethings");
}


void ExampleTest::tearDown()
{
	log("TDD tearDown is called");
	log("Please do clean up here");
}

#pragma mark -
#pragma mark List of Sub Tests

void ExampleTest::setSubTest(Vector<MenuItem *> &menuArray)
{
	SUBTEST(ExampleTest::subTest);
}

#pragma mark -
#pragma mark Sub Test Definition
void ExampleTest::subTest(Ref *sender)
{
	log("this is a sample subTest");
}


#endif
