#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class Jalapeno :public Plants
{
public:
	static Jalapeno* getInstance();
	void Initialization();                                                                                                         /* ��ʼ�� */
	void CreateJalapenoImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateJalapenoAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateJalapenoListener(Node* node);

public:

	/* �������������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		int ExplosiveDamage;          /* ��ը�˺� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		bool IsReadyExplode;          /* �Ƿ�׼����ը */
		bool IsExplode;               /* �Ƿ�ը */
		int tag;                      /* ��� */
	}_JalapenoAnimation;
	std::map<int, _JalapenoAnimation>JalapenoAnimation;
	std::map<int, _JalapenoAnimation>::iterator JalapenoIter;

	std::list<int>JalapenoReady;

private:
	static Jalapeno* _instance;    /* ���� */
	Sprite* JalapenoImage;
	Zombie* zombie = Zombie::getInstance();

private:
	int SetZorder(const float& position);                                                            /* ������ͼ˳�� */
	void Update(float Time, Node* node);
	void UpdateJalapenoReady();                                                                      /* ����ӣ��ը��׼�� */
	void JudgeJalapenoAndZombiesPosition(Node* node);                                                /* �������뽩ʬλ���ж� */
	void PlayJalapenoExplode(Node* node, map<int, _JalapenoAnimation>::iterator JalapenoIter);       /* ���Ż�������ը���� */
	void JalapenoExplodeKillZombies(Node* node,
		map<int, _JalapenoAnimation>::iterator JalapenoIter,
		map<int, Global::_Zombies>::iterator Iter);                                                  /* �жϻ�����ɱ����ʬ */
};