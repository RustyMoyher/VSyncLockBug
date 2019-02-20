#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	// Basic Menu setup
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
	float y = origin.y + closeItem->getContentSize().height/2;
	closeItem->setPosition(Vec2(x,y));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
	// Vsync code
	vsyncLabel = Label::createWithTTF("Vsync: ", "fonts/Marker Felt.ttf", 24);
	vsyncLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 100));
	//vsyncLabel->setPosition(160, 160 - 10);
	this->addChild(vsyncLabel, 2);
	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
