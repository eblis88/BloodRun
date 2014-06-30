#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/GUIDefine.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class ModeSelect : public Scene
{
public:
	static Scene* createScene();

	ModeSelect(void);
	~ModeSelect(void);

	//virtual void onEnter();
	virtual void onExit();
	
	bool init();
	CREATE_FUNC(ModeSelect);

	void gunRushSelect(Ref* sender, Widget::TouchEventType);
	void questModeSelect(Ref* sender,Widget::TouchEventType);
	void survivalSelect(Ref* sender,Widget::TouchEventType);
	void trustBrotherSelect(Ref* sender,Widget::TouchEventType);

protected:
	Layer* m_pLayout;
};

class GunRush : public Scene
{
public:
	static Scene* createScene();
	
	bool init();
	CREATE_FUNC(GunRush);
	
	void levelSelect(Ref* sender, Widget::TouchEventType,int levelID);
protected:
	Layer* m_pLayout;
};

class QuestMode : public Scene
{
public:
	static Scene* createScene();
	
	bool init(){};
	CREATE_FUNC(QuestMode);
	
protected:
	Layer* m_pLayout;
};

class SurvivalMode : public Scene
{
public:
	static Scene* createScene();
	
	bool init(){};
	CREATE_FUNC(SurvivalMode);
	
protected:
	Layer* m_pLayout;
};


class TrustBrother : public Scene
{
public:
	static Scene* createScene();
	
	bool init(){};
	CREATE_FUNC(TrustBrother);
	
protected:
	Layer* m_pLayout;
};