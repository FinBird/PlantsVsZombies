#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class PotatoMine :public Plants
{
public:
	static PotatoMine* getInstance();
	void Initialization();                                                                                                         /* ��ʼ�� */
	void CreatePotatoMineImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreatePotatoMineAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreatePotatoMineListener(Node* node);

public:
	/* �����׻������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		bool IsReady = false;         /* �Ƿ�׼���� */
		bool IsExplode = false;       /* �Ƿ�ը */
		bool IsFirst = false;         /* �Ƿ��һ�� */
		int ExplosiveDamage;          /* �����ױ�ը�˺� */
		int RecordSecond;             /* ��¼���� */
		int BreakGround;              /* ����ʱ�� */
		int tag;                      /* ��� */
	}_PotatoMineAnimation;
	std::map<int, _PotatoMineAnimation>PotatoMineAnimations;
	std::map<int, _PotatoMineAnimation>::iterator PotatoMineIter;

public:
	static PotatoMine* _instance;    /* ���� */
	Sprite* PotatoMineImage;

private:
	void Update(float Time, Node* node);
	void UpdatePotateMine(float time);
	void JudgePeaShooterAndZombiesPosition(Node* node);                                                                                        /* �������뽩ʬλ���ж� */
	void PotatoMineExplodeKillZombies(Node* node, map<int, _PotatoMineAnimation>::iterator PotatoMineIter);                                    /* �����ױ�ը��ɱ��ʬ */
	void StrikeFlyZombies(Node* node, const string& NameHead = "");
};