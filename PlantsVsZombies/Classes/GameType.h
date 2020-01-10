#pragma once
#include "cocos2d.h"
#include "UserLose.h"
#include "LevelData.h"
#include "GlobalVariable.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

using namespace cocos2d;

class GameType
{
public:
	/* ����ģʽ */
	static GameType* getInstance();

	void CreateGameType(Node* node);                                  /* ������Ϸ���� */
	void Initialization();                                            /* ��ʼ�� */
	void UpdateRequirementNumbers(Node* node,const std::string name); /* �������� */
	void WaringPlantsNull();                                          /* ����ֲ��ʹ���� */
	//void JudgeZombiesWin(map<int, Global::_Zombies>::iterator Iter);

public:
	typedef struct
	{
		ui::Text* AllSunNumbersText;                 /* ��ʾ�������� */
		int AtLeastSunNumbers;                       /* ������Ҫ�������� */
		int AllSunNumbers = 0;                       /* ������ */
		bool IsHaveSunNumberRequriement = false;     /* �Ƿ�������Ҫ�� */
		bool IsUpdateImage = false;                  /* ͼƬ�Ƿ���� */
	}_SunNumberRequriement;
	_SunNumberRequriement SunNumberRequriement;

	typedef struct
	{
		ui::Text* PalntsNumbersText;                 /* ��ʾֲ������ */
		int UserPlantsNumbers = -1;                  /* ����ʹ�õ�ֲ������ */
		int SurPlusPlantsNumbers = -1;               /* ʣ��ֲ������ */
		bool IsHavePlantsRequriement = false;        /* �Ƿ���ֲ��Ҫ�� */
		bool IsUpdateImage = false;                  /* ͼƬ�Ƿ���� */
	}_PlantsRequriement;
	_PlantsRequriement PlantsRequriement;

private:
	static GameType* _instance;
	Global* global = Global::getInstance();
	void ShowNumbers(Node* node, const int& ID);     /* ��ʾ���� */
	void UpdateNumbers(Node* node, const int& ID);   /* �������� */
};