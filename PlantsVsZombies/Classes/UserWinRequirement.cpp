#include "UserWinRequirement.h"
#include "AdventureGameScene.h"

UserWinRequirement* UserWinRequirement::_instance = nullptr;

UserWinRequirement* UserWinRequirement::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)UserWinRequirement;
	}
	return _instance;
}

void UserWinRequirement::CreateDialogBox(Node* node, const int& finishedid, const int& ID)
{
	auto layer = LayerColor::create(Color4B(0, 0, 0, ID == 2 ? 0 : 180));
	layer->setGlobalZOrder(30);
	node->addChild(layer);

	LevelObjiectives = ui::Scale9Sprite::create(global->ImagesPath.find("LevelObjiectives")->second);
	LevelObjiectives->setPosition(Director::getInstance()->getWinSize() / 2.0f);
	LevelObjiectives->setGlobalZOrder(30);
	layer->addChild(LevelObjiectives);

	auto LevelObjiectivesText = ui::Text::create();
	LevelObjiectivesText->setString(global->GameText.find("ͨ��Ҫ��")->second);
	LevelObjiectivesText->setFontName("resources/fonts/fzse_gbk.ttf");
	LevelObjiectivesText->setFontSize(50);
	LevelObjiectivesText->setColor(Color3B(0, 255, 255));
	LevelObjiectivesText->setPosition(Vec2(LevelObjiectives->getContentSize().width / 2, 490));
	LevelObjiectivesText->setGlobalZOrder(30);
	LevelObjiectives->addChild(LevelObjiectivesText);

	/* ��ʾҪ�� */
	ShowRequirement(finishedid);

	auto ContinuesGame = ui::Button::create(global->ImagesPath.find("Continue1")->second, global->ImagesPath.find("Continue")->second);
	ID == 0 ? ContinuesGame->setTitleText(global->GameText.find("����")->second) : ContinuesGame->setTitleText(global->GameText.find("ȷ��")->second);
	ContinuesGame->setTitleFontName("resources/fonts/fzse_gbk.ttf");
	ContinuesGame->setTitleFontSize(30);
	ContinuesGame->setTitleColor(Color3B::YELLOW);
	ContinuesGame->setPosition(Vec2(LevelObjiectives->getContentSize().width / 2, 20));
	ContinuesGame->setGlobalZOrder(30);
	LevelObjiectives->addChild(ContinuesGame);

    ContinuesGame->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("tap")->second), global->GlobalMusic.SoundEffect);
				break;
			case ui::Widget::TouchEventType::ENDED:

				switch (ID)
				{
				case 0:
					/* ��ʼ��Ϸ */
					Director::getInstance()->replaceScene(AdventrueGameScene::createScene());
					break;
				case 1:
					Director::getInstance()->replaceScene(TransitionFade::create(0.5f, World_1::createScene()));
					break;
				case 2:
					Director::getInstance()->popScene();
					break;
				}
				break;
			}
		});

	/* ������������ */
	auto listener = EventListenerTouchOneByOne::create();
	

	listener->onTouchBegan = [=](Touch* t, Event* e)
	{
		if (LevelObjiectives->getBoundingBox().containsPoint(t->getLocation()))
		{
			PhasePosition = t->getLocation() - LevelObjiectives->getPosition();
			return true;
		}
		else return false;
	};
	listener->onTouchMoved = [=](Touch* t, Event* e) 
	{
		LevelObjiectives->setPosition(t->getLocation() - PhasePosition);
	};
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, LevelObjiectives);
}

void UserWinRequirement::ShowRequirement(const int& finishedid)
{
	auto leveldata = OpenLevelData::getInstance();

	for (unsigned int i = 0; i < leveldata->LevelData.GameType.size(); i++)
	{
		switch (leveldata->LevelData.GameType.at(i))
		{
		case OpenLevelData::GameTypes::CreateWall:
			ShowText(global->GameText.find("������ķ��ߣ���ֹ��ʬ�Ľ�����")->second, i);
			break;
		case OpenLevelData::GameTypes::AtLeastSunNumbers:
		{
			char buff[128];
			sprintf(buff, global->GameText.find("���ٲ��� %d �����⣡")->second.c_str(), leveldata->LevelData.AtLeastSunNumbers);
			finishedid == 1 ? ShowText(buff, i, Color3B::RED) : ShowText(buff, i);
		}
			break;
		case OpenLevelData::GameTypes::FlowerPosition:
			finishedid == 2 ? ShowText(global->GameText.find("��ʬ�Ȼ�����Ļ�̳��")->second, i, Color3B::RED) : ShowText(global->GameText.find("��Ҫ�ý�ʬ�Ȼ���Ļ�̳��")->second, i);
			break;
		case OpenLevelData::GameTypes::CarNumbers:
		{
			char buff[128];
			sprintf(buff, global->GameText.find("��ʬ�������������ٴ��� %d ��С����")->second.c_str(), leveldata->LevelData.CarNumbers);
			finishedid == 3 ? ShowText(buff, i, Color3B::RED) : ShowText(buff, i);
		}
			break;
		case OpenLevelData::GameTypes::UserPlantsNumbers:
		{
			char buff[128];
			sprintf(buff, global->GameText.find("���ʹ�� %d ��ֲ����������ķ��ߣ�")->second.c_str(), leveldata->LevelData.UsePlantsNumbers);
			ShowText(buff, i);
		}
			break;
		case OpenLevelData::GameTypes::ZombiesInvisible:
			ShowText(global->GameText.find("��ֹ���εĽ�ʬ�Ľ�����")->second, i);
			break;
		case OpenLevelData::GameTypes::SmallZombies:
			ShowText(global->GameText.find("С��ʬ���鷳��")->second, i);
			break;
		case OpenLevelData::GameTypes::BigZombies:
			ShowText(global->GameText.find("�������˽�ʬ�Ľ�����")->second, i);
			break;
		case OpenLevelData::GameTypes::NoPlants:
			ShowText(global->GameText.find("���ֲ����ֲ�ں��ʵĵط���")->second, i);
			break;
		default:
			break;
		}
	}
}

void UserWinRequirement::ShowText(const string& text, const int& ID, Color3B color)
{
	auto requiretext = Label::createWithTTF(text, "resources/fonts/GameFont.ttf", 40);
	requiretext->setColor(Color3B::BLACK);
	requiretext->setLineBreakWithoutSpace(true);
	requiretext->setWidth(790);
	requiretext->setPosition(TextPosition[OpenLevelData::getInstance()->LevelData.GameType.size() - 1][ID]);
	requiretext->setAnchorPoint(Vec2(0, 1));
	requiretext->setGlobalZOrder(30);
	requiretext->setColor(color);
	LevelObjiectives->addChild(requiretext);

	auto LevelObjiectives2 = Sprite::create(global->ImagesPath.find("LevelObjiectives2")->second);
	LevelObjiectives2->setPosition(TextPosition[OpenLevelData::getInstance()->LevelData.GameType.size() - 1][ID] + Vec2(-90, +13));
	LevelObjiectives2->setAnchorPoint(Vec2(0, 1));
	LevelObjiectives2->setGlobalZOrder(30);
	LevelObjiectives->addChild(LevelObjiectives2);
}