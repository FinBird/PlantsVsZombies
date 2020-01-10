#pragma once
#include "Dialog.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameEasterEggs.h"


#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

using namespace ui;
using namespace cocos2d;
using namespace cocos2d::experimental;
using namespace cocos2d::extension;

class OptionsMenu :public Dialog
{
public:
	static Scene* CreateOptionsScene();
	virtual bool init() override;
	CREATE_FUNC(OptionsMenu);

private:

	UserDefault* userdefault = UserDefault::getInstance();
	Director* director = Director::getInstance();

protected:
	Sprite* Option;                                         /* �Ի��� */
	
protected:

	virtual void Create_Dialog();                                                                /* �����Ի��� */
	virtual void CreateButton();                                                                 /* ������ť */
	CheckBox* CreateCheckBox(Vec2& vec2, Vec2& vec2_, const std::string& Label, const int& ID,
		const std::string NotSelect, const std::string Select, const bool IsNew = false);        /* ������ѡ�� */
	ControlSlider* CreateSlider(Vec2& vec2, Vec2& vec2_, const std::string& Label, const int& ID,
		const std::string bgFile, const std::string progressFile,
		const std::string thumbFile, const bool IsNew = false);                                  /* ���������� */
	ControlSlider* CreateSlider(Vec2& vec2, Vec2& vec2_, const std::string& Label, const int& ID,
		Sprite* BgFile, Sprite* progressFile, Sprite* thumbFile, const bool IsNew = false);      /* ���������� */

	void BackGroundMusicVolumeChangeCallBack(Ref* sender, Control::EventType type);              /* ���������������ڻص�����*/
	void SoundEffectMusicVolumeChangeCallBack(Ref* sender, Control::EventType type);             /* ��Ч�����������ڻص�����*/
};