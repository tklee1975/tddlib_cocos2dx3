//
//  TTDSuite.cpp
//  TDDLib
//
//  Created by Ken Lee on 13/12/13.
//
//

#ifdef ENABLE_TDD

#include "TDDSuite.h"
#include "TDDTypes.h"
#include "TDDCases.h"
#include "TDDHelper.h"
#include "TDDMenu.h"
#include "TDDConstant.h"

static int gTestCount = sizeof(gTestArray) / sizeof(gTestArray[0]);

#define kTestZOrder			10000
#define kLineHeight			kDefaultMenuRowHeight
#define kToolBarHeight		kDefaultToolbarHeight

//#define kColorTestMenu		Color4B(50, 50, 100, 255)
#define kColorTestMenu		Color4B(255, 255, 255, 255)
#define kColorToolBar		Color4B(TDD_COLOR_BLUE2)

#pragma mark -
#pragma mark Local Function
namespace {
	bool passFilter(const char *name, const char *filterPattern)
	{
		if(strlen(filterPattern) == 0) {
			return true;
		}
		
		return strcasestr(name, filterPattern) != NULL;
	}
}

#pragma mark -
#pragma mark TDDSuiteScene
TDDSuiteScene::TDDSuiteScene()
{
	
}

TDDSuiteScene::~TDDSuiteScene()
{
	
}

void TDDSuiteScene::onEnter()
{
	log("TDDSuiteScene: onEnter");

	Scene::onEnter();
	
	log("TDDSuiteScene: onEnter is called");
	
	TDDSuiteLayer *layer = new TDDSuiteLayer();
	addChild(layer);
	layer->release();
	
	// Save the stat setting and then turn off
	hasStat = Director::getInstance()->isDisplayStats();
	Director::getInstance()->setDisplayStats(false);
	
}

void TDDSuiteScene::onExit()
{
	log("TDDSuiteScene: onExit");
	this->removeAllChildren();
	
	Director::getInstance()->setDisplayStats(hasStat);
	Scene::onExit();
}


#pragma mark -
#pragma mark TDDSuiteLayer

TDDSuiteLayer::TDDSuiteLayer()
: mEditFilter(NULL)
{
	LayerColor *bgLayer = LayerColor::create(Color4B::WHITE, 800, 400);
	addChild(bgLayer);
	
	setupTestMenu();
	setupToolBar();
	
	
}

TDDSuiteLayer::~TDDSuiteLayer()
{
	
}


void TDDSuiteLayer::goBack(Ref * sender)
{
	log("goback to main");
	Director::getInstance()->popToRootScene();
}

void TDDSuiteLayer::filterTest(Ref * sender)
{
	log("filterTest");
	
	const char *pattern = (mEditFilter == NULL) ? "" : mEditFilter->getText();
	
	TDDHelper::saveFilter(pattern);
	
	// Director::getInstance()->popToRootScene();
	refreshTestMenu();
}



Layer *TDDSuiteLayer::createToolBarLayer()
{
	Size screenSize = TDDHelper::getScreenSize();
	int midY = kToolBarHeight/2;
	int inputW = 140;
	int menuW = 70;
	
	int backX = 40;
	
	int findX  = screenSize.width - menuW/2;
	int inputH = kToolBarHeight - 10;
	int inputX = findX - 10 - menuW / 2  - inputW / 2;
	
	
	
	
	LayerColor *menuLayer = LayerColor::create(kColorToolBar, screenSize.width, kToolBarHeight);
	
	Menu *menuBack = TDDHelper::createMenu(Point(backX, midY), "Back",
										   CC_CALLBACK_1(TDDSuiteLayer::goBack, this));
	
	menuLayer->addChild(menuBack);
	
	
	
	mEditFilter = TDDHelper::createEditBox(menuLayer, Point(inputX, midY), Size(inputW, inputH));
	mEditFilter->setText(TDDHelper::getFilter());
	mEditFilter->setDelegate(this);
	
	Menu *menuFind = TDDHelper::createMenu(Point(findX, midY), "Find",
										   CC_CALLBACK_1(TDDSuiteLayer::filterTest, this));
	
	menuLayer->addChild(menuFind);
	
	return menuLayer;
}

void TDDSuiteLayer::setupToolBar()
{
	Point pos = Point(0, kToolBarHeight);
	Layer *toolBar = createToolBarLayer();
	toolBar->setPosition(Director::getInstance()->convertToGL(pos));
	this->addChild(toolBar);
}

void TDDSuiteLayer::setupTestMenu()
{
	Size screenSize = TDDHelper::getScreenSize();
	Size menuSize = Size(screenSize.width, screenSize.height - kToolBarHeight);

	
	TDDMenu *menu = new TDDMenu(menuSize, kColorTestMenu, kLineHeight);
	this->addChild(menu);
	menu->release();
	
	// Set to the class variable
	mTestMenu = menu;
	
	// Refresh Menu Data
	refreshTestMenu();
}

const char *TDDSuiteLayer::getFilterName()
{
	return TDDHelper::getFilter();
}

void TDDSuiteLayer::createMenuItemArray(const std::vector<int> &testIndices, Vector<MenuItem *> &menuArray)
{
	MenuItemFont::setFontName("GillSans");
	MenuItemFont::setFontSize(22);
	
	MenuItem *menuItem;
	for(int i=0; i<testIndices.size(); i++) {
		int index = testIndices.at(i);
		
		const char *name = gTestArray[index].name;
		
		//menuItem = TDDHelper::createMenuItem(name, CC_CALLBACK_1(TDDSuiteLayer::menuCallback, this));
		menuItem = TDDHelper::createMenuItemWithFont(name, "GillSans", CC_CALLBACK_1(TDDSuiteLayer::menuCallback, this));
		menuItem->setTag(index);	// this must be the index of the test in the gTestArray
		
		menuArray.pushBack(menuItem);
	}
}

void TDDSuiteLayer::refreshTestMenu()
{
	//Array *menuArray = Array::createWithCapacity(gTestCount);
	Vector<MenuItem *> menuArray;
	
	
	// TODO: Filtering !!!!
	const char *filterPattern = getFilterName();
	
	std::vector<int> selectedIndices;
	for (int i = 0; i < gTestCount; i++)
	{
		const char *name = gTestArray[i].name;
		if(passFilter(name, filterPattern) == false) {
			continue;
		}

		selectedIndices.push_back(i);
	}
	
	createMenuItemArray(selectedIndices, menuArray);
	
	// mTestMenu->setMenuItems(menuArray);
	mTestMenu->setItemsWithColumn(menuArray);
}

#pragma mark -
#pragma mark EditBoxDelegate
void TDDSuiteLayer::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("editBox change to [%s]", text.c_str());
	
	filterTest(NULL);
}

void TDDSuiteLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	
}

void TDDSuiteLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	
}

void TDDSuiteLayer::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	
}


#pragma mark -
#pragma mark Test Action Handling
void TDDSuiteLayer::runTest(int testIdx)
{
	
	if(testIdx < 0 || testIdx >= gTestCount) {
		log("ERROR: TDDSuteLayer.runTest: invalid index=%d", testIdx);
		return;
	}
	
	// create the test scene and run it
    auto scene = gTestArray[testIdx].callback();
	if (scene)
    {
		Director::getInstance()->pushScene(scene);
        scene->release();
    }
}

void TDDSuiteLayer::menuCallback(Ref * sender)
{
	log("menuCallback: is called");
	MenuItem *item = dynamic_cast<MenuItem *>(sender);
	
	log("item tag=%d", item->getTag());
	runTest(item->getTag());
	
}



#endif