#include "OptionsSence.h"
#include "GlobalVariable.h"

Scene* OptionsMenu::CreateOptionsScene()
{
	return OptionsMenu::create();
}

bool OptionsMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	this->CreateBackGroundImage();

	this->Create_Dialog();

	return true;
}

void OptionsMenu::Create_Dialog()
{
	Option = Sprite::createWithTexture(director->getTextureCache()->getTextureForKey(global->ImagesPath.find("options_menuback")->second));
	Option->setPosition(director->getWinSize() / 2);
	Option->setScale(1.7f);
	this->addChild(Option);
	
	/* �����ƶ����� */
	this->CreateTouchtListener(Option);

	/* ���������� */
	this->CreateSlider(Vec2(250, 350), Vec2(140, 350), global->GameText.find("����")->second, 1, "options_sliderslot", "options_sliderslot", "options_sliderknob2");
	this->CreateSlider(Vec2(250, 310), Vec2(140, 310), global->GameText.find("��Ч")->second, 2, "options_sliderslot", "options_sliderslot", "options_sliderknob2");

	/* ������ѡ�� */
	this->CreateCheckBox(Vec2(300, 280), Vec2(140, 280), global->GameText.find("��Ϣ")->second, 1, "options_checkbox0", "options_checkbox1");
	this->CreateCheckBox(Vec2(300, 245), Vec2(140, 245), global->GameText.find("ȫ��")->second, 2, "options_checkbox0", "options_checkbox1");
	this->CreateCheckBox(Vec2(300, 210), Vec2(140, 210), global->GameText.find("��֡��")->second, 3, "options_checkbox0", "options_checkbox1");
	this->CreateCheckBox(Vec2(300, 175), Vec2(140, 175), global->GameText.find("������ʾ")->second, 5, "options_checkbox0", "options_checkbox1");

	/* �����ʵ� */
	if (global->NowLevels[0].IsBeginShowEggs)
	{
		auto button = Button::create(global->ImagesPath.find("button")->second, global->ImagesPath.find("button_down")->second);
		button->setTitleLabel(label("������", 20, Vec2(0, 0), 0, Color3B::GRAY, 0.5f));
		button->setPosition(Vec2(210, 140));
		button->setScaleX(2.0f);
		Option->addChild(button);
		button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
			{
				switch (type)
				{
				case Widget::TouchEventType::BEGAN:
					AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
					break;
				case Widget::TouchEventType::ENDED:
					Director::getInstance()->pushScene(TransitionFade::create(0.5f,GameEasterEggs::createScene()));
					break;
				}
			});
	}

    /* ������ť */
	this->CreateButton();
}



ControlSlider* OptionsMenu::CreateSlider(Vec2 &vec2, Vec2 &vec2_, const std::string &Label, const int& ID,
	const std::string bgFile, const std::string progressFile,const std::string thumbFile,const bool IsNew)
{
	/* ���������� */
	auto slider = ControlSlider::create((global->ImagesPath.find(bgFile)->second).c_str(), (global->ImagesPath.find(progressFile)->second).c_str(), (global->ImagesPath.find(thumbFile)->second).c_str());
	slider->setMinimumValue(0);
	slider->setMaximumValue(100);
	slider->setPosition(vec2);
	Option->addChild(slider);

	if (ID == 1) /* ���ֻص����� */
	{
		slider->setValue(global->GlobalMusic.BackGroundMusicVolume * 100);
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionsMenu::BackGroundMusicVolumeChangeCallBack), Control::EventType::VALUE_CHANGED);
	}

	if (ID == 2) /* ��Ч�ص����� */
	{
		slider->setValue(global->GlobalMusic.SoundEffect * 100);
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionsMenu::SoundEffectMusicVolumeChangeCallBack), Control::EventType::VALUE_CHANGED);
	}

	/* ������ǩ */
	switch (IsNew)
	{
	case true:
		Option->addChild(label(Label, 30, vec2_, 0, Color3B::WHITE));
		break;
	case false:
		Option->addChild(label(Label, 20, vec2_, 0, Color3B::GRAY));
		break;
	}

	return slider;
}

