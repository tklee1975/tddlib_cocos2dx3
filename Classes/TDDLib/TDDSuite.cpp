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
#include "TDDSwitch.h"

static int gTestCount = sizeof(gTestArray) / sizeof(gTestArray[0]);

#define kTestZOrder			10000
#define kLineHeight			kDefaultMenuRowHeight
#define kToolBarHeight		kDefaultToolbarHeight
#define kStatusBarHeight	30
#define kStatusBarFontSize	15

//#define kColorTestMenu		Color4B(50, 50, 100, 255)
#define kColorTestMenu		Color4B(255, 255, 255, 0)
#define kColorToolBar		Color4B(TDD_COLOR_BLUE2)

#define kColorSwitchBg				Color4B(TDD_COLOR_WHITE)
#define kColorSwitch				Color4B(TDD_COLOR_BLUE2)
#define kColorSwitchOnText			TDD_COLOR_WHITE
#define kColorSwitchOffText			TDD_COLOR_GRAY

#pragma mark -
#pragma mark Local Function
namespace {
	bool passFilter(const char *name, const char *filterPattern)
	{
		if(strlen(filterPattern) == 0) {
			return true;
		}
		
		std::string modifyName = TDDHelper::replaceString(name, "Test", "");
		

		
		return strcasestr(modifyName.c_str(), filterPattern) != NULL;
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
, mStatusLeftLabel(NULL)
, mFilterCount(0)
{
	LayerColor *bgLayer = LayerColor::create(Color4B(TDD_COLOR_WHITE2), 800, 400);
	addChild(bgLayer);

	// Top bar with: back, filter and all/history
	setupToolBar();
	
	// Menu
	setupTestMenu();

	
	// Status
	setupStatusBar();
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
	
	std::string trimPattern = TDDHelper::trimString(pattern);
	
	TDDHelper::saveFilter(trimPattern.c_str());
	
	// Director::getInstance()->popToRootScene();
	refreshTestMenu();
	
	
	updateStatusBar();
}


// Tool bar constains the following elements
//	Back button
//	Filter Input
//	Switch
Layer *TDDSuiteLayer::createToolBarLayer()
{
	Size screenSize = TDDHelper::getScreenSize();
	int midY = kToolBarHeight/2;
	
	
	int backX = 50;
	
	int inputW = 200;
	int inputH = kToolBarHeight - 10;
	int inputX = inputW / 2 + backX + 50;
	
	
	int switchW = 170;
	int switchY = 5;
	int switchX = screenSize.width - switchW - 20;
	int switchH = kToolBarHeight - switchY * 2;
	
	
	int menuW = 70;
	
	
	
	
	// Layer containter
	LayerColor *menuLayer = LayerColor::create(kColorToolBar, screenSize.width, kToolBarHeight);
	
	
	// Back Button
	Menu *menuBack = TDDHelper::createMenu(Point(backX, midY), "Back",
										   CC_CALLBACK_1(TDDSuiteLayer::goBack, this));
	
	menuLayer->addChild(menuBack);
	
	
	// Filter Input
	
	mEditFilter = TDDHelper::createEditBox(menuLayer, Point(inputX, midY), Size(inputW, inputH));
	mEditFilter->setText(TDDHelper::getFilter());
	mEditFilter->setPlaceHolder("Testcase Filter");
	mEditFilter->setDelegate(this);
	
//	Menu *menuFind = TDDHelper::createMenu(Point(findX, midY), "Find",
//										   CC_CALLBACK_1(TDDSuiteLayer::filterTest, this));
//	menuLayer->addChild(menuFind);

	// Switch
	TDDSwitch *switchControl = new TDDSwitch(Size(switchW, switchH),
											 kColorSwitchBg, kColorSwitch,
											 kColorSwitchOffText, kColorSwitchOnText,
											 TDD_FONT_NAME, TDD_FONT_SIZE1);
	
	switchControl->setPosition(Point(switchX, switchY));
	
	menuLayer->addChild(switchControl);
	
	std::vector<std::string> switches;
	switches.push_back("all");
	switches.push_back("history");
	
	switchControl->setSwitches(switches, CC_CALLBACK_3(TDDSuiteLayer::switchSelected, this));
	
	
	return menuLayer;
}


void TDDSuiteLayer::switchSelected(Ref *sender, std::string name, int selected)
{
	log("selected switch: %s (%d)", name.c_str(), selected);
}


void TDDSuiteLayer::setupToolBar()
{
	Point pos = Point(0, kToolBarHeight);
	Layer *toolBar = createToolBarLayer();
	toolBar->setPosition(Director::getInstance()->convertToGL(pos));
	this->addChild(toolBar);
}



Layer *TDDSuiteLayer::createStatusBarLayer()
{
	Size screenSize = TDDHelper::getScreenSize();
	int midY = kStatusBarHeight/2;
	int margin = 10;
	Point leftAnchor = Point(0, 0.5);
	Point rightAnchor = Point(1, 0.5);
	

	// Layer containter
	LayerColor *layer = LayerColor::create(kColorToolBar, screenSize.width, kStatusBarHeight);
	
	//
	Label *leftLabel = TDDHelper::createLabel("Left", kStatusBarFontSize, Color3B::WHITE);
	leftLabel->setAnchorPoint(leftAnchor);
	leftLabel->setPosition(Point(margin, midY));
	layer->addChild(leftLabel);
	mStatusLeftLabel = leftLabel;
	
	Label *rightLabel = TDDHelper::createLabel("Right", kStatusBarFontSize, Color3B::WHITE);
	rightLabel->setAnchorPoint(rightAnchor);
	rightLabel->setPosition(Point(screenSize.width - margin, midY));
	layer->addChild(rightLabel);
	
	// Setting Right Label
	char text[200];
	sprintf(text, "%s %s (%d)", APP_NAME, VERSION, BUILD);
	rightLabel->setString(text);

	return layer;
}

void TDDSuiteLayer::updateStatusBar()
{
	if(mStatusLeftLabel == NULL) {
		return;
	}
	
	// Setting Left Label
	char text[200];
	
	sprintf(text, "Total: %d  Filtered: %d", getTotalTestCount(), getFilteredTestCount());
	mStatusLeftLabel->setString(text);
	
}

void TDDSuiteLayer::setupStatusBar()
{
	Point pos = Point(0, 0);
	Layer *bar = createStatusBarLayer();
	bar->setPosition(pos);
	this->addChild(bar);
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
		menuItem = TDDHelper::createMenuItemWithFont(name, TDD_FONT_NAME,
										CC_CALLBACK_1(TDDSuiteLayer::menuCallback, this));
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
	
	mFilterCount = (int) selectedIndices.size();
	
	// mTestMenu->setMenuItems(menuArray);
	mTestMenu->setItemsWithColumn(menuArray);
	
	// update filter count
	updateStatusBar();
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

int TDDSuiteLayer::getTotalTestCount()
{
	return gTestCount;
}

int TDDSuiteLayer::getFilteredTestCount()
{
	return mFilterCount;
}


#endif