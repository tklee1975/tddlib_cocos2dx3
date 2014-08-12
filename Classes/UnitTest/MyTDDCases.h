//
//  MyTDDCases.h
//  Cocos2dxTDDLib
//
//	This header should be included by TDDCases.h only
//  Created by Ken Lee on 25/5/14.
//
//


// Add the Header here!
#include "SampleTest.h"
#include "ExampleTest.h"
#include "LabelTest.h"
#include "EditBoxTest.h"
#include "TDDHelperTest.h"
#include "ButtonTest.h"
#include "ScrollTest.h"
#include "TDDMenuTest.h"
#include "SwitchTest.h"
#include "TDDSwitchTest.h"
#include "TDDSuiteLayerTest.h"

//#include#
// NOTE!!! The above line is used to generate new unit test, must not be removed.

// Define
TDD_CASES
{
	TEST(TDDMenuTest),
	TEST(TDDSuiteLayerTest),
	TEST(TDDSwitchTest),
	TEST(TDDSample1),
	TEST(SwitchTest),
	TEST(ButtonTest),
	TEST(ScrollTest),
	TEST(TDDHelperTest),
	TEST(LabelTest),
	TEST(ExampleTest),
	TEST(EditBoxTest),
	TEST(ExampleTest),
	
	
//#testcase#
// NOTE!!! The above line is used to generate new unit test, must not be removed.
};


