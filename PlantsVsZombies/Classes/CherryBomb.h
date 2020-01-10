#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class CherryBomb:public Plants
{
public:

	void Initialization();                                                                                                         /* ��ʼ�� */
	void CreateCherryBombImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateCherryBombAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateCherryBombListener(Node* node);
	static CherryBomb* getInstance();

public:

	/* ӣ��ը���������� */
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
	}_CherryBombAnimation;
	std::map<int, _CherryBombAnimation>CherryBombAnimation;
	std::map<int, _CherryBombAnimation>::iterator CherryBombIter;

	std::list<int>CherryBombReady;

private:
	static CherryBomb* _instance;    /* ���� */
	Sprite* CherryBombImage;
	Zombie* zombie = Zombie::getInstance();

private:
	int SetZorder(const float& position);                                                            /* ������ͼ˳�� */
	void Update(float Time, Node* node);
	void UpdateCherryBombReady();                                                                    /* ����ӣ��ը��׼�� */
	void JudgeCherryBombAndZombiesPosition(Node* node);                                              /* ӣ��ը���뽩ʬλ���ж� */
	void PlayCherryBombExplode(Node* node, map<int, _CherryBombAnimation>::iterator CherryBombIter); /* ����ӣ��ը����ը���� */
	void CherryBombExplodeKillZombies(Node* node, 
		map<int, _CherryBombAnimation>::iterator CherryBombIter, 
		map<int, Global::_Zombies>::iterator Iter);                                                  /* �ж�ӣ��ը��ɱ����ʬ */
};