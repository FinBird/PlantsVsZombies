#include "Plants.h"
#include "Pause_Quit_Game.h"
#include "AdventureGameScene.h"

Scene* AdventrueGameScene::createScene()
{
	return AdventrueGameScene::create();
}

bool AdventrueGameScene::init()
{
	if (!Scene::init()) return false;
	srand(time(nullptr));

	AudioEngine::stopAll();
	global->GlobalMusic.BackGroundMusic.clear();

	switch (global->NowPlayLevels.PlayLevels)
	{
	case 35:
		global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("mainmusic.mo3.2")->second, true));
		break;
	case 36:
		global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("mainmusic.mo3.3")->second, true));
		break;
	case 37:
		global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("mainmusic.mo3.7")->second, true));
		break;
	case 50:
		global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("mainmusic.mo3.10")->second, true));
		break;
	case 51:
		global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("mainmusic.mo3.11")->second, true));
		break;
	case 52:
		global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("mainmusic.mo3.12")->second, true));
		break;
	default:
		global->GlobalMusic.BackGroundMusic.push_back(AudioEngine::play2d(global->MusicsPath.find("KitanaiSekai")->second, true));
		break;
	}
	AudioEngine::setVolume(*global->GlobalMusic.BackGroundMusic.begin(), global->GlobalMusic.BackGroundMusicVolume);
	
	BackGroundLayer::create()->addScene(this);           /* �������� */
	this->addChild(UiLayer, 500, "UiLayer");
	this->addChild(SunLayer, 66666, "SunLayer");
	this->addChild(ZombiesLayer, 100, "ZombiesLayer");
	this->addChild(CarLayer, 10000, "CarLayer");         
	this->CreateMenubutton(1);                           /* �����˵���ť */
	this->CreateBank();                                  /* �������� */
	this->CreateCardButton();                            /* �������ư�ť */
	this->CreateMouse();                    	         /* ���������� */

	if (global->NowPlayLevels.PlayLevels != 36 && 
		global->NowPlayLevels.PlayLevels != 50 && 
		global->NowPlayLevels.PlayLevels != 52)
	{
		SunFlowers->RandomCreateSuns(this);       /* �������� */
	}
	zombies->ZombiesUpdate(ZombiesLayer);         /* ��ʬ���� */

	return true;
}

void AdventrueGameScene::Update(float Time)
{
	/* ����ֲ����ֲλ�� */
	this->CalculatePlantPosition();

	/* ���ƿ����Ƿ���� */
	this->ControlCardEnabled();

	/* ������ʬ */
	this->CreateZombies();                       
}

void AdventrueGameScene::CalculatePlantPosition()
{
	for (int i = 0; i < global->MapSize.RowNumbers; i++)
	{
		for (int j = 0; j < global->MapSize.ColumnNumbers; j++)
		{
			if (Cur.x > GrassPosition + 122 * j && Cur.x < GrassPosition + 122 * (j + 1) && Cur.y>110 + 138 * i && Cur.y < 110 + 138 * (i + 1))
			{
				PlantPlantsPosition.Plants_x = j;
				PlantPlantsPosition.Plants_y = i;
			}
		}
	}

	/* ������ڷ�Χ�ڣ��Ƴ��������� */
	if (Cur.x < GrassPosition || Cur.x>1668 || Cur.y < 110 || Cur.y>810)
	{
		PlantPlantsPosition.Plants_x = -100;
		PlantPlantsPosition.Plants_y = -100;
	}
}

void AdventrueGameScene::ControlCardEnabled()
{
	for (int i = 0; i < global->UserSelectCard.CardNumbers; i++)
	{
		/* ���ֲ����������������ӵ�������� */
		if (PlantsButton.PlantsNeedSuns[global->UserSelectCard.CardID[i]] > global->SunNumbers)
		{
			PlantsButton.CardText[global->UserSelectCard.CardID[i]]->setColor(Color3B::RED);
		}
		else
		{
			PlantsButton.CardText[global->UserSelectCard.CardID[i]]->setColor(Color3B::BLACK);
		}
		/* ���������䵹��ʱ��� */
		if (PlantsButton.TimeBarFinished[global->UserSelectCard.CardID[i]])
		{
			PlantsButton.Card[global->UserSelectCard.CardID[i]]->setEnabled(true);
			/* ���ֲ������������С�������� */
			if (PlantsButton.PlantsNeedSuns[global->UserSelectCard.CardID[i]] <= global->SunNumbers)
			{
				PlantsButton.Card[global->UserSelectCard.CardID[i]]->setColor(Color3B::WHITE);
			}
			else
			{
				PlantsButton.Card[global->UserSelectCard.CardID[i]]->setColor(Color3B::GRAY);
			}
		}
	}
}

void AdventrueGameScene::CreateBank()
{
	/* ��Ϸ������ʾ */
	GameType::getInstance()->CreateGameType(UiLayer);
	UiImageText::getInstance()->CreateCar(CarLayer);                                          /* С�� */
	progressbar = UiImageText::getInstance()->CreateProgressBar(UiLayer);                     /* ������ */
	UiImageText::getInstance()->CreateSunBank(UiLayer);                                       /* ̫���� */
	UiImageText::getInstance()->CreateSeedBank(UiLayer);                                      /* ������ */
	UiImageText::getInstance()->CreateCoinbank(UiLayer);                                      /* ����� */
	UiImageText::getInstance()->CreateShovelBank(UiLayer, &MouseSelectImage.IsSelectShovel);  /* ������ */
	UiImageText::getInstance()->CreateText(UiLayer);                                          /* ���� */
	UiImageText::getInstance()->CreateControlSpeed(UiLayer);                                  /* �����ٶȰ�ť */
	UiImageText::getInstance()->CreateZombiesDieBank(UiLayer);                                /* ��ʬ������ */
	SunFlowers->ShowSunNumbers(SunLayer);                                                     /* ��ʾ������ */
	SunFlowers->ShowCoinNumbers(SunLayer);                                                    /* ��ʾ����� */
	SunFlowers->CreateSunListener(SunLayer);                                                  /* ����̫������� */
}

