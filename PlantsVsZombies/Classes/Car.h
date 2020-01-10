#pragma once
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class Car
{
public:
	static Car* getInstance();
	void Initialization();                                        /* ��ʼ�� */
	void CreateCarAnimation(Node* node, const Vec2& position);
	void CreateCarListener(Node* node);
	float SetZOrder(const float& pos_y);                          /* ����С�����ƴ��� */

	/* С���������� */
	typedef struct
	{
		Sprite* Image;                /* ���� */
		Vec2 position;                /* λ�� */
		bool IsLive;                  /* �Ƿ񼤻� */
		int AnimationID;              /* ����ID */
		int tag;                      /* ��� */
	}_Car;
	std::map<int, _Car>Cars;
	std::map<int, _Car>::iterator cariter;

private:
	static Car* _instance;           /* ���� */
	Global* global = Global::getInstance();

private:
	void Update(float Time, Node* node);
	void JudgeCarAndZombies(Node* node);
	void CarMove(Node* node);
};