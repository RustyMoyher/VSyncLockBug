#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
	
	bool vsyncEnabled;
	cocos2d::Label *vsyncLabel;
	cocos2d::Label *totalLabel;
	
	cocos2d::Vector<cocos2d::Sprite*> spriteArray;
	
	void addItems(int num);
	void menuAdd1();
	void menuAdd10();
	void menuAdd100();
	void menuAdd1000();
	void menuRemoveAll();
	void menuToggleVSync();
	void menuClose();
};

#endif // __HELLOWORLD_SCENE_H__