void AdventrueGameScene::sliderAction(Ref* sender, Control::EventType /*controlEvent*/)
{
	/*ControlSlider* pSliderCtl = static_cast<ControlSlider*>(sender);
	float scale;
	scale = pSliderCtl->getValue();*/

	//director->getScheduler()->setTimeScale(scale);
}

void AdventrueGameScene::CreateCardButton()
{
	for (int i = 0; i < global->UserSelectCard.CardNumbers; i++)
	{
		auto Card = ui::Button::create(global->ImagesPath.find("SeedPacket_Larger")->second, global->ImagesPath.find("SeedPacket_Larger")->second);
		Card->setPosition(Vec2(110, 1008 - 103 * i));
		Card->setEnabled(false);
		Card->setColor(Color3B::GRAY);
		Card->setCascadeColorEnabled(true);
		UiLayer->addChild(Card);

		CreateLayer(global->UserSelectCard.CardID[i]);

		CreateSelectPlantsSkill(global->UserSelectCard.CardID[i]);

		/* �洢���� */
		PlantsButton.Card[global->UserSelectCard.CardID[i]] = Card;

		/* ������տ����ƴ��� ���ÿ����� */
		if (global->UserSelectCard.CardID[i] == 0)
		{
			PlantsButton.Card[global->UserSelectCard.CardID[i]]->setColor(Color3B::WHITE);
			PlantsButton.Card[global->UserSelectCard.CardID[i]]->setEnabled(true);
		}

		/* ��¼���������� */
		PlantsButton.PlantsNeedSuns[global->UserSelectCard.CardID[i]] = PlantsNeedSuns[global->UserSelectCard.CardID[i]];

		/* ������ť�ϵ�ͼƬ���ֲ���¼ */
		PlantsButton.CardText[global->UserSelectCard.CardID[i]] = ShowPlantsAndNeedSunNumbers(Card, global->UserSelectCard.CardID[i]);

		/* ��������ʱ������ */
		global->UserSelectCard.CardID[i] == 0 ? this->SetTimerBar(Card, 0, global->UserSelectCard.CardID[i]) : this->SetTimerBar(Card, PlantsCoolTime[global->UserSelectCard.CardID[i]], global->UserSelectCard.CardID[i]);

		Card->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
			{
				switch (type)
				{
				case ui::Widget::TouchEventType::ENDED:
					this->CreateMovePlantsImage(global->UserSelectCard.CardID[i]);
					break;
				}
			});
	}

	/* ��ʱ���� */
	this->schedule(schedule_selector(AdventrueGameScene::Update));
	this->schedule(CC_CALLBACK_1(AdventrueGameScene::ZombiesUpdateTimeing, this), 1.0f, "ZombiesUpdateTimeing");
}

void AdventrueGameScene::SetTimerBar(ui::Button* Card, const float& Time,const int& ID)
{
	auto TimerBar = ProgressTimer::create(Sprite::create(global->ImagesPath.find("SeedPacketSilhouette1")->second));
	TimerBar->setType(ProgressTimer::Type::BAR);  //�������ν�����
	TimerBar->setBarChangeRate(Vec2(1, 0));       //���ú���
	TimerBar->setMidpoint(Vec2(0, 1));            //���ô�������
	TimerBar->setPosition(Vec2(90, 48));
	TimerBar->setOpacity(150);
	TimerBar->setPercentage(100);
	TimerBar->runAction(Sequence::create(ProgressFromTo::create(Time, 100, 0),
		CallFuncN::create(CC_CALLBACK_1(AdventrueGameScene::TimeBarFinishedCallBack, this, Card, ID)), nullptr));
	Card->addChild(TimerBar);
	
	PlantsButton.TimerBar[ID] = TimerBar;
}

void AdventrueGameScene::TimeBarFinishedCallBack(Node* node, ui::Button* Card,const int& ID)
{
	/* ����ʱ���� */
	PlantsButton.TimeBarFinished[ID] = true;
}

void AdventrueGameScene::CreateMouse()
{
	/* ���������� */
	auto Mouse = EventListenerMouse::create();

	/* ����ƶ� */
	Mouse->onMouseMove = [&](Event* event)
	{
		/* ��ȡ���λ�� */
		Cur = ((EventMouse*)event)->getLocationInView();

		this->MouseMoveControl();
	};

	/* ��갴�� */
	Mouse->onMouseDown = [&](Event* event)
	{
		this->MouseDownControl((EventMouse*)event);
	};

	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Mouse, this);

	/* �������̼��� */
	auto KeyBoard = EventListenerKeyboard::create();
	KeyBoard->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event)
	{
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:                     /* �ո����ͣ */
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
			director->pushScene(Pause_Quit_Game::CreateScene());
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:                 /* ��Сдw�������ϼ�ͷ���� */
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
			if (director->getScheduler()->getTimeScale() == 1.5f)
			{
				director->getScheduler()->setTimeScale(1.0f);
				((ui::Button*)UiLayer->getChildByName("AddSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButton")->second);
			}
			else
			{
				director->getScheduler()->setTimeScale(1.5f);
				((ui::Button*)UiLayer->getChildByName("SubSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButton")->second);
				((ui::Button*)UiLayer->getChildByName("AddSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButtonDown")->second);
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:                /* ��Сдs�������¼�ͷ���� */
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
			if (director->getScheduler()->getTimeScale() == 0.5f)
			{
				director->getScheduler()->setTimeScale(1.0f);
				((ui::Button*)UiLayer->getChildByName("SubSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButton")->second);
			}
			else
			{
				director->getScheduler()->setTimeScale(0.5f);
				((ui::Button*)UiLayer->getChildByName("AddSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButton")->second);
				((ui::Button*)UiLayer->getChildByName("SubSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButtonDown")->second);
			}
			break;
		default:
			break;
		}
	};
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(KeyBoard, this);
}

