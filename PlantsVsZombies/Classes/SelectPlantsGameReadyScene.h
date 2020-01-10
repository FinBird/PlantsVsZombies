#pragma once
#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "Zombies.h"
#include "LevelData.h"
#include "cocos-ext.h"
#include "AudioEngine.h"
#include "spine/spine.h"
#include "ui/CocosGUI.h"
#include "CommonZombies.h"
#include "GlobalVariable.h"
#include "UserWinRequirement.h"
#include "spine\spine-cocos2dx.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

class SelectPlantsGameReadyScene :public Scene
{
public:
	static Scene* createScene();            /* �������� */
	virtual bool init();                    /* ��ʼ�� */
	CREATE_FUNC(SelectPlantsGameReadyScene);
	
	SelectPlantsGameReadyScene()
	{
		
	}

public:
	/* Ԥ����ʬ */
	typedef struct
	{
		SkeletonAnimation* PreviewZombie;
		float PositionY;
	}_PreViewZombies;
	std::vector< _PreViewZombies> PreviewZombies;

private:

	Sprite* SeedChooser;                    /* ����ѡ���� */
	extension::ScrollView* scrollView;      /* ������ͼ */
	SkeletonAnimation* PlantsAnimation;     /* ֲ�ﶯ�� */
	ui::Text* AnimationText[15];            /* ����˵�� */

	ui::ScrollView* PlantCardScrollView;    /* ֲ�￨�ƹ�����ͼ */
	ui::ScrollView* PlantCardTextScrollView;/* ֲ�￨�ƹ�����ͼ */
	float PlantCardScrollViewPercent;       /* ֲ�￨�ƹ�����ͼ�������� */
	float PlantCardScroll;                  /* �������������� */
	float PlantCardTextScroll;              /* �������������� */

	Global* global = Global::getInstance();
	Director* director = Director::getInstance();
	Zombie* zombies = Zombie::getInstance();
	OpenLevelData* LevelData = OpenLevelData::getInstance();

	typedef struct
	{
		/* ���ư�ť */
		ui::Button* button;
		/* �������� */
		int size = 0;
		/* ���Ƶı�� */
		int ID;
	}SeedBankButton;
	SeedBankButton seedbankbutton[10];

protected:
	/* ����������ʬ */
	void CreatePreviewZombies(Sprite* name);
	/* �����������Ӷ��� */
	void CreateFire(Sprite* sprite);
	/* �����˵���ť */
	void CreateMenubutton(const int& ID);
    /* ��ʾֲ������Ҫ�������� */
	ui::Text* ShowPlantsAndNeedSunNumbers(ui::Button* button,const int& ID);

private:
	/* ��ʱ���� */
	void Update(float Time);
	void Update1(float Time);
	void ScrollViewUpdate(float Time);
	
    /* Ϊֲ�￨������ */
	void SortPlantsCard(const int& ID);
	/* Ϊ��ʬ���� */
	void SortZombies();
	
	/* Ԥ�������� */
	void PreloadText();

private:

	/* �������� */
	void CreateBackGround();                                                 
	
	/* �����Ի��� */
	void CreateDialogs();

	/* �����û���Ϣ */
	void CreateUserName(const std::string &);

	/* ��������ʱ���� */
	void CreateReadyText(const std::string&,const int &);

	/* ����ֲ�ﶯ�� */
	void CreatePlantsAnimation(const int& ID);
	void CreateAnimation(const std::string& filepath, const std::string& AnimationName, 
		const std::string &skin, Vec2& vec2, const float& scale = 1.0f);
	void CreateAnimationText(const int& ID, const std::string& name, const Vec2& vec2,
		const float& fontsize, Color3B color = Color3B::WHITE, bool AnchorPoint = true);

	/* ����ֲ�� */
	void CreateSprite(ui::Button* button, const std::string resource, const float& scale = 0.8f);

	/* ����ֲ�￨�ƻ�����ͼ */
	void CreatePlantsCardScrollView();

	/* �������ư�ť */
	ui::Button* CreateButtons(const Vec2& vec2, const int& ID);

	/* �����ƶ����ư�ť */
	void CreateMoveButton(ui::Button* button, const Vec2& vec2, const int& ID);

private:

	/* ɾ��ֲ�￨�ƻص����� */
	void RemovePlantsCardCallBack(Node* node,const int& ID, ui::Button* button);
	
	/* ��ʼѡֲ��ص� */
	void SelectPlantsCallBack(Node* node,const int& ID);   

	/* ׼����Ϸ����ʱ�ص����� */
	void ReadyGameCallBack(Node* node, const std::string &,const int &);

};
