#pragma once
#include "cocos2d.h"
#include "json/writer.h"
#include "json/document.h"
#include "json/stringbuffer.h"

using namespace cocos2d;
using namespace rapidjson;

class OpenLevelData
{
public:
	/* ����ģʽ */
	static OpenLevelData* getInstance();
	void OpenLevelsData(const std::string& worlddata);
	void ReadLevelData(char* LevelName);
	void Decrypt(char* cSrc, char* cDest);                              /* ���ܺ��� */

private:
	typedef struct
	{
		int x, y;
	}_MyPoint;

public:
	enum  GameTypes
	{
		CreateWall,
		AtLeastSunNumbers,
		FlowerPosition,
		CarNumbers,
		UserPlantsNumbers,
		ZombiesInvisible,
		SmallZombies,
		BigZombies,
		NoPlants
	};

	typedef struct
	{
		bool IsEncryption;                                              /* �Ƿ���� */
		bool ZombiesIsVisible = false;                                  /* ��ʬ�Ƿ����� */
		bool ZombiesIsSmall = false;                                    /* �Ƿ���С��ʬ */
		bool ZombiesIsBig = false;                                      /* �Ƿ��Ǿ��˽�ʬ */
		bool IsNoPlants = false;                                        /* �Ƿ񲻿���ֲ */
		int ZombiesFrequency;                                           /* ��ʬ�ܲ��� */
		int CoinNumbers;                                                /* ����� */
		int AtLeastSunNumbers = -1;                                     /* ���ٲ����������� */
		int FlowerPosition;                                             /* ��̳λ�� */
		int CarNumbers;                                                 /* С������ */
		int UsePlantsNumbers;                                           /* ʹ��ֲ������ */
		float UserLose;                                                 /* ���ʧ�� */
		std::vector<int>GameType;                                       /* ��Ϸ���� */
		std::vector<int>ZombiesType;                                    /* ��ʬ���� */
		std::vector<int>ZombiesNumbers;                                 /* ��ʬ�� */
		std::vector<int>MunchZombiesFrequency;                          /* �ཀྵʬ���� */
		std::vector<std::vector<int> >ZombiesTypeProbabilityFrequency;  /* ÿһ��ÿ�ֽ�ʬ���ֵĸ��� */
		std::vector<_MyPoint>NoPlantsPosition;                          /* ��������ֲ�ĵط� */
		int FirstFrequencyTime;                                         /* ��һ����ʬ����ʱ�� */
	}_LevelData;
	_LevelData LevelData;

private:
	static OpenLevelData* _instance;
	Document document;

	void SetInit();
};