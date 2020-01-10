#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class Spikeweed :public Plants
{
public:
	void Initialization();                                                                                                        /* ��ʼ�� */
	void CreateSpikeweedImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateSpikeweedAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateSpikeweedListener(Node* node);
	static Spikeweed* getInstance();

public:
	/* �ش̻������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		bool IsChanged = false;       /* �Ƿ�ı� */
		bool IsHaveZombies = false;   /* �Ƿ��н�ʬ */
		bool IsAttack = true;         /* �Ƿ񹥻� */
		int tag;                      /* ��� */
		int Attack = 20;              /* ������ */
	}_SpikeweedAnimation;
	std::map<int, _SpikeweedAnimation>SpikeweedAnimation;
	std::map<int, _SpikeweedAnimation>::iterator SpikeweedIter;

private:
	static Spikeweed* _instance;    /* ���� */
	Sprite* SpikeweedImage;
	Zombie* zombie = Zombie::getInstance();

private:
	void Update(float Time, Node* node);
	void JudgePeaShooterAndZombiesPosition(Node* node);           /* �ش��뽩ʬλ���ж� */
	void PlayAttractMusic(const int& MusicType);               /* ���ŵش̹������� */
};