void AdventrueGameScene::MouseMoveControl()
{
	/* ������ѡ����ֲ�� */
	if (MouseSelectImage.IsSelectPlants)
	{
		if (PlantPlantsPosition.Plants_x == -100 || PlantPlantsPosition.Plants_y == -100 ||                    /* ������ڵ�ͼ�� */
			global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] == NOPLANTS) /* ���û����ֲ�� */
		{
			Plant->SetImagePosition(this, Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 60));
		}
		if (global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] != NOPLANTS)
		{
			Plant->SetImagePosition(this, Vec2(-1000, -1000));
		}
	}

	/* ������в��� */
	if (MouseSelectImage.IsSelectShovel)
	{
		/* ѭ����ֲ��ָ���ԭ������ɫ */
		for (int i = 0; i < global->MapSize.RowNumbers; i++)
		{
			for (int j = 0; j < global->MapSize.ColumnNumbers; j++)
			{
				if (global->MapSize.PlantsMap[i][j] != 10000 &&
					global->MapSize.PlantsMap[i][j] != NOPLANTS)
				{
					auto Plants = static_cast<SkeletonAnimation*>(this->getChildByTag(j * 5 + i));
					Plants->setColor(Color3B::WHITE);
				}
			}
		}
		if (PlantPlantsPosition.Plants_x >= 0 && PlantPlantsPosition.Plants_x <= 8 &&                             /* ����ڵ�ͼ��Χ�� */
			PlantPlantsPosition.Plants_y >= 0 && PlantPlantsPosition.Plants_y <= 4 &&
			global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] != 10000 &&
			global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] != NOPLANTS)    /* ����ֲ�� */
		{
			auto Plants = static_cast<SkeletonAnimation*>(this->getChildByTag(PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y));
			Plants->setColor(Color3B::GRAY);
		}
	}
}

void AdventrueGameScene::MouseDownControl(EventMouse* eventmouse)
{
	/* ���������겻�ڿ������ڲ����������ֲ�� */
	if (MouseSelectImage.IsSelectPlants) 
	{
		if (Cur.x > 200)
		{
			if (PlantPlantsPosition.Plants_x >= 0 && PlantPlantsPosition.Plants_x <= 8 &&                             /* ����ڵ�ͼ��Χ�� */
				PlantPlantsPosition.Plants_y >= 0 && PlantPlantsPosition.Plants_y <= 4 &&
				global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] == NOPLANTS)    /* û����ֲ�� */
			{
				if (static_cast<int>(eventmouse->getMouseButton()) == 0) /* ��� */
				{
					/* ��¼ʹ��ֲ������ */
					UserDefault::getInstance()->setIntegerForKey("USEPLANTSNUMBERS", ++global->UserGameData.UsePlantsNumbers);

					/* ��ֲֲ�� */
					this->PlantPlants(MouseSelectImage.SelectPlantsID);

					/* ��ͼ��¼��ֲ��ֲ�� */
					global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] = MouseSelectImage.SelectPlantsID;

					/* ���õ���ʱ���Ұ�ť������ */
					PlantsButton.TimeBarFinished[MouseSelectImage.SelectPlantsID] = false;
					PlantsButton.Card[MouseSelectImage.SelectPlantsID]->setEnabled(false);
					PlantsButton.Card[MouseSelectImage.SelectPlantsID]->setColor(Color3B::GRAY);
					PlantsButton.TimerBar[MouseSelectImage.SelectPlantsID]->runAction(
						Sequence::create(
							ProgressFromTo::create(PlantsCoolTime[MouseSelectImage.SelectPlantsID], 100, 0),
							CallFuncN::create(CC_CALLBACK_1(AdventrueGameScene::TimeBarFinishedCallBack, this, PlantsButton.Card[MouseSelectImage.SelectPlantsID], MouseSelectImage.SelectPlantsID)), nullptr));
				}
			}
			else
			{
				AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("tap2")->second), global->GlobalMusic.SoundEffect);
				/* ������ɫ�ָ� */
				PlantsButton.TimerBar[MouseSelectImage.SelectPlantsID]->setPercentage(0);
				PlantsButton.Card[MouseSelectImage.SelectPlantsID]->setColor(Color3B::WHITE);

				if (static_cast<int>(eventmouse->getMouseButton()) == 0) /* ��� */
				{
					AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("buzzer")->second), global->GlobalMusic.SoundEffect);
					UiImageText::getInstance()->CreatePromptText(UiLayer, global->GameText.find("��ʾ��Ϣ")->second);
				}
			}	

			/* �Ƴ�Ԥ��ֲ�� */
			this->removeChildByName("Preview");
			director->getOpenGLView()->setCursor(global->ImagesPath.find("cursor")->second, Point::ANCHOR_TOP_LEFT);
			MouseSelectImage.IsSelectPlants = false;
		}

		if (static_cast<int>(eventmouse->getMouseButton()) == 1) /* �Ҽ� */
		{
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("tap2")->second), global->GlobalMusic.SoundEffect);
			PlantsButton.TimerBar[MouseSelectImage.SelectPlantsID]->setPercentage(0);
			PlantsButton.Card[MouseSelectImage.SelectPlantsID]->setColor(Color3B::WHITE);
			/* ��������������������� */
			global->SunNumbers += PlantsButton.PlantsNeedSuns[MouseSelectImage.SelectPlantsID];
			SunFlowers->UpdateSunNumbers();
			/* ֲ��Ҫ����� */
			GameType::getInstance()->UpdateRequirementNumbers(UiLayer, "ֲ����������");

			/* �Ƴ�Ԥ��ֲ�� */
			this->removeChildByName("Preview");
			director->getOpenGLView()->setCursor(global->ImagesPath.find("cursor")->second, Point::ANCHOR_TOP_LEFT);
			MouseSelectImage.IsSelectPlants = false;
		}
	}

	if (MouseSelectImage.IsSelectShovel &&                                                                /* ������в��� */
		!(ui::Button*)(UiLayer->getChildByName("ShovelBank"))->getBoundingBox().containsPoint(Cur))       /* ��겻�ڲ������� */
	{
		AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("plant2")->second), global->GlobalMusic.SoundEffect);
		if (PlantPlantsPosition.Plants_x >= 0 && PlantPlantsPosition.Plants_x <= 8 &&                             /* ����ڵ�ͼ��Χ�� */
			PlantPlantsPosition.Plants_y >= 0 && PlantPlantsPosition.Plants_y <= 4 &&
			global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] != 10000 &&
			global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x] != NOPLANTS)    /* ����ֲ�� */
		{
			/* ����ֲ�� */
			this->DeletePlants(global->MapSize.PlantsMap[PlantPlantsPosition.Plants_y][PlantPlantsPosition.Plants_x], PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
			
			Zombie::getInstance()->ErgodicZombies();
		}
		/* ������ʧ */
		MouseSelectImage.IsSelectShovel = false;
		director->getOpenGLView()->setCursor(global->ImagesPath.find("cursor")->second, Point::ANCHOR_TOP_LEFT);
	}
}

