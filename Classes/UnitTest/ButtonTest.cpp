#ifdef ENABLE_TDD
//
//  ButtonTest.m
//	TDD Framework 
//
//
#include "ButtonTest.h"
#include "TDDHelper.h"

void ButtonTest::setUp()
{
	log("TDD Setup is called");
	log("Please write somethings");
}


void ButtonTest::tearDown()
{
	log("TDD tearDown is called");
	log("Please do clean up here");
}

#pragma mark -
#pragma mark List of Sub Tests

void ButtonTest::setSubTest(Vector<MenuItem *> &menuArray)
{
	SUBTEST(ButtonTest::testAlignItemsWithScroll);
	SUBTEST(ButtonTest::testAlignItems);
	SUBTEST(ButtonTest::testMenuLayout);
	SUBTEST(ButtonTest::testMenuStyle);
	SUBTEST(ButtonTest::testAlighColumn);
	SUBTEST(ButtonTest::testControlButton);
}

void ButtonTest::onMenuSelected(Ref *sender)
{
	log("menuItem is selected");
}

#pragma mark -
#pragma mark Helper 
Menu *ButtonTest::createMenu(int numitem)
{
	Vector<MenuItem*> menuItems;
	
	for(int i=0; i<numitem; i++) {
		char temp[100];
		sprintf(temp, "Item %d", i);
		
		
	    MenuItem *item = MenuItemFont::create(temp, CC_CALLBACK_1(ButtonTest::onMenuSelected, this));
		menuItems.pushBack(item);
		
		Size itemSize = item->getContentSize();
		//log("menuItem.size=%f,%f", itemSize.width, itemSize.height);
	}
	
	
	return Menu::createWithArray(menuItems);
}

#pragma mark -
#pragma mark Sub Test Definition
void ButtonTest::testMenuLayout(Ref *sender)
{
	log("testMenu");
	int count = 20;
	
	Vector<MenuItem*> menuItems;
	
	for(int i=0; i<count; i++) {
		char temp[100];
		sprintf(temp, "Item %d", i);
		

	    auto item = MenuItemFont::create(temp, CC_CALLBACK_1(ButtonTest::onMenuSelected, this));
		menuItems.pushBack(item);
	}

	
	auto menu = Menu::createWithArray(menuItems);
	
	auto s = Director::getInstance()->getWinSize();
	menu->setPosition(Point(s.width/2, s.height/2));
	
	//
	menu->alignItemsInColumns(5, 5, 5, 5, NULL);

	menu->setAnchorPoint(Point(0, 0));
	//	ONE ROW
	// menu->alignItemsHorizontallyWithPadding(40);
	
	addChild(menu, 0, 100);
}



void ButtonTest::testMenuStyle(Ref *sender)
{
	log("testMenu");
	int count = 20;
	
	Vector<MenuItem*> menuItems;
	
	MenuItemFont::setFontName("GillSans");
	MenuItemFont::setFontSize(22);
	
	for(int i=0; i<count; i++) {
		char temp[100];
		sprintf(temp, "Item %d", i);
		
		
	    auto item = MenuItemFont::create(temp, CC_CALLBACK_1(ButtonTest::onMenuSelected, this));
		menuItems.pushBack(item);
	}
	
	
	auto menu = Menu::createWithArray(menuItems);
	
	auto s = Director::getInstance()->getWinSize();
	menu->setPosition(Point(s.width/2, s.height/2));
	
	//
	menu->alignItemsInColumns(5, 5, 5, 5, NULL);
	
	menu->setAnchorPoint(Point(0, 0));
	//	ONE ROW
	// menu->alignItemsHorizontallyWithPadding(40);
	
	addChild(menu, 0, 100);
}

void defineColumnsVector(ValueVector &vector, int count, int numCol)
{
	int remain = count;
	while(remain > 0) {
		int col = MIN(remain, numCol);
	
		vector.push_back(Value(col));
		
		remain -= numCol;
	}
}

void ButtonTest::testAlighColumn(Ref *sender)
{
	int numCol = 3;
	int count = 100;
	Menu *menu = createMenu(count);
	
	Size menuSize = menu->getContentSize();	// always 710 x 400
	
	ValueVector rowsSetting;
	defineColumnsVector(rowsSetting, count, numCol);
	
	menu->alignItemsInColumnsWithArray(rowsSetting);

	addChild(menu, 0, 100);
	
	log("menuSize: %f x %f", menuSize.width, menuSize.height);
}

