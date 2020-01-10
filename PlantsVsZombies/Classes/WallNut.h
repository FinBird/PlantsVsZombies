#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;

class WallNut :public Plants
{
public:

	void Initialization();                                                                                                      /* ��ʼ�� */
	void CreateWallNutImage(const Vec2& position, Node* node);                                                                  /* ����ֲ��ͼƬ */
	void CreateWallNutAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);  /* ����ֲ�ﶯ�� */
	void CreateWallNutListener(Node* node);
	static WallNut* getInstance();

private:
	void Update(float Time, Node* node);
	void JudgeWallNutAndZombies(Node* node);

public:
	/* ���ǽ�������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		int skinID;                   /* Ƥ����� */
		int tag;                      /* ��� */
	}_WallNutAnimation;
	std::map<int, _WallNutAnimation>WallNutAnimations;
	std::map<int, _WallNutAnimation>::iterator WallNutIter;

private:
	static WallNut* _instance;
	Sprite* WallNutImage;
	Zombie* zombie = Zombie::getInstance();
};