void AdventrueGameScene::CreateMovePlantsImage(const int& ID)
{
	switch (MouseSelectImage.IsSelectPlants)
	{
	case true:
		/* �������� */
		AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("tap2")->second), global->GlobalMusic.SoundEffect);
		/* ���ı� */
		director->getOpenGLView()->setCursor(global->ImagesPath.find("cursor")->second, Point::ANCHOR_TOP_LEFT);
		/* ��Ƭ��ԭ */
		PlantsButton.TimerBar[MouseSelectImage.SelectPlantsID]->setPercentage(0);
		PlantsButton.Card[ID]->setColor(Color3B::WHITE);

		/* ��������������������� */
		global->SunNumbers += PlantsButton.PlantsNeedSuns[MouseSelectImage.SelectPlantsID];
		SunFlowers->UpdateSunNumbers();
		
		/* �Ƴ�Ԥ��ֲ�� */
		this->removeChildByName("Preview");
		MouseSelectImage.IsSelectPlants = false;

		/* ֲ��Ҫ����� */
		GameType::getInstance()->UpdateRequirementNumbers(UiLayer, "ֲ����������");
		break;
	case false:
		if (PlantsButton.PlantsNeedSuns[ID] > global->SunNumbers)                               /* ���ֲ�������������ӵ�����⣬�򷢳����� */
		{
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("buzzer")->second), global->GlobalMusic.SoundEffect);
			SunFlowers->SunNumberTextRunAction(SunLayer);
		}
		else if (GameType::getInstance()->PlantsRequriement.IsHavePlantsRequriement &&
			GameType::getInstance()->PlantsRequriement.SurPlusPlantsNumbers <= 0)       /* ʣ��ֲ������С�ڵ���0 */
		{
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("buzzer")->second), global->GlobalMusic.SoundEffect);
			GameType::getInstance()->WaringPlantsNull();
		}
		else
		{
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("seedlift")->second), global->GlobalMusic.SoundEffect);

			/* ѡ��ֲ��ͼƬ */
			this->SelectPalntsImage(ID);

			/* ��ȥ����������������� */
			global->SunNumbers -= PlantsButton.PlantsNeedSuns[ID];
			SunFlowers->UpdateSunNumbers();

			/* ��Ƭ��� */
			PlantsButton.Card[ID]->setColor(Color3B::GRAY);
			PlantsButton.TimerBar[ID]->setPercentage(100);

			/* ���ѡ���� */
			MouseSelectImage.IsSelectPlants = true;
			MouseSelectImage.SelectPlantsID = ID;

			/* ֲ��Ҫ����� */
			GameType::getInstance()->UpdateRequirementNumbers(UiLayer, "ֲ����������");
		}
		break;
	}
}

