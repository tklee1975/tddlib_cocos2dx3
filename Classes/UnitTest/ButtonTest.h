#ifdef ENABLE_TDD
//
//  ButtonTest.h
//
//
#ifndef __TDD_ButtonTest__
#define __TDD_ButtonTest__

// Include Header

#include "TDDTest.h"

// Class Declaration 
class ButtonTest : public TDDTest
{
protected:
	virtual void setUp();
	virtual void tearDown();
	virtual void setSubTest(Vector<MenuItem *> &menuArray);
	
	
	const Size alignMenuItem(Menu *menu);
private:
	Menu *createMenu(int numitem);
	
	void onMenuSelected(Ref *sender);
	void testMenuLayout(Ref *sender);
	void testMenuStyle(Ref *sender);
	void testAlighColumn(Ref *sender);
	void testAlignItems(Ref *sender);
	void testAlignItemsWithScroll(Ref *sender);
}; 

#endif

#endif
