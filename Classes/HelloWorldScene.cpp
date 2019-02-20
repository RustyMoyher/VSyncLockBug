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
	
	int buttonSize = 50;
	auto label1 = Label::createWithTTF("Add 1", "fonts/Marker Felt.ttf", buttonSize);
	auto label10 = Label::createWithTTF("Add 10", "fonts/Marker Felt.ttf", buttonSize);
	auto label100 = Label::createWithTTF("Add 100", "fonts/Marker Felt.ttf", buttonSize);
	auto label1000 = Label::createWithTTF("Add 1000", "fonts/Marker Felt.ttf", buttonSize);
	auto labelRemove = Label::createWithTTF("Remove All", "fonts/Marker Felt.ttf", buttonSize);
	auto labelVSync = Label::createWithTTF("Toggle VSync", "fonts/Marker Felt.ttf", buttonSize);
	
	auto add1Item = MenuItemLabel::create(label1, CC_CALLBACK_0(HelloWorld::menuAdd1, this));
	auto add10Item = MenuItemLabel::create(label10, CC_CALLBACK_0(HelloWorld::menuAdd10, this));
	auto add100Item = MenuItemLabel::create(label100, CC_CALLBACK_0(HelloWorld::menuAdd100, this));
	auto add1000Item = MenuItemLabel::create(label1000, CC_CALLBACK_0(HelloWorld::menuAdd1000, this));
	auto removeAllItem = MenuItemLabel::create(labelRemove, CC_CALLBACK_0(HelloWorld::menuRemoveAll, this));
	auto toggleVSyncItem = MenuItemLabel::create(labelVSync, CC_CALLBACK_0(HelloWorld::menuToggleVSync, this));
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_0(HelloWorld::menuClose, this));
	
    auto menu = Menu::create(add1Item, add10Item, add100Item, add1000Item, removeAllItem, toggleVSyncItem, closeItem, NULL);
	menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 3) + origin);
	menu->alignItemsHorizontallyWithPadding(60);
    this->addChild(menu, 100);
	
	// Label setup
	std::string vsyncStr = vsyncEnabled ? "VSync: Enabled" : "VSync: Disabled";
	vsyncLabel = Label::createWithTTF(vsyncStr, "fonts/Marker Felt.ttf", 100);
	vsyncLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 150) + origin);
	this->addChild(vsyncLabel, 200);
	
	totalLabel = Label::createWithTTF("Objects: 0", "fonts/Marker Felt.ttf", 100);
	totalLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 280) + origin);
	this->addChild(totalLabel, 200);
	
    return true;
}

void HelloWorld::addItems(int num)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < num; i++) {
		auto sprite = Sprite::create("HelloWorld.png");
		this->addChild(sprite);
		spriteArray.pushBack(sprite);
		
		int x = cocos2d::RandomHelper::random_int(10, (int)visibleSize.width - 10);
		int y = cocos2d::RandomHelper::random_int(10, (int)visibleSize.height - 10);
		sprite->setPosition(x, y);
		
		// Helps make the text easier to read
		sprite->setColor(Color3B::BLUE);
	}
	
	totalLabel->setString("Objects: " + std::to_string(spriteArray.size()));
}

void HelloWorld::menuAdd1() { addItems(1); }
void HelloWorld::menuAdd10() { addItems(10); }
void HelloWorld::menuAdd100() { addItems(100); }
void HelloWorld::menuAdd1000() { addItems(1000); }

void HelloWorld::menuRemoveAll()
{
	int count = spriteArray.size();
	
	for (int i = 0; i < count; i++) {
		auto sprite = spriteArray.at(i);
		removeChild(sprite, true);
	}
	
	spriteArray.clear();
	totalLabel->setString("Objects: " + std::to_string(spriteArray.size()));
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

