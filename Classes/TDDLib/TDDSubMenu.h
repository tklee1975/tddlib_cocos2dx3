//
//  TDDSubMenu.h
//  Cocos2dxTDDLib
//
//  Created by Ken Lee on 5/9/14.
//
//

#ifndef __Cocos2dxTDDLib__TDDSubMenu__
#define __Cocos2dxTDDLib__TDDSubMenu__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include <string>
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;

#define kDefaultHeaderColor			Color4B(0, 0, 0, 100)
#define kDefaultBodyColor			Color4B(50, 50, 50, 160)

class TDDSubMenu : public LayerColor
{
public:
	TDDSubMenu(const Size &size,
			   const Color4B &headerColor = kDefaultHeaderColor,
			   const Color4B &bodyColor = kDefaultBodyColor,
			   const Color3B &textColor = Color3B::WHITE,
			   const std::string font = "arial",
			   const int fontSize = 15);
	
	~TDDSubMenu();
	
private:
	void setupHeader(const Color4B &headerColor);
};


#endif /* defined(__Cocos2dxTDDLib__TDDSubMenu__) */