void AdventrueGameScene::CreateZombies()
{
	/* ˢ�½�ʬ */
	if (ZombiesAppearControl.LastFrequencyZombiesWasDeath)
	{
		ZombiesAppearControl.LastFrequencyZombiesWasDeath = false;
		if (ZombiesAppearControl.ZombiesAppearFrequency < LevelData->LevelData.ZombiesFrequency)
		{
			int zombiesnumbers = zombies->CreateZombiesForNumbers(ZombiesAppearControl.ZombiesAppearFrequency);
			for (int i = 0; i < zombiesnumbers; i++)
			{
				zombies->CreateZombies(Vec2(1780 + rand() % 800, ZombiesAppearControl.ZombiesPosition[rand() % 5]),
					ZombiesLayer, ZombiesTag++, 2 + rand() % 2, zombies->CreateZombiesForProbility(ZombiesAppearControl.ZombiesAppearFrequency), false);
			}
			/* ���ò�ͬ�Ľ�ʬ�ڲ�ͬ����Ϸ���� */
			zombies->SetZombiesForGameType();

			ZombiesAppearControl.ZombiesAppearFrequency++;

			float percent = ZombiesAppearControl.ZombiesAppearFrequency / (float)LevelData->LevelData.ZombiesFrequency;
			progressbar->runAction(ProgressFromTo::create(10.0f, LevelLastPrecent * 100, percent * 100));
			LevelLastPrecent = percent;
		}
	}
	UiLayer->getChildByName("ProgressBar")->getChildByName("progressbarhead")->setPosition(Vec2(470 - 460 * (progressbar->getPercentage() / 100.0f), 22));

	/* ���ƽ�ʬ��ˢ�� */
	if (IsRefurbishZombies())
	{
		if (ZombiesAppearControl.ZombiesAppearFrequency)
		{
			ZombiesAppearControl.Time = 0; /* ������һ��ˢ��ʱ������ */
		}
		ZombiesAppearControl.LastFrequencyZombiesWasDeath = true;
		ZombiesAppearControl.IsBegin = false;
		UserDefault::getInstance()->flush();
	}

	/* ���ƴ󲨽�ʬ��Ϯ������������ */
	if (ZombiesAppearControl.Time >= LevelData->LevelData.FirstFrequencyTime && ZombiesAppearControl.ZombiesAppearFrequency == 0)
	{
		AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("awooga")->second), global->GlobalMusic.SoundEffect);
	}
    if (ZombiesAppearControl.ZombiesAppearFrequency == LevelData->LevelData.ZombiesFrequency && !ZombiesAppearControl.IsShowWords)
	{
		if (progressbar->getPercentage() >= LevelLastPrecent * 100 - 8)
		{
			auto flag = dynamic_cast<Sprite*>(UiLayer->getChildByName("ProgressBar")->getChildByName("_progressbarflag"));
			flag->setTexture(global->ImagesPath.find("ProgressBarFlag1")->second);
			CreateGameWords("Final");
			ZombiesAppearControl.IsShowWords = true;
		}
	}
	bool istrue = false;
	for (unsigned int i = 0; i < LevelData->LevelData.MunchZombiesFrequency.size(); i++)
	{
		if (ZombiesAppearControl.ZombiesAppearFrequency == LevelData->LevelData.MunchZombiesFrequency.at(i) && !ZombiesAppearControl.IsShowWords)
		{
			if (progressbar->getPercentage() >= LevelLastPrecent * 100 - 8)
			{
				CreateGameWords("ManyZombiesComing");
				ZombiesAppearControl.IsShowWords = true;
			}
		}
		
		if (ZombiesAppearControl.ZombiesAppearFrequency == LevelData->LevelData.MunchZombiesFrequency.at(i))
		{
			if (progressbar->getPercentage() >= LevelLastPrecent * 100 - 8)
			{
				char name[20] = { "" };
				sprintf(name, "progressbarflag%d", i);
				auto flag = dynamic_cast<Sprite*>(UiLayer->getChildByName("ProgressBar")->getChildByName(name));
				flag->setTexture(global->ImagesPath.find("ProgressBarFlag1")->second);
				istrue = true;
			}
		}
	}
	if (ZombiesAppearControl.IsShowWords &&
		!istrue &&
		ZombiesAppearControl.ZombiesAppearFrequency != LevelData->LevelData.ZombiesFrequency)
	{
		ZombiesAppearControl.IsShowWords = false;
	}

	/* �ؿ����� */
	if (global->Zombies.size() <= 0 && ZombiesAppearControl.ZombiesAppearFrequency >= LevelData->LevelData.ZombiesFrequency)
	{
		director->getScheduler()->setTimeScale(1.0f);/* �ָ����ű��� */
		director->getOpenGLView()->setCursor(global->ImagesPath.find("cursor")->second, Point::ANCHOR_TOP_LEFT); /* �ָ������ʽ */

		SetStop();

		if (request->JudgeUserWin() == 100)
		{
			if (global->NowPlayLevels.PlayLevels >= 52)
			{
				director->getInstance()->pushScene(TransitionFade::create(0.5f, GameEasterEggs::createScene()));
			}
			UserWin();
		}
		else
		{
			GameOver(); /* ����ʧ�� */
		}
	}
}

void AdventrueGameScene::GameOver()
{
	/* ��¼����ʧ�ܸ��� */
	UserDefault::getInstance()->setIntegerForKey("BREAKTHROUGH", ++global->UserGameData.BreakThrough);
	UserDefault::getInstance()->flush();

	AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("losemusic")->second), global->GlobalMusic.SoundEffect);
	UserWinRequirement::getInstance()->CreateDialogBox(UiLayer, request->JudgeUserWin(), 1);

	this->runAction(Sequence::create(DelayTime::create(5),
		CallFunc::create([]()
			{
				Director::getInstance()->replaceScene(TransitionFade::create(0.5f, World_1::createScene()));
			}), nullptr));

	LevelData->LevelData.FlowerPosition = 0;
}

void AdventrueGameScene::ZombiesUpdateTimeing(float Time)
{	
	if (!ZombiesAppearControl.IsBegin)
	{
		ZombiesAppearControl.Time = 0;
		ZombiesAppearControl.IsBegin = true;
	}

	/* ��ʱ */
	ZombiesAppearControl.Time++;
}