ControlSlider* OptionsMenu::CreateSlider(Vec2& vec2, Vec2& vec2_, const std::string& Label, const int& ID, Sprite* BgFile, Sprite* progressFile, Sprite* thumbFile, const bool IsNew)
{
	/* ���������� */
	auto slider = ControlSlider::create(BgFile, progressFile, thumbFile);
	slider->setMinimumValue(0);
	slider->setMaximumValue(100);
	slider->setPosition(vec2);
	Option->addChild(slider);

	if (ID == 1) /* ���ֻص����� */
	{
		slider->setValue(global->GlobalMusic.BackGroundMusicVolume * 100);
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionsMenu::BackGroundMusicVolumeChangeCallBack), Control::EventType::VALUE_CHANGED);
	}

	if (ID == 2) /* ��Ч�ص����� */
	{
		slider->setValue(global->GlobalMusic.SoundEffect * 100);
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionsMenu::SoundEffectMusicVolumeChangeCallBack), Control::EventType::VALUE_CHANGED);
	}

	/* ������ǩ */
	switch (IsNew)
	{
	case true:
		Option->addChild(label(Label, 30, vec2_, 0, Color3B::WHITE));
		break;
	case false:
		Option->addChild(label(Label, 20, vec2_, 0, Color3B::GRAY));
		break;
	}

	return slider;
}

void OptionsMenu::BackGroundMusicVolumeChangeCallBack(Ref* sender, Control::EventType type)
{
	auto slider = (ControlSlider*)sender;
	for (auto sp : global->GlobalMusic.BackGroundMusic)  /* ѭ�������������� */
	{
		AudioEngine::setVolume(sp, slider->getValue() / 100.0f);
	}

	global->GlobalMusic.BackGroundMusicVolume = slider->getValue() / 100.0f;
	userdefault->setFloatForKey("GLOBALMUSIC", global->GlobalMusic.BackGroundMusicVolume);

	if (slider->getSelectedThumbSprite()->getContentSize().height == 40)
	{
		/* ��ת���� */
		slider->getThumbSprite()->setRotation(slider->getValue() * 10);
		slider->getSelectedThumbSprite()->setRotation(slider->getValue() * 10);
	}	
}

void OptionsMenu::SoundEffectMusicVolumeChangeCallBack(Ref* sender, Control::EventType type)
{
	/* ������Ч���� */
	auto slider = (ControlSlider*)sender;
	global->GlobalMusic.SoundEffect = slider->getValue() / 100.0f;
	userdefault->setFloatForKey("SOUNDEFFECT", global->GlobalMusic.SoundEffect);

	if (slider->getSelectedThumbSprite()->getContentSize().height == 40)
	{
		/* ��ת���� */
		slider->getThumbSprite()->setRotation(slider->getValue() * 10);
		slider->getSelectedThumbSprite()->setRotation(slider->getValue() * 10);
	}
}