const Size ButtonTest::alignMenuItem(Menu *menu)
{
	Vector<Node *> childrenNode = menu->getChildren();
	
	int width = 500;
	int numCol = 3;
	int colWidth = width/numCol;
	
	int x = 0;
	int y = 0;
	int maxH = 0;
	int spacing = 20;
	int totalH = 0;
	int firstX = (numCol - 1) * colWidth;
	
	int count = (int) childrenNode.size();
	int remain = (count - 1) % numCol;
	x = remain * colWidth;
	
	for(int i=(count-1); i>=0; i--) {
		Node *node = childrenNode.at(i);
		MenuItem *item = dynamic_cast<MenuItem *>(node);
		if(item == NULL) {
			continue;
		}
		
		Size itemSize = item->getContentSize();
		log("menuItem: %f x %f", itemSize.width, itemSize.height);
		
		item->setAnchorPoint(Point(0, 0));
		item->setPosition(Point(x, y));
		
		log("menuItem: %f x %f pos: x=%d y=%d", itemSize.width, itemSize.height, x, y);
		
		x -= colWidth;
		maxH = MAX(maxH, itemSize.height);
		
		if(x < 0) {
			totalH += maxH + spacing;
			y += (maxH + spacing);
			x = firstX;
		}
	}
	
	log("totalH=%d", totalH);
	
	return Size(width, totalH);
}

void ButtonTest::testAlignItems(Ref *sender)
{
	int numCol = 3;
	int count = 100;
	Menu *menu = createMenu(count);
	
//	Size menuSize = menu->getContentSize();	// always 710 x 400
//	
//	ValueVector rowsSetting;
//	defineColumnsVector(rowsSetting, count, numCol);
//	
////	menu->alignItemsInColumnsWithArray(rowsSetting);
	
	
	Size menuSize = alignMenuItem(menu);
	menu->setPosition(Point(0, 200));
//	
//	//
//	ScrollView *scrollView = ScrollView::create(Size(500, 200));
//	scrollView->setPosition(Point(50, 50));
//	
//	scrollView->setContainer(menu);
//	scrollView->setContentSize(menuSize);
//	scrollView->setDirection(ScrollView::Direction::VERTICAL);
//
	
	addChild(menu, 0, 100);
	
	log("menuSize: %f x %f", menuSize.width, menuSize.height);
}

void ButtonTest::testAlignItemsWithScroll(Ref *sender)
{
	int numCol = 3;
	int count = 100;
	Menu *menu = createMenu(count);
	
	Size menuSize = alignMenuItem(menu);
	menu->setPosition(Point(0, 0));

	ScrollView *scrollView = ScrollView::create(Size(500, 200));
	scrollView->setPosition(Point(50, 50));
	
	scrollView->setContainer(menu);
	scrollView->setContentSize(menuSize);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	//
	
	addChild(scrollView, 0, 100);
	
	log("menuSize: %f x %f", menuSize.width, menuSize.height);
}

void ButtonTest::testControlButton(Ref *sender)
{
	log("Testing controlButton");
	
	Point buttonPos = Point(50, 200);

	Scale9Sprite *bgButton = Scale9Sprite::create();
	// bgButton->addChild(LayerColor::create(Color4B::WHITE, 80, 30));
	
	Scale9Sprite *bgHiliButton = Scale9Sprite::create();
	Scale9Sprite *bgSelected = Scale9Sprite::create();
	
	// bgButton->setContentSize(Size(200, 50));
	Label *titleButton = Label::createWithSystemFont("test", "arial", 15);
	titleButton->setColor(Color3B::BLUE);

	ControlButton *button = ControlButton::create(titleButton, bgButton);
	button->setBackgroundSpriteForState(bgHiliButton, Control::State::HIGH_LIGHTED);
	button->setTitleColorForState(Color3B::WHITE, Control::State::HIGH_LIGHTED);
	button->setBackgroundSpriteForState(bgSelected, Control::State::SELECTED);
	button->setTitleColorForState(Color3B::RED, Control::State::SELECTED);
	
	
	
	// ((Label *)button->getTitleLabel())->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
	TDDHelper::setAlphaPremultiplied(button->getTitleLabel());

	button->setContentSize(Size(80, 30));
	button->setPosition(buttonPos);
	button->addTargetWithActionForControlEvents(this,
				cccontrol_selector(ButtonTest::touchUpInsideAction), Control::EventType::TOUCH_UP_INSIDE);
	
	addChild(button);
	
	button->setSelected(false);
	
	
	LayerColor *hotspot = LayerColor::create(Color4B::RED, 4, 4);
	hotspot->setPosition(Point(buttonPos.x - 2, buttonPos.y - 2));
	addChild(hotspot);
}

void ButtonTest::touchUpInsideAction(Ref *sender, Control::EventType controlEvent)
{
	ControlButton *button = (ControlButton *)sender;
	
	log("Button is clicked");
	if(button->isSelected()) {
		button->setHighlighted(false);
		button->setSelected(false);
	} else {
		button->setSelected(true);
		button->setHighlighted(true);
	}
	// button->setColor(Color3B::RED);
   //  _displayValueLabel->setString(String::createWithFormat("Touch Up Inside.")->getCString());
}

#endif