void AdventrueGameScene::CreateGameWords(const string& name)
{
	AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("finalwave")->second), global->GlobalMusic.SoundEffect);
	auto zombiescoming = Sprite::create(global->ImagesPath.find(name)->second);
	zombiescoming->setPosition(director->getWinSize() / 2);
	zombiescoming->setGlobalZOrder(11);
	zombiescoming->setScale(5.0f);
	zombiescoming->setName("zombiescoming");
	this->addChild(zombiescoming);
	zombiescoming->runAction(Sequence::create(ScaleTo::create(0.5f, 1.0f), DelayTime::create(1.5f),
		CallFunc::create([=]()
			{
				this->removeChildByName("zombiescoming");
			}), nullptr));
}

bool AdventrueGameScene::IsRefurbishZombies()
{
	if ((ZombiesAppearControl.Time >= LevelData->LevelData.FirstFrequencyTime &&
		 ZombiesAppearControl.ZombiesAppearFrequency == 0)                                                                       /* ��һ��ˢ�¿��� */

		|| (ZombiesAppearControl.Time >= 32 + rand() % 10 &&
		   (ZombiesAppearControl.ZombiesAppearFrequency == 1 || ZombiesAppearControl.ZombiesAppearFrequency == 2))               /* �ڶ�����ˢ�¿��� */

		|| ZombiesAppearControl.Time >= 45                                                                                       /* �������45��ˢ����һ�� */

		|| (global->Zombies.size() <= 3 && ZombiesAppearControl.ZombiesAppearFrequency > 2)                                      /* ������ŵĽ�ʬ��С�ڹ涨��ˢ����һ�� */

		|| (global->Zombies.size() <= 0 && ZombiesAppearControl.ZombiesAppearFrequency != 0)
		)
	{
		return true;
	}
	return false;
}

void AdventrueGameScene::UserWin()
{
	/* ��¼���� */
	if (global->NowLevels[global->NowPlayLevels.PlayWorlds].Levels == global->NowPlayLevels.PlayLevels)
	{
		
		UserDefault::getInstance()->setIntegerForKey(global->UserGameData.UserDataName[global->UserGameData.UserDataNumber].c_str(), ++(global->NowLevels[1].Levels));
		UserDefault::getInstance()->flush();
	}

	auto moneybag_hi_res = ui::Button::create(global->ImagesPath.find("moneybag_hi_res")->second);
	moneybag_hi_res->setPosition(Vec2(700 + rand() % 1000, 100 + rand() % 700));
	moneybag_hi_res->runAction(JumpBy::create(0.5f, Vec2(100 - rand() % 200, 0), 100 + rand() % 100, 1));
	moneybag_hi_res->setGlobalZOrder(20);
	moneybag_hi_res->setName("moneybag_hi_res");
	this->addChild(moneybag_hi_res);

	moneybag_hi_res->runAction(RepeatForever::create(Sequence::create(TintTo::create(0.3f, 150, 150, 150), TintTo::create(0.3f, 255, 255, 255), nullptr)));

	moneybag_hi_res->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("moneyfalls")->second), global->GlobalMusic.SoundEffect);
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				moneybag_hi_res->setEnabled(false);
				moneybag_hi_res->setBright(true);
				auto cariter = Car::getInstance();
				for (cariter->cariter = cariter->Cars.begin(); cariter->cariter != cariter->Cars.end(); ++cariter->cariter)
				{
					if (!cariter->cariter->second.IsLive)
					{
						cariter->cariter->second.IsLive = true;
						cariter->cariter->second.AnimationID = 2;
						AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("plastichit2")->second), global->GlobalMusic.SoundEffect);

						cariter->cariter->second.Image->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.1f, 0), FadeOut::create(0.1f), nullptr), nullptr));
						cariter->cariter->second.Image->setVisible(false);
						CoinMove(cariter->cariter->second.Image->getPosition(), 0);
					}
				}

				AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("moneyfalls")->second), global->GlobalMusic.SoundEffect);
				CreateCoin(moneybag_hi_res);
				break;
			}
		});


}

void AdventrueGameScene::SetStop()
{
	((ui::Button*)UiLayer->getChildByName("SubSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButton")->second);
	((ui::Button*)UiLayer->getChildByName("SubSpeed"))->setEnabled(false);
	((ui::Button*)UiLayer->getChildByName("AddSpeed"))->loadTextureNormal(global->ImagesPath.find("SpeedButton")->second);
	((ui::Button*)UiLayer->getChildByName("AddSpeed"))->setEnabled(false);

	/* ��ʱ��ȡ�� */
	this->unschedule(schedule_selector(AdventrueGameScene::Update));
	this->unscheduleAllCallbacks();

	/* ���Ʋ����� */
	for (int i = 0; i < global->UserSelectCard.CardNumbers; i++)
	{
		PlantsButton.Card[global->UserSelectCard.CardID[i]]->setEnabled(false);
		PlantsButton.Card[global->UserSelectCard.CardID[i]]->setColor(Color3B::GRAY);
	}

	/* ���Ӳ����� */
	ui::Button* ShovelBank = (ui::Button*)(UiLayer->getChildByName("ShovelBank"));
	ShovelBank->setEnabled(false);

	/* ��ͣ������� */
	for (SunFlowers->SunflowerIter = SunFlowers->SunFlowerAnimations.begin(); SunFlowers->SunflowerIter != SunFlowers->SunFlowerAnimations.end(); ++SunFlowers->SunflowerIter)
	{
		SunFlowers->SunflowerIter->second.Animation->stopAllActions();
	}
	SunLayer->stopAllActions();

	/* ����л� */
	director->getOpenGLView()->setCursor(global->ImagesPath.find("cursor")->second, Point::ANCHOR_TOP_LEFT);

}

