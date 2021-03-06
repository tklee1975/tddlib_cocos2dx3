#ifdef ENABLE_TDD
//
//  TDDHelperTest.m
//	TDD Framework 
//
//
#include "TDDHelperTest.h"
#include "TDDHelper.h"
#include "TDDConstant.h"

void TDDHelperTest::setUp()
{
	log("TDD Setup is called");
	log("Please write somethings");
}


void TDDHelperTest::tearDown()
{
	log("TDD tearDown is called");
	log("Please do clean up here");
}

#pragma mark -
#pragma mark List of Sub Tests

void TDDHelperTest::setSubTest(Vector<MenuItem *> &menuArray)
{
	SUBTEST(TDDHelperTest::testColor);
	SUBTEST(TDDHelperTest::testMenuItemFont);
	SUBTEST(TDDHelperTest::testAlignMenuItem);
	SUBTEST(TDDHelperTest::testCreateEditBox);
}

#pragma mark -
#pragma mark Helper Method
Menu *TDDHelperTest::createMenu(int numitem)
{
	Vector<MenuItem*> menuItems;
	
	for(int i=0; i<numitem; i++) {
		char temp[100];
		sprintf(temp, "Item %d", i);
		
		
	    MenuItem *item = MenuItemFont::create(temp, NULL);
		menuItems.pushBack(item);
		
		Size itemSize = item->getContentSize();
		//log("menuItem.size=%f,%f", itemSize.width, itemSize.height);
	}
	
	
	return Menu::createWithArray(menuItems);
}

Menu *TDDHelperTest::createMenuWithFont(int numitem, const char *font, int fontSize, const Color3B &color)
{
	Vector<MenuItem*> menuItems;
	
	MenuItemFont::setFontName(font);
	MenuItemFont::setFontSize(fontSize);
	
	
	for(int i=0; i<numitem; i++) {
		char temp[100];
		sprintf(temp, "Item %d", i);
		
		
	    MenuItem *item = MenuItemFont::create(temp, NULL);
		menuItems.pushBack(item);
		
		Size itemSize = item->getContentSize();
		//log("menuItem.size=%f,%f", itemSize.width, itemSize.height);
	}
	
	for(int i=0; i<menuItems.size(); i++) {
		MenuItem *item = menuItems.at(i);
		item->setColor(color);
	}
	
	
	return Menu::createWithArray(menuItems);
}

#pragma mark -
#pragma mark Sub Test Definition
void TDDHelperTest::testCreateEditBox(Ref *sender)
{
	log("testCreateEditBox");
	
	Point pos = Point(50, 100);
	Size size = Size(200, 60);
	
	EditBox *edit = TDDHelper::createEditBox(this, pos, size);
	edit->setAnchorPoint(Point(0, 0));
	edit->setText("Testing!!!");
}



void TDDHelperTest::testAlignMenuItem(Ref *sender)
{
	int numCol = 3;
	int count = 100;
	Menu *menu = createMenu(count);
	menu->setPosition(Point(0, 0));

	
	int width = 500;
	Size menuSize = TDDHelper::alignMenuItem(menu, width, numCol);

	//LayerColor *colorLayer = LayerColor::create(Color4B::GRAY, menuSize.width, menuSize.height);
	// colorLayer->addChild(menu);

	Node *containerLayer = menu;
	
	
	ScrollView *scrollView = ScrollView::create(Size(width, 200));
	scrollView->setPosition(Point(50, 50));
	
	scrollView->setContainer(containerLayer);
	scrollView->setContentSize(menuSize);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	//
	
	addChild(scrollView, 0, 100);
	

}


void TDDHelperTest::testMenuItemFont(Ref *sender)
{
	int numCol = 3;
	int count = 100;
	Menu *menu = createMenuWithFont(count, "GillSans", 20, Color3B::YELLOW);

	menu->setPosition(Point(50, 50));
	
	int width = 500;

	TDDHelper::alignMenuItem(menu, width, numCol);
	
	addChild(menu, 0, 100);
	
	
}



void TDDHelperTest::testColor(Ref *sender)
{
	LayerColor *layer;
	float width = 100;
	float height = 100;
	float x = 5;
	float y = 50;
	
	const int numColor = 5;
	Color3B colors[numColor] = {
		TDD_COLOR_BLACK,
		TDD_COLOR_WHITE,
		TDD_COLOR_BLUE1,
		TDD_COLOR_BLUE2,
		TDD_COLOR_GREEN1,
	};
	
	// layer = LayerColor::create
	
	for(int i=0; i<numColor; i++) {
		Color3B color3B = colors[i];
		Color4B color = Color4B(color3B);
		
		layer = LayerColor::create(color, width, height);
		layer->setPosition(x, y);
		addChild(layer);
		
		x += width;
	}
}

#endif
