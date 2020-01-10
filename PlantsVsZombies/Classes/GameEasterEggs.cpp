#include "GameEasterEggs.h"

Scene* GameEasterEggs::createScene()
{
	return GameEasterEggs::create();
}

bool GameEasterEggs::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto AudioID = global->changeBgMusic("ZombiesWinEggs", false);

	/* ���ֲʵ� */
	string buff = { "      �������������ף����ͨ���˴˲��԰�����йؿ�����л���ܹ�����ʱ������ע����Ϸ�����ǵĹ�ע���ҿ�����Ϸ���������������Ϊ���ǵĹ�ע����ʹ�������㹻������ʹ�Ҽ��������ȥ��������Ϸ���ĸ��á�\n      ֲ���ս��ʬ�����Ϸ������ϲ������Ϸ֮һ���ܾ���ǰ�Ҿ�ϣ���Լ��ܹ���������һ��ͬ����Ϸ�������Ǹ�ʱ���������ޣ�ֱ��ȥ����٣�2018�꣩�ҿ�ʼ������������˴�Լһ�����¡����������������ޣ�����������Ϸ����û�п����ԡ���󲻵ò������������������Ҳ�û�������ķ�����ʱ��һ�꣨2019�꣩������Ҵ��¿�ʼ����ֲ���ս��ʬ�������������µ�ѧϰ�뿪����������������һ�����п����ԵĲ��԰档��Ϸ������һ�����Ѷ��Ҽ����Ĺ��̣��ڼ��������������⣬�й�������Ҳ�й��˷ܡ������Ҽ����������\n      �´ο��ܵĸ���������ֲ���Լ���ʬ���࣬�����̵�ϵͳ�Լ�ͼ��ϵͳ����һ���µ����磬������Ϸ���࣬����С��Ϸ�ȵȡ�\n       Ŀǰ�����ֽ�ʬ�Ͱ���ֲ�ֲ��ͽ�ʬ�Ķ������Ǳ������ģ��������������������ޣ���Щ��ʬ��ֲ�ﶯ������ʵ�֣������������������Ը������ҵ��˿���˽���ң���������spine��������Ĺ��������������ĸ����ǲ���ʱ�ģ����ܻ����������qq��2117610943\n\n" };
	
	auto Eggstext = Label::createWithTTF("", "resources/fonts/GameFont.ttf", 36);
	Eggstext->setString(buff + "��Ϸ�����о��� "+std::to_string(global->UserGameData.BreakThrough)+" �δ���ʧ�ܣ�\n��Ϸ������ʹ�� "+std::to_string(global->UserGameData.UsePlantsNumbers)+" ��ֲ����з�����\n��Ϸ�����й��� " + std::to_string(global->UserGameData.KillAllZombies) + " ����ʬ�����ˣ�");
	Eggstext->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, -430));
	Eggstext->setColor(Color3B(0, 255, 255));
	Eggstext->setMaxLineWidth(1700);
	this->addChild(Eggstext);

	Eggstext->runAction(Sequence::create(MoveTo::create(25.0f, Director::getInstance()->getWinSize() / 2.0f), 
		CallFunc::create([=]() 
			{
				auto text = Label::createWithTTF("�������������ֲ������", "resources/fonts/GameFont.ttf", 36);
				text->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2.0f, 100));
				text->setColor(Color3B::WHITE);
				text->setName("Text");
				this->addChild(text);

				this->runAction(RepeatForever::create(Sequence::create(
					CallFunc::create([=]()
						{
							static int I = 0;
							if (I % 3 == 0 || I % 5 == 0 || I % 7 == 0)I++;
							else I += 2;
							auto size = Eggstext->getStringLength();
							for (int i = 0; i < size; i++)
							{
								auto letter = Eggstext->getLetter(i);
								if (letter)
								{
									letter->runAction(Sequence::create(DelayTime::create(0.05f * i), Spawn::create(JumpBy::create(0.7f, Vec2(0, 0), 50, 1), RotateBy::create(0.7f, 360), Sequence::create(TintTo::create(0.35f, Color3B::RED), TintTo::create(0.35f, I % 2 == 0 ? Color3B::GREEN : Color3B(0, 255, 255))), nullptr), nullptr));
								}
							}
						}), DelayTime::create(Eggstext->getStringLength() * 0.05f / 3.0f), nullptr)));

				this->runAction(RepeatForever::create(Sequence::create(
					CallFunc::create([=]()
						{
							auto size1 = text->getStringLength();
							for (int i = 0; i < size1; i++)
							{
								auto letter = text->getLetter(i);
								if (letter)
								{
									letter->runAction(Sequence::create(DelayTime::create(0.1f * i), JumpBy::create(0.5f, Vec2(0, 0), 30, 1), nullptr));
								}
							}
						}), DelayTime::create(text->getStringLength() * 0.1f), nullptr)));

			}),nullptr));

	AudioEngine::setFinishCallback(AudioID, [=](int i,string name) 
		{
			this->getChildByName("Text")->setVisible(false);

			global->GlobalMusic.BackGroundMusic.clear();
			global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("mainmusic")->second, true));
			AudioEngine::setVolume(*global->GlobalMusic.BackGroundMusic.begin(), global->GlobalMusic.BackGroundMusicVolume);

			/* ������ť */
			auto button = ui::Button::create(global->ImagesPath.find("SeedChooser_Button2")->second, global->ImagesPath.find("SeedChooser_Button2_Glow")->second);
			button->setTitleText(global->GameText.find("�˳�")->second);
			button->setTitleColor(Color3B(0, 255, 255));
			button->setTitleFontSize(18);
			button->setScale(2.0f);
			button->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 100));
			this->addChild(button);
			button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
				{
					switch (type)
					{
					case ui::Widget::TouchEventType::BEGAN:
						AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("tap2")->second), global->GlobalMusic.SoundEffect);
						break;
					case ui::Widget::TouchEventType::ENDED:
						Director::getInstance()->popScene();
						break;
					}
				});
		});
	return true;
}

