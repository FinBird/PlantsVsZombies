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

class ConeDoorZombies :public CommonZombies
{
public:
	/* ����ģʽ */
	static ConeDoorZombies* getInstance();
	void CreateConeDoorZombies(Node* node, const Vec2& Position, const int& tag, const int& AnimationID, const bool& IsReadyScene = false);
	void CreateConeDoorZombiesAniamton(map<int, Global::_Zombies>::iterator iter, Node* node);
	void ZombiesKilledByCar(map<int, Global::_Zombies>::iterator iter, Node* node);

private:
	static ConeDoorZombies* _instance;

private:
	void SetShieldPrimaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                   /* ���û���һ������ */
	void SetShieldSecondaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                 /* ���û��ܶ������� */
	void SetShieldThirdInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                     /* ���û����������� */
	void SetShield1PrimaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                  /* ���û���1һ������ */
	void SetShield1SecondaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                /* ���û���1�������� */
	void SetShield1ThirdInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                    /* ���û���1�������� */
};