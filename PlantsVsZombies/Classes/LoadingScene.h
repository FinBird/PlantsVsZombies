#pragma once
#include <map>
#include "cocos2d.h"
#include "MainMenu.h"
#include "LevelData.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

using namespace cocos2d;
using namespace cocos2d::experimental;

class LoadingScene :public Scene
{
public:
	static Scene* CreateLaodingScene();          /* �������� */
	virtual bool init() override;                /* ��ʼ�� */
	CREATE_FUNC(LoadingScene); 

private:

	int TextNumbers;                               /* �ı��� */
	int LoadFileNumbers = 0;                       /* �ļ������� */
	int AllFileNumbers;                            /* �ļ�����(ͼƬ�����֣��������ı�) */
	bool FlowerVisible[5] = { false };             /* ���ػ����Ƿ�ɼ� */
	float LoadingPrecent = 0;                      /* ���ؽ��� */
	Sprite* sprite[8];                             /* ����ͼƬ */
	MenuItemLabel* label;                          /* ���ֱ�ǩ */
	ui::LoadingBar* loadingBar;                    /* ������ */
	EventListenerTouchOneByOne* Listener;          /* ���ؼ��� */

	Global* global = Global::getInstance();        /* ȫ�ֱ������� */
	Director* director = Director::getInstance();  /* ���ݵ��� */
	FileUtils* Files = FileUtils::getInstance();   /* �ļ����� */

private:

	void update(float Time) override;                 /* ��ʱ�� */

	void SetSystem();                                 /* ����ϵͳ���� */
	void CalculateFileNumbers();                      /* �����ļ����� */

	void LoadUserData();                              /* �����û����� */
	void LoadingText();                               /* �������� */
	void LoadingImage();                              /* ����ͼƬ */
	void LoadingMusic();                              /* �������� */
	void LoadingAnimation();                          /* ���ض��� */

	void ShowLoadingBackGround();                     /* չʾ���� */
	void ShowTileAndLoadingBar();                     /* չʾ������ */
	void ShowLoadingBarFlower(const int &ID);         /* չʾ�������ϵĻ� */
	void BeginLoadingImageAndMusic();                 /* ��ʼ����ͼƬ������ */

	void RunLoGoCallBack(Node* node,const int &ID);   /* չʾlogo�ص� */
	void LoadingTextCallBack();                       /* �������ֻص� */
	void LoadingImageCallBack(Ref* pSender);          /* ����ͼƬ�ص� */
	void LoadingMusicCallBack(bool isSucceed);        /* �������ֻص� */
	void LoadingAnimationCallBack();                  /* ���ض����ص� */
	void BeginGameCallBack(Ref* pSender);             /* ��ʼ��Ϸ�ص� */

	int OpenResourcesPath(map<string, string>& Path, const std::string& xml, bool IsEncryption = false);  /* ����Դ·�� */
};