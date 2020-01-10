#pragma once
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "AudioEngine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

class LmpZombies :public Zombie
{
public:
	/* ����ģʽ */
	static LmpZombies* getInstance();
	void CreateLmpZombies(Node* node, const Vec2& Position, const int& tag, const int& AnimationID, const bool& IsReadyScene = false);
	void CreateLmpZombiesAniamton(map<int, Global::_Zombies>::iterator iter, Node* node);
	void ZombiesKilledByCar(map<int, Global::_Zombies>::iterator iter, Node* node);

private:
	static LmpZombies* _instance;

private:
	virtual void SetZombiesPrimaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                                  /* ���ý�ʬһ������ */
    virtual void SetZombiesSecondaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                                /* ���ý�ʬ�������� */
};