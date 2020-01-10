#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class CabbagePult :public Plants
{
public:
	static CabbagePult* getInstance();
	void Initialization();                                                                                                         /* ��ʼ�� */
	void CreateCabbagePultImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateCabbagePultAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateCabbagePultListener(Node* node);

public:
	/* ���Ĳ�Ͷ�ֻ������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		bool IsChanged = false;       /* �Ƿ�ı� */
		bool IsCreateCabbage = false; /* �Ƿ񴴽����Ĳ� */
		int tag;                      /* ��� */
	}_CabbagePultAnimation;
	std::map<int, _CabbagePultAnimation>CabbagePultAnimations;
	std::map<int, _CabbagePultAnimation>::iterator CabbagePultIter;

	/* ���Ĳ����� */
	typedef struct
	{
		SkeletonAnimation* CabbageBullet;   /* ͼ�� */
		int tag;                            /* ��� */
		bool IsUse;                         /* �Ƿ�ʹ�� */
		float Attack = 40;                  /* ������ */
		float PositionY;                    /* ���� */
	}_CabbageBullet;
	std::map<int, _CabbageBullet>CabbageBullet;
	std::map<int, _CabbageBullet>::iterator CabbageBulletIter;

public:
	int CabbageBulletTag = 0;               /* ���Ĳ��ӵ���� */

private:
	static CabbagePult* _instance;          /* ���� */
	Sprite* CabbagePultImage;
	Zombie* zombie = Zombie::getInstance();
	Global* global = Global::getInstance();
	 
private:

	void Update(float Time, Node* node);
	void JudgeCabbagePultAndZombiesPosition(Node* node);
	void JudgeCabbageBulletAndZombiesPosition(Node* node);                                                                                /* �㶹�뽩ʬλ���ж� */
	void CreateCabbage(const Vec2& CabbagePosition, const Vec2& ZombiesPosition, Node* node, map<int, Global::_Zombies>::iterator Iter);
	void CreateCabbageExplode(const Vec2& position, Node* node);                                                                          /* �������Ĳ˱�ը���� */
	float SetZOrder(const float& pos_y);                                                                                                  /* �����㶹���ƴ��� */
	void PlayPeaExplodeMusic(const int& MusicType);                                                                                       /* ���ž��Ĳ˱�ը���� */
};