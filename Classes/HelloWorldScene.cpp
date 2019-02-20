#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

void errorCallback(int, const char* err_str)
{
	std::cout << "GLFW Error: " << err_str << std::endl;
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	
	// Init Vsync
	vsyncEnabled = true;
	motionEnabled = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	glfwSetErrorCallback(errorCallback);
	glfwSwapInterval(1);
#endif

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
	auto labelMotion = Label::createWithTTF("Toggle Motion", "fonts/Marker Felt.ttf", buttonSize);
	auto labelFull = Label::createWithTTF("Toggle Fullscreen", "fonts/Marker Felt.ttf", buttonSize);
	
	auto add1Item = MenuItemLabel::create(label1, CC_CALLBACK_0(HelloWorld::menuAdd1, this));
	auto add10Item = MenuItemLabel::create(label10, CC_CALLBACK_0(HelloWorld::menuAdd10, this));
	auto add100Item = MenuItemLabel::create(label100, CC_CALLBACK_0(HelloWorld::menuAdd100, this));
	auto add1000Item = MenuItemLabel::create(label1000, CC_CALLBACK_0(HelloWorld::menuAdd1000, this));
	auto removeAllItem = MenuItemLabel::create(labelRemove, CC_CALLBACK_0(HelloWorld::menuRemoveAll, this));
	auto toggleVSyncItem = MenuItemLabel::create(labelVSync, CC_CALLBACK_0(HelloWorld::menuToggleVSync, this));
	auto toggleMotionItem = MenuItemLabel::create(labelMotion, CC_CALLBACK_0(HelloWorld::menuToggleMotion, this));
	auto toggleFullscreenItem = MenuItemLabel::create(labelFull, CC_CALLBACK_0(HelloWorld::menuToggleFullscreen, this));
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_0(HelloWorld::menuClose, this));
	
    auto menuTop = Menu::create(add1Item, add10Item, add100Item, add1000Item, removeAllItem, NULL);
	auto menuBottom = Menu::create(toggleVSyncItem, toggleMotionItem, toggleFullscreenItem, closeItem, NULL);
	menuTop->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 3 + 40) + origin);
	menuBottom->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 3 - 60) + origin);
	menuTop->alignItemsHorizontallyWithPadding(60);
	menuBottom->alignItemsHorizontallyWithPadding(60);
    this->addChild(menuTop, 100);
	this->addChild(menuBottom, 100);
	
	// Label setup
	std::string vsyncStr = vsyncEnabled ? "VSync: ON" : "VSync: OFF";
	vsyncLabel = Label::createWithTTF(vsyncStr, "fonts/Marker Felt.ttf", 100);
	vsyncLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 150) + origin);
	this->addChild(vsyncLabel, 200);
	
	totalLabel = Label::createWithTTF("Objects: 0", "fonts/Marker Felt.ttf", 100);
	totalLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 300) + origin);
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
		
		if (motionEnabled) moveSprite(sprite);
	}
	
	totalLabel->setString("Objects: " + std::to_string(spriteArray.size()));
}


void HelloWorld::moveSprite(Sprite *sprite)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int minX = 10;
	int maxX = visibleSize.width - 10;
	bool left = cocos2d::RandomHelper::random_int(0, 1) == 0;
	
	float time = 10.0f;
	float speed = (maxX - minX) / time;
	
	Vec2 goal = Vec2(left ? minX : maxX, sprite->getPositionY());
	float dist = sprite->getPosition().distance(goal);
	float fTime = dist / speed;
	MoveTo *moveFirst = MoveTo::create(fTime, goal);
	
	auto repeatBlock = CallFunc::create([sprite, minX, maxX, left, time]()
	{
		if (!sprite) return;
		
		auto moveLeft = MoveTo::create(time, Vec2(minX, sprite->getPositionY()));
		auto moveRight = MoveTo::create(time, Vec2(maxX, sprite->getPositionY()));
		Sequence *seq = nullptr;
		
		if (left) {
			seq = Sequence::create(moveRight, moveLeft, nullptr);
		} else {
			seq = Sequence::create(moveLeft, moveRight, nullptr);
		}
		RepeatForever *repeat = RepeatForever::create(seq);
		sprite->runAction(repeat);
	});
	
	Sequence *seq = Sequence::create(moveFirst, repeatBlock, nullptr);
	sprite->runAction(seq);
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	vsyncEnabled = !vsyncEnabled;
	if (vsyncEnabled) {
		glfwSwapInterval(1);
	} else {
		glfwSwapInterval(0);
	}
	
	std::string vsyncStr = vsyncEnabled ? "VSync: ON" : "VSync: OFF";
	vsyncLabel->setString(vsyncStr);
#endif
}

void HelloWorld::menuToggleMotion()
{
	motionEnabled = !motionEnabled;
	if (motionEnabled) {
		for (auto sprite : spriteArray) {
			moveSprite(sprite);
		}
	} else {
		for (auto sprite : spriteArray) {
			sprite->stopAllActions();
		}
	}
}

void HelloWorld::menuToggleFullscreen()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	auto glViewImpl = (GLViewImpl*)Director::getInstance()->getOpenGLView();
	if (glViewImpl->isFullscreen()) {
		auto size = glViewImpl->getDesignResolutionSize();
		glViewImpl->setWindowed(size.width, size.height);
	} else {
		glViewImpl->setFullscreen();
	}
#endif
}

void HelloWorld::menuClose()
{
	Director::getInstance()->end();
}

