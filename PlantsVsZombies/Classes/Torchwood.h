#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "PeaShooter.h"
#include "spine/spine.h"
#include "FirePeaShooter.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class Torchwood :public Plants
{
public:
	void Initialization();                                                                                                        /* ��ʼ�� */
	void CreateTorchwoodImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateTorchwoodAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateTorchwoodListener(Node* node);
	static Torchwood* getInstance();

public:
	/* �����׮�������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		int tag;                      /* ��� */
	}_TorchwoodAnimation;
	std::map<int, _TorchwoodAnimation>TorchwoodAnimation;
	std::map<int, _TorchwoodAnimation>::iterator TorchwoIter;

private:
	static Torchwood* _instance;    /* ���� */
	Sprite* TorchwoodImage;
	PeaShooter* PeaShooters = PeaShooter::getInstance();
	FirePeaShooter* FirePeaShooters = FirePeaShooter::getInstance();
	Zombie* zombie = Zombie::getInstance();

private:
	void Update(float Time, Node* node);
	void JudgeTorchwoodAndZombiesPosition(Node* node); /* ��ʬ������׮λ���ж� */
	void JudgeTorchwoodAndPeaPosition(Node* node);     /* �㶹������׮λ���ж� */
};