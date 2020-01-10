#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class Garlic :public Plants
{
public:
	static Garlic* getInstance();
	void Initialization();                                                                                                         /* ��ʼ�� */
	void CreateGarlicImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateGarlicAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateGarlicListener(Node* node);
	
public:
	/* ����������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		int EatNumbers = 10;          /* ���ԵĴ��� */
		int SumEatNumbers = 10;       /* ���Ա��ԵĴ��� */
		float BloodVolume = 200000;   /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		int tag;                      /* ��� */
		int AnimationID = 0;          /* ������� */
	}_GarlicAnimation;
	std::map<int, _GarlicAnimation>GarlicAnimations;
	std::map<int, _GarlicAnimation>::iterator GarlicIter;

private:
	static Garlic* _instance;    /* ���� */
	Sprite* GarlicImage;
	Zombie* zombie = Zombie::getInstance();

private:
	void Update(float Time, Node* node);
	void JudgeGarlicAndZombiesPosition(Node* node);           /* �����뽩ʬλ���ж� */
};