void AdventrueGameScene::CreateCoin(ui::Button* button)
{
	const int number = LevelData->getInstance()->LevelData.CoinNumbers / 2 + rand() % (LevelData->getInstance()->LevelData.CoinNumbers / 2);

	button->runAction(Sequence::create(Repeat::create(Sequence::create(MoveBy::create(0.05f, Vec2(5, 5)), MoveBy::create(0.05f, Vec2(-5, -5)), nullptr), number / 2), DelayTime::create(0.5f), FadeOut::create(0.5f),
		CallFunc::create([=]()
			{
				this->removeChildByName("moneybag_hi_res");
			}),
		nullptr));

	for (int i = 0; i < number; i++)
	{
		CoinMove(button->getPosition() - Vec2(-10, 55), i);

		if (i >= number - 1)
		{
			this->runAction(Sequence::create(DelayTime::create(2.0f),
				CallFunc::create([=]()
					{
						auto audio = AudioEngine::play2d(global->MusicsPath.find("winmusic")->second);
						AudioEngine::setVolume(audio, global->GlobalMusic.SoundEffect);
						AudioEngine::setFinishCallback(audio, [=](int i, string name)
							{
								AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("lightfill")->second), global->GlobalMusic.SoundEffect);
							});

						auto AwardRays = Sprite::create(global->ImagesPath.find("AwardRays")->second);
						AwardRays->setPosition(director->getWinSize() / 2.0f);
						AwardRays->runAction(RepeatForever::create(Spawn::create(RotateBy::create(0.5f, 30), ScaleBy::create(0.5f, 1.5f), nullptr)));
						AwardRays->setGlobalZOrder(20);
						this->addChild(AwardRays);

						auto White = Sprite::create(global->ImagesPath.find("White")->second);
						White->setAnchorPoint(Vec2(0, 0));
						White->setContentSize(director->getWinSize());
						White->setOpacity(0);
						White->setGlobalZOrder(20);
						this->addChild(White);
						White->runAction(Sequence::create(DelayTime::create(1.0f), FadeIn::create(7.0f),
							CallFunc::create([=]()
								{
									/* �������� */
									UserDefault::getInstance()->setIntegerForKey("COINNUMBERS", global->CoinNumbers);
									UserDefault::getInstance()->flush();

									director->replaceScene(World_1::createScene());
								}), nullptr));
					}), nullptr));
		}
	}
}

void AdventrueGameScene::CoinMove(const Vec2& position, const int& ID)
{
	auto coin = SkeletonAnimation::createWithData(global->GlobalAnimationData.find("coin")->second);
	coin->setScale(0.05f);
	coin->setPosition(position);
	coin->setGlobalZOrder(20);
	coin->setOpacity(0);
	coin->setName("coin");
	this->addChild(coin);

	coin->runAction(Sequence::create(
		DelayTime::create(ID * 0.05f),
		Spawn::create(
			FadeIn::create(0.5f),
			ScaleTo::create(0.5f, 0.3f),
			JumpBy::create(0.5f, Vec2(150 - rand() % 300, 100 - rand() % 100), rand() % 100 + 200, 1), nullptr),
		DelayTime::create(0.05f),
		MoveTo::create(0.5f, Vec2(1650, -40)),
		Spawn::create(ScaleTo::create(0.2f, 0.5f), FadeOut::create(0.2f),
			CallFunc::create([&]()
				{
					AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("moneyfalls")->second), global->GlobalMusic.SoundEffect);
					this->removeChildByName("coin");
					global->CoinNumbers += 2;
					SunFlowers->getInstance()->UpdateCoinNumbers(SunLayer);
				}), nullptr),
		nullptr));
}

void AdventrueGameScene::CreateLayer(const int& ID)
{
	Layer* LayerName[10] =
	{   
		PeaShooterLayer ,WallNutLayer ,CherryBombLayer,PotatpMineLayer ,CabbageLayer ,TorchwoodLayer ,
		SpikeweedLayer,GarlicLayer,FirePeaShooterLayer,JalapenoLayer
	};

	const string LayerName1[] =
	{
		{"PeaLayer"},{"WallNutLayer"},{"CherryBombLayer"},{"PotatpMineLayer"},{"CabbageLayer"},{"TorchwoodLayer"},
	    {"SpikeweedLayer"},{"GarlicLayer"},{"FirePeaShooterLayer"},{"JalapenoLayer"}
	};

	if (ID < 11 && ID > 0)
	{
		this->addChild(LayerName[ID - 1], 1000 + ID, LayerName1[ID - 1]);
	}
}

void AdventrueGameScene::CreateSelectPlantsSkill(const int& ID)
{
	switch (ID)
	{
	case 1:
		PeaShooters->CreatePeaShooterListener(PeaShooterLayer);
		break;
	case 2:
		WallNuts->CreateWallNutListener(WallNutLayer);
		break;
	case 3:
		CherryBombs->CreateCherryBombListener(CherryBombLayer);
		break;
	case 4:
		PotatoMines->CreatePotatoMineListener(PotatpMineLayer);
		break;
	case 5:
		CabbagePults->CreateCabbagePultListener(CabbageLayer);
		break;
	case 6:
		Torchwoods->CreateTorchwoodListener(TorchwoodLayer);
		break;
	case 7:
		Spikeweeds->CreateSpikeweedListener(SpikeweedLayer);
		break;
	case 8:
		Garlics->CreateGarlicListener(GarlicLayer);
		break;
	case 9:
		FirePeaShooters->CreateFirePeaShooterListener(FirePeaShooterLayer);
		break;
	case 10:
		Jalapenos->CreateJalapenoListener(JalapenoLayer);
		break;
	default:
		break;
	}
}

