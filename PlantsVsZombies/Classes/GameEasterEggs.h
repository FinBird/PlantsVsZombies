#pragma once
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "GlobalVariable.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

using namespace cocos2d;
using namespace cocos2d::experimental;

class GameEasterEggs :public Scene
{
public:
	static Scene* createScene();             /* �������� */
	virtual bool init();                     /* ��ʼ�� */
	CREATE_FUNC(GameEasterEggs);

private:
	Global* global = Global::getInstance();
};