#ifdef ENABLE_TDD
//
//  TDDSubMenu.cpp
//  Cocos2dxTDDLib
//
//  Created by Ken Lee on 5/9/14.
//
//

#include "TDDSubMenu.h"



TDDSubMenu::TDDSubMenu(const Size &size,
					   const Color4B &headerColor,
					   const Color4B &bodyColor,
					   const Color3B &textColor,
					   const std::string font,
					   const int fontSize)
{
	TDDSubMenu::initWithColor(bodyColor, size.width, size.height);
	
	// Add the header
	setupHeader(headerColor);
}

void TDDSubMenu::setupHeader(const Color4B &headerColor)
{
	GLfloat parentH = this->getContentSize().height;
	GLfloat width = this->getContentSize().width;
	GLfloat height = 30;
	
	LayerColor *headerLayer = LayerColor::create(headerColor, width, height);
	Point pos = Point(0, parentH - height);
	headerLayer->setPosition(pos);
	this->addChild(headerLayer);
}

//: mSwitchBg(NULL)
//, mSelected(-1)
//, mCallback(NULL)
//, mBgColor(bgColor)
//, mSwitchColor(switchColor)
//, mOffTextColor(offTextColor)
//, mOnTextColor(onTextColor)
//, mFont(font)
//, mFontSize(fontSize)
//, mEnableCallback(false)
//{
//	TDDSwitch::initWithColor(bgColor, size.width, size.height);
//	
//	//
//	// Switch Button Background
//	
//}


TDDSubMenu::~TDDSubMenu()
{
}



// Only for TDDLib
#endif