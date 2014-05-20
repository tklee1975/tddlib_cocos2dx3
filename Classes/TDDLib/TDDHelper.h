//
//  TDDHelper.h
//  TDDLib
//
//  Created by Ken Lee on 13/12/13.
//
//

#ifndef __TDDLib__TDDHelper__
#define __TDDLib__TDDHelper__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "TDDTypes.h"
#include <string>
#include <vector>

#define kButtonUp		1
#define kButtonDown		2
#define kButtonLeft		3
#define kButtonRight	4

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

class TDDHelper
{
public:
	static std::string getVersion();
	static std::string getLibraryName();
	
	static Size getScreenSize();
	static Point getAlignPoint(float x, float y, TDDAlign halign, TDDAlign valign);
	
	static void showTests();
	static void addTestButton(Node *parent, cocos2d::Point pos);
	static Menu *createMenu(cocos2d::Point pos, const char *name, const ccMenuCallback& callback);
	static MenuItem *createMenuItem(const char *name, const ccMenuCallback& callback);
	static void scrollToTop(ScrollView *scrollView);
	static Point getCenter(Size &parentSize, Size &nodeSize);
	static EditBox *createEditBox(Node *parent, Point position, Size size);
	static void saveFilter(const char *pattern);
	static const char *getFilter();
	
	// static Layer *createKeyPadLayer(Object *target, Control::Handler handler);
};

#endif /* defined(__Dg__TDDHelper__) */
