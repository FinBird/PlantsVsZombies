#pragma once
#include "cocos2d.h"
#include "spine/spine.h"
#include "AudioEngine.h"
#include "CommonZombies.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

class ConeZombies :public CommonZombies
{
public:
	/* ����ģʽ */
	static ConeZombies* getInstance();
	void CreateConeZombiesAniamton(map<int, Global::_Zombies>::iterator Iter, Node* node);
	void CreateConeZombies(Node* node, const Vec2& Position, const int& AnimationID, const int& tag);
	void ZombiesKilledByCar(map<int, Global::_Zombies>::iterator iter, Node* node);

private:
	static ConeZombies* _instance;

private:
	void SetShieldPrimaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                  /* ���û���һ������ */
	void SetShieldSecondaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                /* ���û��ܶ������� */
	void SetShieldThirdInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                    /* ���û����������� */
};