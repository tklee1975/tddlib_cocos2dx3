//
//  TDDHelper.cpp
//  TDDLib
//
//  Created by Ken Lee on 13/12/13.
//
//

#include "TDDHelper.h"
#include "TDDSuite.h"
#include "TDDConstant.h"

//#include "GUIHelper.h"

#define kLibName			"TDDLib+cocos2dx"
#define kLibVersion			"0.1"


#ifdef ENABLE_TDD
#define HAS_TDD		true
#else
#define HAS_TDD		false
#endif

#define kTDDFilterKey	"tdd.filter.pattern"

static std::string sFilterPattern("");

Size TDDHelper::getScreenSize()
{
	auto glView = Director::getInstance()->getOpenGLView();
	return glView->getDesignResolutionSize();
}

Point TDDHelper::getAlignPoint(float x, float y, TDDAlign halign, TDDAlign valign)
{
	Size size = getScreenSize();
	
	// Horizon
	if(halign == eTDDLeft) {
		x = size.width - x;
	} else if (halign == eTDDCenter) {
		x = size.width / 2 + x;
	}
	
	log("getAlignPoint: h=%f w=%f", size.height, size.width);
	
	// Vertical
	if(valign == eTDDTop) {
		y = size.height - y;
	} else if (valign == eTDDMiddle) {
		y = size.height / 2 + y;
	}
	
	 log("getAlignPoint: x=%f y=%f", x, y);
	
	return Point(x, y);
}

void TDDHelper::showTests()
{
#ifdef ENABLE_TDD
	Scene *scene = new TDDSuiteScene();
	
	Director::getInstance()->pushScene(scene);
	
	scene->release();
#endif
}

#pragma mark - GUI Helper

MenuItem *TDDHelper::createMenuItem(const char *name, const ccMenuCallback& callback)
{
	auto label = LabelTTF::create(name, kDefaultFont, kDefaultFontSize);
	
	auto menuItem = MenuItemLabel::create(label, callback);
	
	return menuItem;
}

MenuItem *TDDHelper::createMenuItemWithFont(const char *name,
											const char *font,
											Color3B color,
											const ccMenuCallback& callback)
{
//	Label *label = Label::createWithSystemFont(value, _fontName, _fontSize);
//    if (MenuItemLabel::initWithLabel(label, callback))

	
	// LabelTTF *label = LabelTTF::create(name, kDefaultFont, kDefaultFontSize);
	Label *label = Label::createWithSystemFont(name, font, kDefaultFontSize);
	setLabelColor(label, color);
	
	return MenuItemLabel::create(label, callback);

}


MenuItem *TDDHelper::createMenuItemWithFont(const char *name, const char *font,
											const ccMenuCallback& callback)
{
	Label *label = Label::createWithSystemFont(name, font, kDefaultFontSize);
	setLabelColor(label, TDD_COLOR_BLUE2);
	
	return MenuItemLabel::create(label, callback);
}


Menu *TDDHelper::createMenu(Point pos, const char *name, const ccMenuCallback& callback)
{
	
	auto menuItem = createMenuItemWithFont(name, kDefaultFont, Color3B::WHITE, callback);
	Menu *menu = Menu::create(menuItem, NULL);
	menu->setPosition(pos);
	
	return menu;
}

void TDDHelper::addTestButton(Node *parent, Point pos)
{
	if(HAS_TDD == false) {
		log("ERROR: TDD Framework is disable!");
		return;
	}
	
	
	if(parent == NULL) {
		log("ERROR: addTestButton: parent is NULL");		// or use Assert
		return;
	}
	
	Menu *menu = createMenu(pos, "Test!", [](Ref *sender) {
												TDDHelper::showTests();
											}
							);
	
	parent->addChild(menu);
}


EditBox * TDDHelper::createEditBox(Node *parent, Point position, Size size)
{
	Scale9Sprite *bg = Scale9Sprite::create();	// empty sprite 9
	bg->addChild(LayerColor::create(Color4B::WHITE, size.width, size.height));
	
	// Add the background layer
	Point layerPos = Point(position);
	layerPos.x -= size.width / 2;
	layerPos.y -= size.height / 2;
	
	
	// Add the Edit box
	EditBox *edit = EditBox::create(size, bg);
	edit->setPosition(position);
	
	edit->setFont(TDD_FONT_NAME, TDD_EDITBOX_FONT_SIZE);
	edit->setFontColor(TDD_EDITBOX_TEXT_COLOR);
	
	if(parent != NULL) {
		parent->addChild(edit);
	}
	
	return edit;
}




