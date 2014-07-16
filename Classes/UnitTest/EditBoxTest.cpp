#ifdef ENABLE_TDD
//
//  EditBoxTest.m
//	TDD Framework 
//
//
#include "EditBoxTest.h"
#include "TDDHelper.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

void EditBoxTest::setUp()
{
	log("TDD Setup is called");
	log("Please write somethings");
}


void EditBoxTest::tearDown()
{
	log("TDD tearDown is called");
	log("Please do clean up here");
}

#pragma mark -
#pragma mark List of Sub Tests

void EditBoxTest::setSubTest(Vector<MenuItem *> &menuArray)
{
	SUBTEST(EditBoxTest::testEditBoxStyle);
	SUBTEST(EditBoxTest::testEditBox);
	SUBTEST(EditBoxTest::testDelegate);
}

#pragma mark -
#pragma mark Sub Test Definition
void EditBoxTest::testEditBox(Ref *sender)
{
	log("testEditBox");
//	EditBox::cr
	Scale9Sprite *bg = Scale9Sprite::create();
	//const Size& size, Scale9Sprite* pNormal9SpriteBg, Scale9Sprite* pPressed9SpriteBg/* = NULL*/, Scale9Sprite* pDisabled9SpriteBg/* = NULL*/)
	EditBox *edit = EditBox::create(Size(200, 60), bg, NULL, NULL);
	edit->setText("testing");
	edit->setPosition(Point(100, 100));
	addChild(edit);
}

void EditBoxTest::testEditBoxStyle(Ref *sender)
{
	log("testEditBox");
	//	EditBox::cr
	Scale9Sprite *bg = Scale9Sprite::create();
	bg->addChild(LayerColor::create(Color4B::WHITE, 200, 60));
	
	//const Size& size, Scale9Sprite* pNormal9SpriteBg, Scale9Sprite* pPressed9SpriteBg/* = NULL*/, Scale9Sprite* pDisabled9SpriteBg/* = NULL*/)
	EditBox *edit = EditBox::create(Size(200, 60), bg, NULL, NULL);
	edit->setText("testing");
	edit->setPosition(Point(200, 100));
	edit->setFont("GillSans", 15);
	edit->setFontColor(Color3B::BLACK);
	
	addChild(edit);
}

void EditBoxTest::testDelegate(Ref *sender)
{
	log("testEditBox");
	//	EditBox::cr
	Scale9Sprite *bg = Scale9Sprite::create();
	bg->addChild(LayerColor::create(Color4B::WHITE, 200, 60));
	
	//const Size& size, Scale9Sprite* pNormal9SpriteBg, Scale9Sprite* pPressed9SpriteBg/* = NULL*/, Scale9Sprite* pDisabled9SpriteBg/* = NULL*/)
	EditBox *edit = EditBox::create(Size(200, 60), bg, NULL, NULL);
	edit->setText("testing");
	edit->setPosition(Point(200, 100));
	edit->setFont("GillSans", 15);
	edit->setFontColor(Color3B::BLACK);
	edit->setDelegate(this);
	
	addChild(edit);
}

void EditBoxTest::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
	log("editBox edit begin");
}
void EditBoxTest::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
	log("editBox edit end");
}
void EditBoxTest::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
	log("editBox change to [%s]", text.c_str());
}
void EditBoxTest::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	log("editBox edit return hit");
}

#endif