void AdventrueGameScene::DeletePlants(const int& ID, const int& tag)
{
	switch (ID)
	{
	case 0:
		SunFlowers->SunFlowerAnimations.find(tag)->second.BloodVolume = 0;
		break;
	case 1:
		PeaShooters->PeaShooterAnimations.find(tag)->second.BloodVolume = 0;
		break;
	case 2:
		WallNuts->WallNutAnimations.find(tag)->second.BloodVolume = 0;
		break;
	case 3:
		CherryBombs->CherryBombAnimation.find(tag)->second.BloodVolume = 0;
		break;
	case 4:
		PotatoMines->PotatoMineAnimations.find(tag)->second.Animation->setVisible(false);
		break;
	case 5:
		CabbagePults->CabbagePultAnimations.find(tag)->second.BloodVolume = 0;
		break;
	case 6:
		Torchwoods->TorchwoodAnimation.find(tag)->second.BloodVolume = 0;
		break;
	case 7:
		Spikeweeds->SpikeweedAnimation.find(tag)->second.BloodVolume = 0;
		break;
	case 8:
		Garlics->GarlicAnimations.find(tag)->second.EatNumbers = 0;
		break;
	case 9:
		FirePeaShooters->FirePeaShooterAnimations.find(tag)->second.BloodVolume = 0;
		break;
	case 10:
		Jalapenos->JalapenoAnimation.find(tag)->second.BloodVolume = 0;
		break;
	default:
		break;
	}
}

void AdventrueGameScene::SelectPalntsImage(const int& ID)
{
	string PlantsIamgeName[] = 
	{
		{"SunFlower_2"},{"PeaShooter"},{"Wallnut_body"},{"CherryBomb"},{"PotatoMine"},{"Cabbage"},{"Torchwood"},
	    {"Spikeweed"},{"Garlic"},{"FirePeaShooter"},{"Jalapeno"}
	};
	string PlantsIamgeName1[] = 
	{ 
		{"SunFlower_2_1"},{"PeaShooter_1"},{"Wallnut_body_1"},{"CherryBomb_1"},{"PotatoMine_1"},{"Cabbage_1"},
	    {"Torchwood_1"},{"Spikeweed_1"},{"Garlic_1"},{"FirePeaShooter_1"},{"Jalapenos_1"}
	};
	if (global->GlobalParameter.Global_CursorNotHide == cocos2d::ui::CheckBox::EventType::UNSELECTED)
	{
		director->getOpenGLView()->setCursor(global->ImagesPath.find(PlantsIamgeName[ID])->second, Point::ANCHOR_MIDDLE);
	}
	else
	{
		director->getOpenGLView()->setCursor(global->ImagesPath.find(PlantsIamgeName1[ID])->second, Point::ANCHOR_MIDDLE);
	}

	switch (ID)
	{
	case 0:
		SunFlowers->CreateSunFlowerImage(Vec2(-1000, -1000), this);
		break;
	case 1:
		PeaShooters->CreatePeaShooterImage(Vec2(-1000, -1000), this);
		break;
	case 2:
		WallNuts->CreateWallNutImage(Vec2(-1000, -1000), this);
		break;
	case 3:
		CherryBombs->CreateCherryBombImage(Vec2(-1000, -1000), this);
		break;
	case 4:
		PotatoMines->CreatePotatoMineImage(Vec2(-1000, -1000), this);
		break;
	case 5:
		CabbagePults->CreateCabbagePultImage(Vec2(-1000, -1000), this);
		break;
	case 6:
		Torchwoods->CreateTorchwoodImage(Vec2(-1000, -1000), this);
		break;
	case 7:
		Spikeweeds->CreateSpikeweedImage(Vec2(-1000, -1000), this);
		break;
	case 8:
		Garlics->CreateGarlicImage(Vec2(-1000, -1000), this);
		break;
	case 9:
		FirePeaShooters->CreateFirePeaShooterImage(Vec2(-1000, -1000), this);
		break;
	case 10:
		Jalapenos->CreateJalapenoImage(Vec2(-1000, -1000), this);
		break;
	default:
		break;
	}
}

void AdventrueGameScene::PlantPlants(const int& ID)
{
	srand(time(nullptr));
	rand() % 2 == 0 ? AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("plant2")->second), global->GlobalMusic.SoundEffect) : AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("plant")->second), global->GlobalMusic.SoundEffect);
	switch (ID)
	{
	case 0:
		SunFlowers->CreateSunFlowerAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 1:
		PeaShooters->CreatePeaShooterAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 2:
		WallNuts->CreateWallNutAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 3:
		CherryBombs->CreateCherryBombAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 4:
		PotatoMines->CreatePotatoMineAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 5:
		CabbagePults->CreateCabbagePultAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 6:
		Torchwoods->CreateTorchwoodAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 7:
		Spikeweeds->CreateSpikeweedAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 8:
		Garlics->CreateGarlicAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 9:
		FirePeaShooters->CreateFirePeaShooterAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	case 10:
		Jalapenos->CreateJalapenoAnimation(Vec2(PlantPlantsPosition.Plants_x, PlantPlantsPosition.Plants_y),
			Vec2(GrassPosition + 122 * PlantPlantsPosition.Plants_x + 60, 110 + 138 * (PlantPlantsPosition.Plants_y + 1) - 125),
			this, 19 - PlantPlantsPosition.Plants_x + 5 - PlantPlantsPosition.Plants_y, PlantPlantsPosition.Plants_x * 5 + PlantPlantsPosition.Plants_y);
		break;
	default:
		break;
	}
}