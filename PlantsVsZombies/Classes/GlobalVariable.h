#pragma once
#include <map>
#include <list>
#include "AudioEngine.h"
#include "spine/spine.h"
#include "ui/CocosGUI.h"
#include "spine\spine-cocos2dx.h"

using namespace std;
using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

class Global
{
public:
	static Global* getInstance();
	int changeBgMusic(const std::string& _musicName,bool _loop);

public:
	/* ������Ч���� */
	struct Global_Music
	{
		float SoundEffect = 1;             /* ��Ч */
		float BackGroundMusicVolume = 0.5f;
		list<int>BackGroundMusic;          /* ���� */
	};
	Global_Music GlobalMusic;

	/* ���ò��� */
	struct Global_Parameter
	{
		ui::CheckBox::EventType Global_Information = ui::CheckBox::EventType::SELECTED;
		ui::CheckBox::EventType Global_HighFPS = ui::CheckBox::EventType::UNSELECTED;
		ui::CheckBox::EventType Global_FullScreen = ui::CheckBox::EventType::UNSELECTED;
		ui::CheckBox::EventType Global_CursorNotHide = ui::CheckBox::EventType::UNSELECTED;
		ui::CheckBox::EventType Global_StretchingShow = ui::CheckBox::EventType::SELECTED;
	};
	Global_Parameter GlobalParameter;

	/* �û����� */
	struct User
	{
		std::string UserName = "��ŭ��С��ʬ"; /* �û����� */
		bool IsUpdate = false;
		std::string UserCaveFileName[8];
		std::string UserCaveFileNameKey[8] =
		{ {"USERNAMEDATA"},
		{"USERNAMEDATA_2"},
		{"USERNAMEDATA_3"},
		{"USERNAMEDATA_4"},
		{"USERNAMEDATA_5"},
		{"USERNAMEDATA_6"},
		{"USERNAMEDATA_7"},
		{"USERNAMEDATA_8"} };
	};
	User UserData;

	/* �û�ѡ��Ŀ��ƴ洢 */
	typedef struct
	{
		int CardNumbers = 0;  /* ��Ƭ���� */
		int CardID[10];       /* ��Ƭ���� */
	}userselectcard;
	userselectcard UserSelectCard;

	/* ����ö�� */
	enum class _BackGroundImageName
	{
		Mordern = 0,
		DarkAges = 1,
		NeonMixtapeTour = 2,
		FrostibiteCaves = 3
	};
	_BackGroundImageName BackGroundImageName;

	/* ��ʬ���� */
	enum class ZombiesType
	{
		CommonZombies = 1,
		ConeZombies,
		BucketZombies,
		CommonDoorZombies,
		ConeDoorZombies,
		BucketDoorZombies,
		LmpZombies
	}; 
	
	/* ��ʬ�洢�ṹ�� */
	typedef struct
	{
		SkeletonAnimation* ZombiesAnimation;   /* ���� */
		ZombiesType ZombiesType;               /* ��ʬ���� */
		int MusicType;                         /* �������� */
		int AnimationID;                       /* ��������ID */
		int Tag;                               /* ��� */
		float _BloodVolume;                    /* Ѫ�� */
		float _ShieldVolume;                   /* ����Ѫ�� */
		float _ShieldVolume1;                  /* ����1Ѫ�� */
		float BloodVolume;                     /* Ѫ�� */
		float ShieldVolume;                    /* ����Ѫ�� */
		float ShieldVolume1;                   /* ����1Ѫ�� */
		float Speed;                           /* �ƶ��ٶ� */
		float CaveSpeed;                       /* �洢�ƶ��ٶ� */
		bool IsUseForGameType = false;         /* �Ƿ�ʹ������Ϸ���� */
		bool IsHaveShield;                     /* �Ƿ��л��� */
		bool IsEat;                            /* �Ƿ��ڳ�ֲ�� */
		bool IsEatGarlic = false;              /* �Ƿ�Դ��� */
		bool IsShow = false;                   /* �Ƿ����� */
		bool IsCanDelete[2] = { false };       /* �Ƿ����ɾ�� */
	}_Zombies;

	map<int, _Zombies>Zombies;
	map<int, _Zombies>::iterator Iter;

	/* ��Ϸ��ͼ */
	typedef struct
	{
		int PlantsMap[5][9];      /* ֲ����ֲ��ͼ */
		int RowNumbers;           /* ���� */
		int ColumnNumbers;        /* ���� */
	}_MapSize;
	_MapSize MapSize;

	/* ��ǰ���� */
	typedef struct
	{
		int Levels = 1;  /* ��ǰ���� */
		bool IsBeginShowEggs = false;
	}_NowLevels;
	_NowLevels NowLevels[5];

	/* ��ǰ��Ĺ��������� */
	typedef struct
	{
		Sprite* background;                              /* ��ǰ�����ͼ */
		char PlayWorldName[128];                         /* ��ǰ�������� */
		int PlayLevels = 1;                              /* ��ǰ���� */
		int PlayWorlds = 1;                              /* ��ǰ���� */
		bool IsReadWoldInformation[13] = { false };      /* �Ƿ��ȡ������Ϣ */
	}_NowPlayLevels;
	_NowPlayLevels NowPlayLevels;

	/* �û���Ϸ���� */
	typedef struct
	{
		int KillAllZombies = 0;    /* ɱ����ʬ���� */
		int UsePlantsNumbers = 0;  /* ʹ��ֲ������ */
		int BreakThrough = 0;      /* ����ʧ�ܴ��� */
		int UserDataNumber = -1;   /* �û���Ϸ�浵��� */
		string UserDataName[8] =   /* �û��浵���� */
		{ {"WORLD_1_LEVELS"},
		{"WORLD_1_LEVELS_2"},
		{"WORLD_1_LEVELS_3"},
		{"WORLD_1_LEVELS_4"},
		{"WORLD_1_LEVELS_5"},
		{"WORLD_1_LEVELS_6"},
		{"WORLD_1_LEVELS_7"},
		{"WORLD_1_LEVELS_8"}
		};
	}_UserGameData;
	_UserGameData UserGameData;

	/* �����洢 */
	typedef struct
	{
		map<int, Scene*> CaveScene;
		Scene* Temporary = nullptr;
		int Level = -1;
	}_CaveScene;
	_CaveScene CaveScene;

	/* �����洢 */
	map<string, spSkeletonData*>GlobalAnimationData;

	/* ��Ϸ�ı� */
	map<string, string>GameText;

	/* ͼƬ·�� */
	map<string, string>ImagesPath;

	/* ����·�� */
	map<string, string>MusicsPath;

	/* ����·�� */
	map<string, string>AnimationPath;

	/* �ı�·�� */
	map<string, string>TextPath;

	/* ������ */
	int SunNumbers;

	/* ����� */
	int CoinNumbers;

	/* ��ǰfps */
	int NowFps;

	/* ������˵������� */
	bool MainToWorld;

private:
	static Global* _instance;    /* ���� */
};