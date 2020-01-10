#pragma once
#include "Plants.h"
#include "Zombies.h"
#include "cocos2d.h"
#include "spine/spine.h"
#include "AudioEngine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

class SunFlower :public Plants
{
public:

	void Initialization();                                                                                                           /* ��ʼ�� */
	void CreateSunFlowerImage(const Vec2& position, Node* node);                                                                     /* ����ֲ��ͼƬ */
	void CreateSunFlowerAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag);     /* ����ֲ�ﶯ�� */
	void CreateSunListener(Node* node);                                                                                              /* ����������� */
	void ShowSunNumbers(Node* node);                                                                                                 /* ��ʾ������ */
	void ShowCoinNumbers(Node* node);                                                                                                /* ��ʾ����� */
	void RandomCreateSuns(Node* node);                                                                                               /* ����������� */
	void RandomCreateCoins(Node* node, const Vec2& position);                                                                        /* ���������� */
	void SunNumberTextRunAction(Node* node);                                                                                         /* ��������ɫ�仯 */
	void UpdateSunNumbers(Node* node = nullptr);                                                                                     /* ���������� */
	void UpdateCoinNumbers(Node* node);                                                                                              /* ���½���� */

	/* ����ģʽ */
	static SunFlower* getInstance();

private:
	void Update(float Time, Node* node);                                                                   /* ���������� */
	void CreateSun(Node* node, SkeletonAnimation* animation, const Vec2& position, const int& ID);
	void RemoveSunCallBack(Node* node, Node* node1, const int& tag);                                       /* ɾ������ص����� */
	void JudgeSunFlowerAndZombies(Node* node);                                                             /* �ж����տ��뽩ʬ */
	
public:
	
	/* ���տ��������� */
	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		float BloodVolume = 300;      /* Ѫ�� */
		Vec2 position;                /* λ�� */
		Vec2 RowAndColumn;            /* ��ϸ��ַ���� */
		int tag;                      /* ��� */
	}_SunFlowerAnimation;
	std::map<int, _SunFlowerAnimation>SunFlowerAnimations;
	std::map<int, _SunFlowerAnimation>::iterator SunflowerIter;

	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		bool IsUsed = false;          /* �Ƿ�ʹ�� */
	}_Suns;
	std::map<int, _Suns> Suns;                        /* ����洢 */
	std::map<int, _Suns>::iterator SunsIter;

	typedef struct
	{
		SkeletonAnimation* Animation; /* ���� */
		bool IsUsed = false;          /* �Ƿ�ʹ�� */
	}_Coins;
	std::list<_Coins> Coins;                          /* ��Ҵ洢 */
	std::list<_Coins>::iterator CoinIter;

public:
	int suntag = 0;                                   /* ̫����� */
	int cointag = 10000;                              /* ���ұ�� */

private:
	static SunFlower* _instance;
	Sprite* SunFlowerImage;
	ui::Text* SunNumbersText;
	ui::Text* CoinNumbersText;
	Zombie* zombie = Zombie::getInstance();

};
