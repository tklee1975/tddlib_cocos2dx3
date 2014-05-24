TDDLib on cocos2d-x
================

(This README is composed in http://dillinger.io/)

A Test Driven Development Framework for cocos2d-x 3.0 final. 
It helps building unit tests with cocos2d-x 3.0.

## Feature

* Create Tests
* Create sub tests for one Test
* Filter test by keyword

## Project Structure

* /script : The script to create a new test 
* /Classes : The example project source 
* /Classes/TDDLib : The TDDLib library source
* /Classes/UnitTest : Example Unit test


## How to setup in your project

### 1. Download the Library project 

The project library can be downloaded at https://github.com/tklee1975/tddlib_cocos2dx3; You can use download as ZIP or clone the project

### 2. Add the library to your project

After download the project, you will the project structure mentioned in last section. Copy the Library source code to your cocos2dx project. For my preference, I will copy to a folder named "Library" under my Classes folder.

Then add the 'TDDLib' folder to the Xcode. 


### 3. Add the script to your project

Besides source code, there are some scripts that help to make the UnitTest classes. 

### 4. Set the MACRO 'ENABLE_TDD'

As we don't want to let the unit test stuff affect the size of the release build, all the UnitTest code and most of the library are enclosed by the 'ENABLE_TDD' macro. The test will not be included if 'ENABLE_TDD' isn't defined. 

To turn the test code on, we need add the Marcro "ENABLE_TDD" definition to the compile setting. 

### 5. Add the Test Button

Unlike the way of most unit test framework, TDDLib will build with the main code; Thus, the unit tests are linked with the main code in Test build version. 

The way to do so is that add "test" button is placed on the Main View (e.g title scene or main scene) of the game. 

The code sample is: 

<pre>
TDDHelper::addTestButton(this, Point(visibleSize.width/2, 50)); 
</pre>

## How to add a new test

(note: we will use ExampleTest as the example of the new UnitTest)

### 1. Run the 'createTest' script 

* Go to the main folder e.g MyProject/
* Run the createTest.sh script  
 <pre>
 ./script/createTest.sh Example
 </pre>
  noted that the following files will be generated.

  - MyProject/Classes/UnitTest/ExampleTest.h
  - MyProject/Classes/UnitTest/ExampleTest.cpp


### 2. Add the new test class

* Add the new UnitTest header and source files to XCode
* For my preference, I will place them in a group called 'UnitTest'.

### 3. Add an entry in TDDCases.h

* The above steps are make the Unit Test code available, this step is to make the test code visible in the test menu.
* To do so, need to add some codes in TDDCases.h

 * Add the header file of new Unit Test. e.g <code>#include "ExampleTest.h"</code>
 * Add an entry in gTestArray, e.g <code>ADD_CASE(ExampleTest)</code>
  
* When it is done, the TDDCases.h will be shown like the following code sample:

<pre>
#include "SampleTest.h"
#include "ExampleTest.h" 
// 
#define ADD_CASE(__ClassName__) {#__ClassName__, []() { return new __ClassName__(); } }
// Define
TDDTestCase gTestArray[] =
{
	ADD_CASE(TDDTest),
	ADD_CASE(TDDSample1),
	ADD_CASE(ExampleTest),
};
</pre>
 
 

### 4. Build and Run 
* Build (Cmd+B) and Run (Cmd + R) in Xcode. 


### 5. Adding test code
* If the unit test is successfully added. you can place your test code inside.

#### 5.1 Using the sub test

Every Unit Test is designed to contain many sub tests to be invoked. Just add the sub test method and add the entry in the setSubTest method. 

The code sample are as follows:

* Add the sub test method 

<pre>
void ExampleTest::testSomethingNew(Ref *sender)
{
	log("testSomethingNew");
}
</pre>

* Add the entry in setSubTest method

<pre>
void ExampleTest::setSubTest(Vector<MenuItem *> &menuArray)
{
	SUBTEST(ExampleTest::testSomethingNew);
	SUBTEST(ExampleTest::testSprite);
}
</pre>


#### 5.2 Override the Unit Test content

Every Unit Test Class (TDDTest) is the sub class of Scene. So it can do everything you expect to be done in Scene. But the different is that TDDTest will run 'setUp' after the Scene is loaded and 'tearDown' below the Scene is removed. 

So, we can setup a custom testing UI at the setUp logic to fit the test environment we needed.

(note: build an example in the future)

## Future Development
* Document:
    * Tutorial #1: Setup TDDLib
    * Tutorial #2: Very simple unit test
* Feature: 
    * Test Filtering in the Test Menu 
    * More compact subtest menu
    * Remmber the test filtering keyword
    * Clear the current filtering keyword
* Sample Code
    * Custom Test UI. e.g particle test with setting sliders

## Help! I need somebody help! 
### Call for users
* I am the only user of this project now;
* As more users, more suggestions come and the framework will evolve faster and better.
* Users help to discover bugs and bad UX (User Experience).
* Users may drive me to work. (This is my pet project after work, so I will be lazy ....) 

### Call for Developers
* It would be fun if more people get involved in the development.
* You can help to code review so that the code can be more concise and easy to understand.

### Improvement on the document. 
* I am not an native english person. Thus, my grammer and explanation are not good enough to help users understand the detail.
* I am really weak in technical writing >.< !










