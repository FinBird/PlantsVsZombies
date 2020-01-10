#pragma once
#include "cocos2d.h"
#include "Request.h"
#include "LevelData.h"
#include "spine/spine.h"
#include "AudioEngine.h"
#include "UiImageText.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

class Zombie :public Node
{
public:
	/* ����ģʽ */
	static Zombie* getInstance();
	void CreateZombies(const Vec2& Position, Node* node, const int& tag, const int& AnimationID, const int& ZombiesTyped, const bool& IsReadyScene = false);
	void ZombiesUpdate(Node* node);
	void ErgodicZombies();
	void SetZombiesSpeed(map<int, Global::_Zombies>::iterator Iter);
	void ZombiesKilledByCar(Node* node, map<int, Global::_Zombies>::iterator Iter);
	void SetZombiesForGameType();
	void PlayZombiesDieAnimation(Node* node, map<int, Global::_Zombies>::iterator Iter, const string& name);
	int CreateZombiesForProbility(const int& ZombiesAppearFrequency);
	int CreateZombiesForNumbers(const int& ZombiesAppearFrequency);
	string ZombiesTypeAniamtion(Global::ZombiesType& zombiestype);

	~Zombie() { delete request; }

protected:
	float SetZOrder(const float& pos_y);
	virtual void SetZombiesPrimaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                                                        /* ���ý�ʬһ������ */
	virtual void SetZombiesSecondaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node);                                                      /* ���ý�ʬ�������� */
	virtual void ZombiesLoseArmAnimation(map<int, Global::_Zombies>::iterator iter, Node* node, const string& name);                                    /* ��ʬ���첲���� */
	virtual void ZombiesLoseHeadAnimation(map<int, Global::_Zombies>::iterator iter, Node* node, const string& name);                                   /* ��ʬ��ͷ���� */
	virtual void ZombiesLoseShieldAnimation(map<int, Global::_Zombies>::iterator iter, Node* node, const string& name);                                 /* ��ʬ�����ܶ��� */
	virtual void ZombiesBodyAnimation(map<int, Global::_Zombies>::iterator iter, Node* node, const string& name);                                       /* ��ʬ������䶯�� */

protected:
	Global* global = Global::getInstance();

private:
	void Update(float Time, Node* node);
	void JudgeGameTypeForZombies(Sprite* sprite);

private:
	static Zombie* _instance;
	Request* request = new Request();
	OpenLevelData* LevelData = OpenLevelData::getInstance();

	float ZombiesSpeed[10] = { 35,30,30,30,30,30,30,40 };

};