CheckBox* OptionsMenu::CreateCheckBox(Vec2 &vec2, Vec2 &vec2_, const std::string &Label, const int &ID,
	const std::string NotSelect, const std::string Select, const bool IsNew)
{
	auto checkbox = CheckBox::create();
	checkbox->loadTextureBackGround(global->ImagesPath.find(NotSelect)->second);
	checkbox->loadTextureFrontCross(global->ImagesPath.find(Select)->second);
	checkbox->setPosition(vec2);
	Option->addChild(checkbox);

	switch (ID)
	{
	case 1:
		checkbox->setSelected(global->GlobalParameter.Global_Information == cocos2d::ui::CheckBox::EventType::SELECTED ? true : false);
		break;
	case 2:
		checkbox->setSelected(global->GlobalParameter.Global_FullScreen == cocos2d::ui::CheckBox::EventType::SELECTED ? true : false);
		break;
	case 3:
		checkbox->setSelected(global->GlobalParameter.Global_HighFPS == cocos2d::ui::CheckBox::EventType::SELECTED ? true : false);
		break;
	case 4:
		checkbox->setSelected(global->GlobalParameter.Global_CursorNotHide == cocos2d::ui::CheckBox::EventType::SELECTED ? true : false);
		break;
	case 5:
		checkbox->setSelected(global->GlobalParameter.Global_StretchingShow == cocos2d::ui::CheckBox::EventType::SELECTED ? true : false);
		break;
	default:
		break;
	}
	
	checkbox->addEventListener([=](Ref* sender, CheckBox::EventType type)
	{
		switch (type)
		{
		case CheckBox::EventType::SELECTED:
			switch (ID)
			{
			case 1: /* ��ʾ��Ϣ */
				userdefault->setBoolForKey("SHOWINFORMATION", true);
				global->GlobalParameter.Global_Information = CheckBox::EventType::SELECTED; /* ���� */
				director->setDisplayStats(true);
				break;
			case 2: /* ȫ�� */
				userdefault->setBoolForKey("SHOWFULLSCREEN", true);
				global->GlobalParameter.Global_FullScreen= CheckBox::EventType::SELECTED;
				((GLViewImpl*)director->getOpenGLView())->setFullscreen();
				break;
			case 3: /* ��֡�� */
				userdefault->setBoolForKey("SHOWHIGHFPS", true);
				global->GlobalParameter.Global_HighFPS = CheckBox::EventType::SELECTED;
				director->setAnimationInterval(1.0f / 60);
				global->NowFps = 60;
				break;
			case 4: /* ������� */
				userdefault->setBoolForKey("CURSORHIDE", true);
				global->GlobalParameter.Global_CursorNotHide = CheckBox::EventType::SELECTED;
				break;
			case 5: /* ������ʾ */
				userdefault->setBoolForKey("STRETCHINGSHOW", true);
				director->getOpenGLView()->setDesignResolutionSize(director->getWinSize().width, director->getWinSize().height, ResolutionPolicy::EXACT_FIT);
				global->GlobalParameter.Global_StretchingShow = CheckBox::EventType::SELECTED;
				break;
			default:
				break;
			}
			break; 
		case CheckBox::EventType::UNSELECTED:
			switch (ID)
			{
			case 1:
				userdefault->setBoolForKey("SHOWINFORMATION", false);
				global->GlobalParameter.Global_Information = CheckBox::EventType::UNSELECTED;
				director->setDisplayStats(false);
				break;
			case 2:
				userdefault->setBoolForKey("SHOWFULLSCREEN", false);
				global->GlobalParameter.Global_FullScreen = CheckBox::EventType::UNSELECTED;
				((GLViewImpl*)director->getOpenGLView())->setWindowed(1280, 720);
				break;
			case 3:
				userdefault->setBoolForKey("SHOWHIGHFPS", false);
				global->GlobalParameter.Global_HighFPS = CheckBox::EventType::UNSELECTED; /* ���� */
				director->setAnimationInterval(1.0f / 45);
				global->NowFps = 45;
				break;
			case 4:
				userdefault->setBoolForKey("CURSORHIDE", false);
				global->GlobalParameter.Global_CursorNotHide = CheckBox::EventType::UNSELECTED;
				break;
			case 5: 
				userdefault->setBoolForKey("STRETCHINGSHOW", false);
				director->getOpenGLView()->setDesignResolutionSize(director->getWinSize().width, director->getWinSize().height, ResolutionPolicy::SHOW_ALL);
				global->GlobalParameter.Global_StretchingShow = CheckBox::EventType::UNSELECTED;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	});

	switch (IsNew)
	{
	case true:
		Option->addChild(label(Label, 30, vec2_, 0, Color3B::WHITE));
		break;
	case false:
		Option->addChild(label(Label, 20, vec2_, 0, Color3B::GRAY));
		break;
	}
	
	return checkbox;
}

void OptionsMenu::CreateButton()
{
	auto button = Button::create(global->ImagesPath.find("options_backtogamebutton0")->second, global->ImagesPath.find("options_backtogamebutton2")->second);
	button->setTitleLabel(label(global->GameText.find("����")->second, 30));
	button->setPosition(Vec2(210, 55));
	Option->addChild(button);
	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
			break;
		case Widget::TouchEventType::ENDED:
			userdefault->flush();
			director->popScene();
			break;
		}
	});
}