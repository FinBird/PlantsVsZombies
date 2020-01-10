#pragma once
#include "Car.h"
#include "Garlic.h"
#include "cocos2d.h"
#include "Zombies.h"
#include "WallNut.h"
#include "Jalapeno.h"
#include "UserLose.h"
#include "GameType.h"
#include "Spikeweed.h"
#include "LevelData.h"
#include "SunFlower.h"
#include "Torchwood.h"
#include "PotatoMine.h"
#include "PeaShooter.h"
#include "CherryBomb.h"
#include "CabbagePult.h"
#include "UiImageText.h"
#include "ui/CocosGUI.h"
#include "spine/spine.h"
#include "CommonZombies.h"
#include "GameEasterEggs.h"
#include "FirePeaShooter.h"
#include "GlobalVariable.h"
#include "BackGroundLayer.h"
#include "UserWinRequirement.h"
#include "spine\spine-cocos2dx.h"
#include "SelectPlantsGameReadyScene.h"

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::extension;

constexpr auto NOPLANTS = -1;
constexpr auto GrassPosition = 570;

class AdventrueGameScene :public SelectPlantsGameReadyScene
{
public:
	static Scene* createScene();             /* �������� */
	virtual bool init();                     /* ��ʼ�� */
	CREATE_FUNC(AdventrueGameScene);
	Global* global = Global::getInstance();

	AdventrueGameScene()
	{
		ZombiesTag = 0; /* ��ʬ��ǳ�ʼ�� */
		/* ��ʼ����ͼ */
		global->MapSize.RowNumbers = 5;
		global->MapSize.ColumnNumbers = 9;
		for (int i = 0; i < global->MapSize.RowNumbers; i++)
		{
			for (int j = 0; j < global->MapSize.ColumnNumbers; j++)
			{
				global->MapSize.PlantsMap[i][j] = NOPLANTS;
			}
		}

		/* ��ʼ���Ƿ��в�����ֲ�ĵط� */
		if (OpenLevelData::getInstance()->LevelData.IsNoPlants)
		{
			for (auto sp : OpenLevelData::getInstance()->LevelData.NoPlantsPosition)
			{
				global->MapSize.PlantsMap[sp.y][sp.x] = 10000;
			}
		}

		GameType::getInstance()->Initialization(); /* ��Ϸ���ͳ�ʼ�� */
		SunFlowers->Initialization();              /* ���տ���ʼ�� */
		PeaShooters->Initialization();             /* �㶹���ֳ�ʼ�� */
		CherryBombs->Initialization();             /* ӣ��ը����ʼ�� */
		WallNuts->Initialization();                /* ���ǽ��ʼ�� */
		PotatoMines->Initialization();             /* �����׳�ʼ�� */
		CabbagePults->Initialization();            /* ���Ĳ�Ͷ�ֳ�ʼ�� */
		Torchwoods->Initialization();              /* �����׮��ʼ�� */
		Spikeweeds->Initialization();              /* �ش̳�ʼ�� */
		Garlics->Initialization();                 /* �����ʼ�� */
		FirePeaShooters->Initialization();         /* ���㶹���ֳ�ʼ�� */
		Jalapenos->Initialization();               /* ��������ʼ�� */
		Cars->Initialization();                    /* С����ʼ�� */
		global->Zombies.clear();                   /* ��ս�ʬ */
	}
	~AdventrueGameScene()
	{
		delete request;
		this->removeAllChildrenWithCleanup(true);
	}

private:
	/* �洢��ť�Լ���ť����ʱ */
	typedef struct
	{
		ui::Button* Card[20];                 /* ���� */
		ui::Text* CardText[20];               /* �������� */
		ProgressTimer* TimerBar[20];          /* ����ʱ */
		int PlantsNeedSuns[20];               /* �������� */
		bool TimeBarFinished[20] = { 0 };     /* ����ʱ�Ƿ���� */
	}_PlantsButton;
	_PlantsButton PlantsButton;

	/* ���ѡ���ֲ�� */
	typedef struct
	{
		Sprite* Iamge = nullptr;          /* ͼƬ */
		int SelectPlantsID;               /* ��ѡֲ���� */
		bool IsSelectPlants = false;      /* �Ƿ�ѡ����ֲ�� */
		bool IsSelectShovel = false;      /* �Ƿ�ѡ���˲��� */
	}_MouseSelectImage;
	_MouseSelectImage MouseSelectImage;

	/* ֲ����ֲ���� */
	typedef struct
	{
		int Plants_x;
		int Plants_y;
	}_PlantPlantsPosition;
	_PlantPlantsPosition PlantPlantsPosition;

