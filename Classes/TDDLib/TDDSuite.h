//
//  TTDSuite.h
//  TDDLib
//
//  Created by Ken Lee on 13/12/13.
//
//

#ifndef __TDDLib__TTDSuite__
#define __TDDLib__TTDSuite__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

USING_NS_CC;

class TDDMenu;

class TDDSuiteScene : public Scene
{
public:
	TDDSuiteScene();
    ~TDDSuiteScene();
	
	virtual void onEnter();
	virtual void onExit();
	
private:
	bool hasStat;
};

class TDDSuiteLayer : public Layer
{
public:
    TDDSuiteLayer();
    ~TDDSuiteLayer();

	void goBack(Ref *sender);
	void filterTest(Ref *sender);
	void menuCallback(Ref *sender);
	void runTest(int testIdx);
	
#pragma mark -
#pragma mark Private Data
// Private Data
private:
    Point mBeginPos;
	TDDMenu *mTestMenu;
	EditBox *mEditFilter;
	
#pragma mark -
#pragma mark Private Method
	void setupTestMenu();
	void setupToolBar();
	void refreshTestMenu();
	const char *getFilterName();
	Layer *createToolBarLayer();	// Tool Bar
	
	
};


#endif /* defined(__Dg__TTDSuite__) */
