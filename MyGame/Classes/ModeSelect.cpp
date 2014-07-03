#include "ModeSelect.h"
#include "HelloWorldScene.h"
#include "DataDictionary.h"

using namespace cocostudio;
using namespace cocos2d;
using namespace ui;

ModeSelect::ModeSelect(void)
{
	Scene::init();
}


ModeSelect::~ModeSelect(void)
{
}


Scene* ModeSelect::createScene()
{
	auto scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  

    // 'layer' is an autorelease object
    auto layer = ModeSelect::create();
	scene->addChild(layer);
	return scene;
}

Scene* GunRush::createScene()
{
	auto scene = Scene::create();
    auto layer = GunRush::create();
	scene->addChild(layer);
	return scene;
}

Scene* QuestMode::createScene()
{
	auto scene = Scene::create();
    auto layer = GunRush::create();
	scene->addChild(layer);
	return scene;
}

Scene* SurvivalMode::createScene()
{
	auto scene = Scene::create();
    auto layer = GunRush::create();
	scene->addChild(layer);
	return scene;
}

Scene* TrustBrother::createScene()
{
	auto scene = Scene::create();
    auto layer = GunRush::create();
	scene->addChild(layer);
	return scene;
}

bool ModeSelect::init()
{
     m_pLayout = Layer::create();
    addChild(m_pLayout);

    auto _widget = GUIReader::getInstance()->widgetFromJsonFile("LevelSelect.json");
	m_pLayout->addChild(_widget);
    
	Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _widget->getSize();
    m_pLayout->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));

	Button* bt1 = dynamic_cast<Button*>(_widget->getChildByName("Gun Rush"));
    bt1->addTouchEventListener(CC_CALLBACK_2(ModeSelect::gunRushSelect, this));
        
    Button* bt2 = dynamic_cast<Button*>(_widget->getChildByName("Quest"));
    bt2->addTouchEventListener(CC_CALLBACK_2(ModeSelect::questModeSelect, this));
        
    Button* bt3 = dynamic_cast<Button*>(_widget->getChildByName("Survival"));
    bt3->addTouchEventListener(CC_CALLBACK_2(ModeSelect::survivalSelect, this));

	Button* bt4 = dynamic_cast<Button*>(_widget->getChildByName("Trust Brother"));
    bt4->addTouchEventListener(CC_CALLBACK_2(ModeSelect::trustBrotherSelect, this));

	return true;
}

bool GunRush::init()
{
	m_pLayout = Layer::create();
    addChild(m_pLayout);

    auto _widget = GUIReader::getInstance()->widgetFromJsonFile("GunRush.json");
	m_pLayout->addChild(_widget);
    
	Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _widget->getSize();
    m_pLayout->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));

	char button_name[20];

	auto doc = DataDictionary::Instance()->getDoc("level.json");

	for (int row = 1; row <= 2; row++)
	{
		for (int col = 1; col <= 4; col++)
		{
			sprintf(button_name, "Button_%d_%d", row, col);
			Button* button = dynamic_cast<Button*>(_widget->getChildByName(button_name));
			button->addTouchEventListener(CC_CALLBACK_2(GunRush::levelSelect, this,  (row-1)*4+col));
			string name = (*doc)[(row-1)*4+col-1]["name"].GetString();
			button->setTitleText(name);
		}
	}

	return true;
}

void GunRush::levelSelect(Ref* sender, Widget::TouchEventType touchType, int levelID)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}


//退出场景函数，用于清理资源
//void ModeSelect::onExit()
//{
//    //m_pUILayer->removeFromParent();
//     
//    //SceneReader::sharedSceneReader()->purge();
//    //GUIReader::shareReader()->purge();
//    //ActionManager::shareManager()->purge();
//     
//    CCScene::onExit();
//}
////关闭按钮的回调函数
//void ModeSelect::menuCloseCallback(CCObject* pSender, TouchEventType type)
//{    //判断触摸事件的类型，如果是TOUCH_EVENT_ENDED触摸结束就关闭当前程序
//    if (type == TOUCH_EVENT_ENDED)
//    {    
//        //调用Director的结束方法
//        CCDirector::sharedDirector()->end();
//        //判断系统平台是否是ios平台，如果是则调用exit（0）方法，该方法是ios系统专用的退出函数。
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//        exit(0);
//#endif
//    }
//}

void ModeSelect::gunRushSelect(Ref* sender,Widget::TouchEventType type)
{
	Director::getInstance()->replaceScene(GunRush::createScene());
}
void ModeSelect::questModeSelect(Ref* sender, Widget::TouchEventType type)
{
	Director::getInstance()->replaceScene(QuestMode::createScene());
}
void ModeSelect::survivalSelect(Ref* sender, Widget::TouchEventType type)
{
	Director::getInstance()->replaceScene(SurvivalMode::createScene());
}
void ModeSelect::trustBrotherSelect(Ref* sender, Widget::TouchEventType type)
{
	Director::getInstance()->replaceScene(TrustBrother::createScene());
}