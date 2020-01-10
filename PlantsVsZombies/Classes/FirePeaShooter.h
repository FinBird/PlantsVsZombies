#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class FirePeaShooter :public Plants
{
public:

	static FirePeaShooter* getInstance();
	void Initialization();                                                                                                         /* ��ʼ�� */
	void CreateFirePeaShooterImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateFirePeaShooterAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateFirePeaShooterListener(Node* node);

public:
	/* �㶹���ֻ������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		bool IsChanged = false;       /* �Ƿ�ı� */
		bool IsCreatePea = false;     /* �Ƿ񴴽��㶹 */
		int tag;                      /* ��� */
	}_FirePeaShooterAnimation;
	std::map<int, _FirePeaShooterAnimation>FirePeaShooterAnimations;
	std::map<int, _FirePeaShooterAnimation>::iterator FirePeaShooterIter;

	/* �㶹���� */
	typedef struct
	{
		SkeletonAnimation* Pea;       /* ���� */
		int tag;                      /* ��� */
		float Attack = 40;            /* ������ */
		bool IsUsed = false;          /* �Ƿ�ʹ�� */
	}_FirePea;
	std::map<int, _FirePea>FirePeas;
	std::map<int, _FirePea>::iterator FirePeaIter;

public:
	int FirePeaTag = 0;                  /* �㶹��� */

private:
	static FirePeaShooter* _instance;    /* ���� */
	Sprite* FirePeaShooterImage;
	Zombie* zombie = Zombie::getInstance();

private:
	void Update(float Time, Node* node);
	void CreatePea(const Vec2& position, Node* node);                                 /* �����㶹 */
	void CreatePeaExplode(const Vec2& position, Node* node, const int& ID = 0);       /* �����㶹��ը���� */
	float SetZOrder(const float& pos_y);                                              /* �����㶹���ƴ��� */

	void JudgeFirePeaShooterAndZombiesPosition(Node* node);           /* �㶹�����뽩ʬλ���ж� */
	void JudgeFirePeaAndZombiesPosition(Node* node);                  /* �㶹�뽩ʬλ���ж� */

};