void TDDHelper::scrollToTop(ScrollView *scrollView)
{
	Size containerSize = scrollView->getContainer()->getContentSize();
	
	Point offset = Point(0, -containerSize.height + scrollView->getViewSize().height);
	
	// log("containerH=%f scrollH=%f", containerSize.height, scrollView->getViewSize().height);
	
	//[scrollView setContentOffset:offset animated:NO];
	scrollView->setContentOffset(offset);
}


Point TDDHelper::getCenter(Size &parentSize, Size &nodeSize)
{
	float x = (parentSize.width - nodeSize.width) / 2;
	float y = (parentSize.height - nodeSize.height) / 2;
	
	return Point(x, y);
}

void TDDHelper::saveFilter(const char *pattern)
{
	sFilterPattern = pattern;
	
	CCUserDefault::getInstance()->setStringForKey(kTDDFilterKey, pattern);
	log("Save filter %s for key=%s", pattern, kTDDFilterKey);

	CCUserDefault::getInstance()->flush();
}

const char *TDDHelper::getFilter()
{
	sFilterPattern = CCUserDefault::getInstance()->getStringForKey(kTDDFilterKey);
	
	log("Load filter for key=%s result=%s",  kTDDFilterKey, sFilterPattern.c_str());
	
	return sFilterPattern.c_str();
}

std::string TDDHelper::getVersion()
{
	return kLibVersion;
}

std::string TDDHelper::getLibraryName()
{
	return kLibName;
}

/*
Layer *TDDHelper::createKeyPadLayer(Object *target, Control::Handler handler)
{
	Layer *layer = Layer::create();
	std::vector<Node *> nodeArray;
	
	Size size = Size(40, 40);
	Point buttonPos[4] = {
		Point(0, 40),
		Point(0, -40),
		Point(-40, 0),
		Point(40, 0),
	};
	
	ControlButton *button;
	
	button = GUIHelper::createButton("UP", target, handler, kButtonUp);
	button->setPreferredSize(size);
	button->setPosition(buttonPos[0]);
	layer->addChild(button);
	
	button = GUIHelper::createButton("DN", target, handler, kButtonDown);
	button->setPreferredSize(size);
	button->setPosition(buttonPos[1]);
	layer->addChild(button);
	
	button = GUIHelper::createButton("LT", target, handler, kButtonLeft);
	button->setPreferredSize(size);
	button->setPosition(buttonPos[2]);
	layer->addChild(button);
	
	button = GUIHelper::createButton("RT", target, handler, kButtonRight);
	button->setPreferredSize(size);
	button->setPosition(buttonPos[3]);
	layer->addChild(button);

	return layer;
} */




const Size TDDHelper::alignMenuItem(Menu *menu, int parentWidth, int numCol, int lineSpace)
{
	Vector<Node *> childrenNode = menu->getChildren();
	
	int width = parentWidth;
	int colWidth = width/numCol;
	
	int x;
	int y = 0;
	int maxH = 0;
	int spacing = lineSpace;
	int totalH = 0;
	int firstX = colWidth/2 + (numCol - 1) * colWidth;
	
	int count = (int) childrenNode.size();
	int remain = (count - 1) % numCol;
	x = remain * colWidth + colWidth/2;
	
	for(int i=(count-1); i>=0; i--) {
		Node *node = childrenNode.at(i);
		MenuItem *item = dynamic_cast<MenuItem *>(node);
		if(item == NULL) {
			continue;
		}
		
		Size itemSize = item->getContentSize();
		// log("menuItem: %f x %f", itemSize.width, itemSize.height);
		
		item->setAnchorPoint(Point(0.5, 0));
		item->setPosition(Point(x, y));
		
		// log("menuItem: %f x %f pos: x=%d y=%d", itemSize.width, itemSize.height, x, y);
		
		x -= colWidth;
		maxH = MAX(maxH, itemSize.height);
		
		if(x < 0) {
			totalH += maxH + spacing;
			y += (maxH + spacing);
			x = firstX;
		}
	}
	
	
	return Size(width, totalH);
}

void TDDHelper::setLabelColor(Label *label, const Color3B &textColor)
{
	label->setColor(textColor);
	label->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
}
