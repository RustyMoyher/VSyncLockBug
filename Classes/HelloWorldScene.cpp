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
	
	// Init Vsync
	vsyncEnabled = true;
	glfwSwapInterval(1);

	// Menu setup
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto label1 = Label::createWithTTF("Add 1", "fonts/Marker Felt.ttf", 36);
	auto label10 = Label::createWithTTF("Add 10", "fonts/Marker Felt.ttf", 36);
	auto label100 = Label::createWithTTF("Add 100", "fonts/Marker Felt.ttf", 36);
	auto label1000 = Label::createWithTTF("Add 1000", "fonts/Marker Felt.ttf", 36);
	auto labelRemove = Label::createWithTTF("Remove All", "fonts/Marker Felt.ttf", 36);
	auto labelVSync = Label::createWithTTF("Toggle VSync", "fonts/Marker Felt.ttf", 36);
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_0(HelloWorld::menuClose, this));
	
	auto add1Item = MenuItemLabel::create(label1, CC_CALLBACK_0(HelloWorld::menuAdd1, this));
	auto add10Item = MenuItemLabel::create(label10, CC_CALLBACK_0(HelloWorld::menuAdd10, this));
	auto add100Item = MenuItemLabel::create(label100, CC_CALLBACK_0(HelloWorld::menuAdd100, this));
	auto add1000Item = MenuItemLabel::create(label1000, CC_CALLBACK_0(HelloWorld::menuAdd1000, this));
	auto removeAllItem = MenuItemLabel::create(labelRemove, CC_CALLBACK_0(HelloWorld::menuRemoveAll, this));
	auto toggleVSyncItem = MenuItemLabel::create(labelVSync, CC_CALLBACK_0(HelloWorld::menuToggleVSync, this));
	
    auto menu = Menu::create(add1Item, add10Item, add100Item, add1000Item, removeAllItem, toggleVSyncItem, closeItem, NULL);
	menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 3) + origin);
	menu->alignItemsHorizontallyWithPadding(50);
    this->addChild(menu, 100);
	
	// Label setup
	std::string vsyncStr = vsyncEnabled ? "VSync: Enabled" : "VSync: Disabled";
	vsyncLabel = Label::createWithTTF(vsyncStr, "fonts/Marker Felt.ttf", 60);
	vsyncLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 150) + origin);
	this->addChild(vsyncLabel, 200);
	
	totalLabel = Label::createWithTTF("Objects: 0", "fonts/Marker Felt.ttf", 60);
	totalLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 280) + origin);
	this->addChild(totalLabel, 200);
	
    return true;
}

void HelloWorld::addItems(int num)
{
	
}

void HelloWorld::menuAdd1() { addItems(1); }
void HelloWorld::menuAdd10() { addItems(10); }
void HelloWorld::menuAdd100() { addItems(100); }
void HelloWorld::menuAdd1000() { addItems(1000); }

void HelloWorld::menuRemoveAll()
{
	
}

void HelloWorld::menuToggleVSync()
{
	vsyncEnabled = !vsyncEnabled;
	int intervalInt = vsyncEnabled ? 1 : 0;
	glfwSwapInterval(intervalInt);
	std::string vsyncStr = vsyncEnabled ? "VSync: Enabled" : "VSync: Disabled";
	vsyncLabel->setString(vsyncStr);
}

void HelloWorld::menuClose()
{
	Director::getInstance()->end();
}

