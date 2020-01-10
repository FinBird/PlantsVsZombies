#include "Pause_Quit_Game.h"

Scene* Pause_Quit_Game::CreateScene()
{
	return Pause_Quit_Game::create();
}

bool Pause_Quit_Game::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/* �������� */
	this->CreateBackGroundImage();

	/* �����Ի��� */
	this->Create_Dialog();

	return true;
}

void Pause_Quit_Game::Create_Dialog()
{
	Option = Sprite::createWithTexture(director->getTextureCache()->getTextureForKey(global->ImagesPath.find("LevelObjiectivesBg")->second));
	Option->setPosition(director->getWinSize() / 2);
	Option->setScale(0.9f);
	this->addChild(Option);

	auto PauseAnimation= SkeletonAnimation::createWithData(global->GlobalAnimationData.find("PauseAnimation")->second);
	PauseAnimation->setAnimation(0, "animation", true);
	PauseAnimation->setPosition(Vec2(530, 650));
	Option->addChild(PauseAnimation);

	/* �����ƶ����� */
	TouchListener = CreateTouchtListener(Option);

	/* ���������� */
	auto musicslider = CreateSlider(Vec2(600, 520), Vec2(150, 520), global->GameText.find("����")->second, 1,
		Sprite::create(global->ImagesPath.find("bgFile")->second),
		Sprite::create(global->ImagesPath.find("progressFile")->second),
		Sprite::create(global->ImagesPath.find("thumbFile")->second),
		true);
	auto SoundEffectslider = CreateSlider(Vec2(600, 450), Vec2(150, 450), global->GameText.find("��Ч")->second, 2,
		Sprite::create(global->ImagesPath.find("bgFile")->second),
		Sprite::create(global->ImagesPath.find("progressFile")->second),
		Sprite::create(global->ImagesPath.find("thumbFile")->second),
		true);

	musicslider->setScale(1.2f);
	SoundEffectslider->setScale(1.2f);

	/* ������ѡ�� */
	auto check    = CreateCheckBox(Vec2(350, 380), Vec2(150, 380), global->GameText.find("��Ϣ")->second, 1, "CheckBox2", "CheckBox", true);
	auto check1   = CreateCheckBox(Vec2(800, 380), Vec2(600, 380), global->GameText.find("ȫ��")->second, 2, "CheckBox2", "CheckBox", true);
	auto check2   = CreateCheckBox(Vec2(350, 310), Vec2(150, 310), global->GameText.find("��֡��")->second, 3, "CheckBox2", "CheckBox", true);
	auto check3   = CreateCheckBox(Vec2(800, 310), Vec2(600, 310), global->GameText.find("�����ʾ")->second, 4, "CheckBox2", "CheckBox", true);
	auto check4   = CreateCheckBox(Vec2(350, 240), Vec2(150, 240), global->GameText.find("������ʾ")->second, 5, "CheckBox2", "CheckBox", true);

	check->setScale(0.6f);
	check1->setScale(0.6f);
	check2->setScale(0.6f);
	check3->setScale(0.6f);
	check4->setScale(0.6f);

	/* ������ť */
	CreateOwnButton(Vec2(210, 170), global->GameText.find("�鿴ͼ��")->second, 0);
	CreateOwnButton(Vec2(520, 170), global->GameText.find("���¿�ʼ")->second, 1);
	CreateOwnButton(Vec2(830, 170), global->GameText.find("������Ϸ")->second, 4);
	CreateOwnButton(Vec2(365, 70), global->GameText.find("����˵��")->second, 3);
	CreateOwnButton(Vec2(665, 70), global->GameText.find("�˳���Ϸ")->second, 2);

	/* ������Ӧ */
	auto KeyBoard = EventListenerKeyboard::create();
	KeyBoard->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event)
	{
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:                     /* �ո����ͣ */
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
			director->popScene();
			break;
		default:
			break;
		}
	};
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(KeyBoard, this);
}

void Pause_Quit_Game::CreateOwnButton(const Vec2& vec2, const std::string name, const int& ID)
{
	/* �����������˵���ť */
	auto button = ui::Button::create(global->ImagesPath.find("ButtonNew2")->second, global->ImagesPath.find("ButtonNew")->second);
	auto label = Label::createWithTTF(name, "resources/fonts/fzse_gbk.ttf", 35);
	label->enableShadow(Color4B(0, 0, 0, 200));//������Ӱ
	label->setScale(2.0f);
	button->setTitleLabel(label);
	button->setTitleColor(Color3B::WHITE);
	button->setPosition(vec2);
	button->setScale(0.5f);
	Option->addChild(button);

	button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
				break;
			case ui::Widget::TouchEventType::ENDED:
				switch (ID)
				{
				case 0:
					Application::getInstance()->openURL("https://share.weiyun.com/5TewoDc");
					break;
				case 1:
					director->getScheduler()->setTimeScale(1.0f);
					director->replaceScene(TransitionFade::create(1.0f,SelectPlantsGameReadyScene::createScene()));
					break;
				case 2:
				{
					//auto scene = CaveScene.CaveScene.find(NowPlayLevels.PlayLevels);
					///* ����д浵��ɾ�� */
					//if (scene != CaveScene.CaveScene.end())
					//{
					//	CaveScene.CaveScene.erase(NowPlayLevels.PlayLevels);
					//}
					//CaveScene.CaveScene.insert(pair<int, Scene*>(NowPlayLevels.PlayLevels, CaveScene.Temporary));

					director->getScheduler()->setTimeScale(1.0f);
					director->replaceScene(TransitionFade::create(1.0f, World_1::createScene()));
				}
					break;
				case 3:
				{				
					Option->setVisible(false);
					TouchListener->setEnabled(false);

					auto Prompt = Sprite::create(global->ImagesPath.find("Prompt")->second);
				    //Prompt->setPosition(Vec2(550,300));
					Prompt->setPosition(director->getWinSize() / 2.0f);
					Prompt->setScale(1.2f);
					Prompt->setOpacity(200);
					Prompt->setName("Prompt");
					this->addChild(Prompt);

					auto Close = ui::Button::create(global->ImagesPath.find("CloseDown")->second, global->ImagesPath.find("Close")->second);
					Close->setPosition(Vec2(1150, 520));
					Close->setScale(0.6f);
					Prompt->addChild(Close);

					Close->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
						{
							switch (type)
							{
							case ui::Widget::TouchEventType::BEGAN:
								AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("tap")->second), global->GlobalMusic.SoundEffect);
								break;
							case ui::Widget::TouchEventType::ENDED:
								Option->setVisible(true);
								TouchListener->setEnabled(true);
								this->removeChildByName("Prompt");
								break;
							}
						});
				}
					break;
				case 4:
					director->popScene();
					break;
				}
				break;
			}
		});
}