	/* ��ʬ���ֲ������� */
	typedef struct
	{
		int ZombiesPosition[5] = { 130,268,406,544,682 }; /* ��ʬλ�� */
		int ZombiesAppearFrequency = 0;                   /* ��ʬ���ִ��� */
		bool LastFrequencyZombiesWasDeath = false;        /* ��һ����ʬ������ */
		bool IsBegin = false;                             /* ��ʱ�Ƿ�ʼ */
		bool IsShowWords = false;                         /* �Ƿ���ʾ���� */
		double Time = 0;                                  /* ��ʱ */
	}_ZombiesAppearControl;
	_ZombiesAppearControl ZombiesAppearControl;

private:
	int ZombiesTag;                                                        /* ��ʬ��� */
	Vec2 Cur;                                                              /* ������� */
	float LevelLastPrecent = 0;                                            /* �ؿ���һ�ν��Ƚ��� */
	SkeletonAnimation* SelectPlantsAnimation;                              /* ֲ�ﶯ�� */
	ProgressTimer* progressbar;
	float PlantsCoolTime[15] = 
	{
		7.5f,7.5f,30,35,30,7.5f,7.5f,7.5f,10,10,35
	};                                                                     /* ֲ����ȴʱ�� */
	
	int PlantsNeedSuns[15] =
	{
		50,100,50,150,25,100,175,100,50,200,150
	};                                                                     /* ֲ���������� */


private:
	/* ����layer */
	Layer* UiLayer = Layer::create();
	Layer* SunLayer = Layer::create();
	Layer* PeaShooterLayer = Layer::create();
	Layer* WallNutLayer = Layer::create();
	Layer* CherryBombLayer = Layer::create();
	Layer* PotatpMineLayer = Layer::create();
	Layer* CabbageLayer = Layer::create();
	Layer* TorchwoodLayer = Layer::create();
	Layer* SpikeweedLayer = Layer::create();
	Layer* GarlicLayer = Layer::create();
	Layer* FirePeaShooterLayer = Layer::create();
	Layer* JalapenoLayer = Layer::create();
	Layer* ZombiesLayer = Layer::create();
	Layer* CarLayer = Layer::create();

	/* ��ȡֲ�ﵥ������ */
	Director* director = Director::getInstance();
	SunFlower* SunFlowers = SunFlower::getInstance();
	PeaShooter* PeaShooters = PeaShooter::getInstance();
	WallNut* WallNuts = WallNut::getInstance();
	CherryBomb* CherryBombs = CherryBomb::getInstance();
	PotatoMine* PotatoMines = PotatoMine::getInstance();
	CabbagePult* CabbagePults = CabbagePult::getInstance();
	Torchwood* Torchwoods = Torchwood::getInstance();
	Spikeweed* Spikeweeds = Spikeweed::getInstance();
	FirePeaShooter* FirePeaShooters = FirePeaShooter::getInstance();
	Garlic* Garlics = Garlic::getInstance();
	Jalapeno* Jalapenos = Jalapeno::getInstance();

	/* ��ȡ��ʬ�������� */
	Zombie* zombies = Zombie::getInstance();

	/* �ؿ����ݵ��� */
	OpenLevelData* LevelData = OpenLevelData::getInstance();

	/* С�� */
	Car* Cars = Car::getInstance();

	Request* request = new Request();

private:
	void Update(float Time);
	void ZombiesUpdateTimeing(float Time);                                                      /* ��ʬ���¼�ʱ */
	void CreateLayer(const int& ID);                                                            /* ������ */
	void CreateCardButton();                                                                    /* �������ư�ť */
	void CreateMouse();                                                                         /* ������� */
	void CreateBank();                                                                          /* �������� */
	void CreateCoin(ui::Button* button);                                                        /* ������� */
	void CoinMove(const Vec2& position, const int& ID);                                         /* ����ƶ� */
	void SetTimerBar(ui::Button* Card, const float& Time, const int& ID);                       /* ���õ���ʱʱ���� */
	void CreateMovePlantsImage(const int& ID);                                                  /* ������������ƶ�ֲ�� */
	void CalculatePlantPosition();                                                              /* ����ֲ����ֲλ�� */
	void ControlCardEnabled();                                                                  /* ���ƿ����Ƿ���� */
	void MouseMoveControl();                                                                    /* ����ƶ����� */
	void MouseDownControl(EventMouse* eventmouse = nullptr);                                    /* ��갴�¿��� */
	void PlantPlants(const int& ID);                                                            /* ��ֲֲ�� */
	void SelectPalntsImage(const int& ID);                                                      /* ѡ��ֲ��ͼƬ */
	void CreateSelectPlantsSkill(const int& ID);                                                /* ����ѡ��ֲ��ļ��� */
	void DeletePlants(const int& ID, const int& tag);                                           /* ɾ��ֲ�� */
	void TimeBarFinishedCallBack(Node* node, ui::Button* Card, const int& ID);                  /* ����ʱ��ɻص����� */
	void CreateGameWords(const string& name);                                                   /* ������Ϸ���� */
	void CreateZombies();                                                                       /* ������ʬ */
	void UserWin();                                                                             /* �û�Ӯ */
	void SetStop();                                                                             /* ����ֹͣ */
	bool IsRefurbishZombies();                                                                  /* �Ƿ�ˢ�½�ʬ */
	//int JudgeUserIsWin();                                                                       /* �ж�����Ƿ�Ӯ */
	void GameOver();                                                                            /* ��Ϸ���� */
	void sliderAction(Ref* sender, Control::EventType);
};