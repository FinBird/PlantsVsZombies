#pragma once

#include "cocos2d.h"
#include "HelpScene.h"
#include "QuitScene.h"
#include "AudioEngine.h"
#include "spine/spine.h"
#include "OptionsSence.h"
#include "InputDataScene.h"
#include "SelectWorldScene.h"
#include "spine\spine-cocos2dx.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

using namespace cocos2d;
using namespace spine;
using namespace cocos2d::experimental;

class MainMenu :public Scene
{
public:
	
	static Scene* createScene();            /* �������� */
	virtual bool init();                    /* ��ʼ�� */
	CREATE_FUNC(MainMenu);

private:
	
	bool PlayMusic[8] = { false };          /* �����Ƿ񲥷� */
	Vec2 cur;                               /* �����λ�� */
	Text* UserText;                         /* �����û����� */
	Node* UserNameActionParent;             /* �û����ƶ���parent */
	Menu* menu[2];                          /* �˵� */
	Sprite* sprite[17],*MainButton[9];      /* ���� */
	MenuItemImage* MenuItem[5];             /* �˵��� */
	EventListenerMouse* Mouse;              /* ������ */

	Global* global = Global::getInstance();
	Director* director = Director::getInstance();

private:
	
	short CheckCurInButtons();                                   /* �ж������λ��*/
	void CurUpdate(float time);                                  /* ����궨ʱ�� */
	void UpdateUserNameOnce(float time);
	void SetCloudPosition(Node *node,int ID, const Vec2 &vec2);  /* �����Ƶ�λ�� */
	void PlayMusicBleepInGameButtons(int ID);                    /* �������� */
	void PlayMusicBleepInMainBuutons(int ID, const Vec2 &vec2);
private:

	/*��Ϸѡ����*/
	void BeginAdventureGame();     /* ð��ģʽ */
	void BeginSurvivalGame();      /* ����С��Ϸ */
	void BeginChallengesGame();    /* ����ģʽ */
	void BeginVasebreakerGame();   /* ����ģʽ */

private:

	/*�ص�����*/
	void MenuHelpCallBack(Ref* pSender);   /* ���� */
	void MenuOptionCallBack(Ref* pSender); /* ѡ�� */
	void MenuQuitCallBack(Ref* pSender);   /* �˳� */
	void MenuDataCallBack(Ref* pSender);   /* ���� */

private:

	/*��������*/
	void CreateMainSprite();                                  /* ���������˵����� */
	void CreateParticle();                                    /* ����������Ч */
	void CreateSmoke(const float &Scale, const Vec2 &vec2);   /* ��������������Ч */
	void CreateMouseListener();                               /* ������������ */
	void CreateMainButton();                                  /* ������ť */
	void CreateClouds();                                      /* ������ */
	void CreateAnimation();                                   /* �������� */
	void CreateFlowers();                                     /* �������� */
	void CreateFlowers(const float &Scale, const Vec2 &vec2, const std::string &fileName, const int &ID);
};
