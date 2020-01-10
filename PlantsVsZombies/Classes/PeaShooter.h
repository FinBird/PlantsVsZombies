#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class PeaShooter :public Plants
{
public:

	void Initialization();                                                                                                         /* ��ʼ�� */
	void CreatePeaShooterImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreatePeaShooterAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreatePeaShooterListener(Node* node);
	static PeaShooter* getInstance();

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
	}_PeaShooterAnimation;
	std::map<int, _PeaShooterAnimation>PeaShooterAnimations;
	std::map<int, _PeaShooterAnimation>::iterator iter;

	/* �㶹���� */
	typedef struct
	{
		SkeletonAnimation* Pea;       /* ���� */
		int tag;                      /* ��� */
		int FireNumbers = 0;          /* ȼ�մ��� */
		int TorchwoodTag = 0;         /* �����׮��� */
		float Attack = 20;            /* ������ */
		bool IsUsed = false;          /* �Ƿ�ʹ�� */
		bool IsFire = false;          /* �Ƿ�ȼ�� */
	}_Pea;
	std::map<int, _Pea>Peas;
	std::map<int, _Pea>::iterator PeaIter;

public:
	int PeaTag = 0;                  /* �㶹��� */

private:
	static PeaShooter* _instance;    /* ���� */
	Sprite* PeaShooterImage;
	Zombie* zombie = Zombie::getInstance();

private:
	void Update(float Time,Node* node);
	void CreatePea(const Vec2& position, Node* node);                                 /* �����㶹 */
	void CreatePeaExplode(const Vec2& position, Node* node, const int& ID = 0);       /* �����㶹��ը���� */
	float SetZOrder(const float& pos_y);                                              /* �����㶹���ƴ��� */

	void PlayPeaExplodeMusic(const int& MusicType);               /* �����㶹��ը���� */
	void JudgePeaShooterAndZombiesPosition(Node* node);           /* �㶹�����뽩ʬλ���ж� */
	void JudgePeaAndZombiesPosition(Node* node);                  /* �㶹�뽩ʬλ���ж� */

};
