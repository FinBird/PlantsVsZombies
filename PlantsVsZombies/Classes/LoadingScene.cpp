#include "ui/CocosGUI.h"
#include "LoadingScene.h"
#include "GlobalVariable.h" 
#include "tinyxml2/tinyxml2.h"

#define MYDEBUG 0

using namespace ui;

Scene* LoadingScene::CreateLaodingScene()
{
	return LoadingScene::create();
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	/* �����ļ����� */
	this->CalculateFileNumbers(); 

	/* ����ϵͳ���� */
	this->SetSystem();

	/* �����û���Ϣ */
	this->LoadUserData();

	/* չʾ���ؽ��� */
	this->ShowLoadingBackGround();
	
	//wglSwapIntervalEXT(0);
	return true;
}

void LoadingScene::SetSystem()
{
	/* ���ù�� */
	director->getOpenGLView()->setCursor(global->ImagesPath.find("cursor")->second, Point::ANCHOR_TOP_LEFT);

	/* ����ͼ�� */
	director->getOpenGLView()->setIcon(global->ImagesPath.find("PlantsVsZombies")->second);

}

void LoadingScene::LoadUserData()
{
	auto userdefault = UserDefault::getInstance();

	/* ɱ����ʬ�� */
	global->UserGameData.KillAllZombies = userdefault->getIntegerForKey("KILLALLZOMBIES");
	/* ʹ��ֲ������ */
	global->UserGameData.UsePlantsNumbers = userdefault->getIntegerForKey("USEPLANTSNUMBERS");
	/* ����ʧ�ܸ��� */
	global->UserGameData.BreakThrough = userdefault->getIntegerForKey("BREAKTHROUGH");
	/* �浵��� */
	global->UserGameData.UserDataNumber = userdefault->getIntegerForKey("USERDATANUMBER");

	/* ��ʾ�ʵ� */
	global->NowLevels[0].IsBeginShowEggs = userdefault->getBoolForKey("ISBEGINSHOWEGGS");

	/* ����� */
	global->CoinNumbers = userdefault->getIntegerForKey("COINNUMBERS");

	/* ��Ч */
	global->GlobalMusic.SoundEffect = userdefault->getFloatForKey("SOUNDEFFECT");

	/* ���� */
	global->GlobalMusic.BackGroundMusicVolume= userdefault->getFloatForKey("GLOBALMUSIC");

	/* ��ȡ�û��浵���� */
	for (int i = 0; i < 8; i++)
	{
		if (!userdefault->getStringForKey(global->UserData.UserCaveFileNameKey[i].c_str()).size())
		{
			global->UserData.UserCaveFileName[i] = "δ�����浵";
		}
		else
		{
			global->UserData.UserCaveFileName[i] = userdefault->getStringForKey(global->UserData.UserCaveFileNameKey[i].c_str());
		}
	}

	/* �û����� */
	global->UserData.UserName = global->UserData.UserCaveFileName[global->UserGameData.UserDataNumber];
	global->UserData.IsUpdate = true;

	/* ��ʾ��Ϣ */
	switch (userdefault->getBoolForKey("SHOWINFORMATION"))
	{
	case true:
		director->setDisplayStats(true);
		global->GlobalParameter.Global_Information = cocos2d::ui::CheckBox::EventType::SELECTED;
		break;
	case false:
		director->setDisplayStats(false);
		global->GlobalParameter.Global_Information = cocos2d::ui::CheckBox::EventType::UNSELECTED;
		break;
	}

	/* �Ƿ�ȫ�� */
	switch (userdefault->getBoolForKey("SHOWFULLSCREEN"))
	{
	case true:
		((GLViewImpl*)director->getOpenGLView())->setFullscreen();
		global->GlobalParameter.Global_FullScreen = cocos2d::ui::CheckBox::EventType::SELECTED;
		break;
	case false:
		((GLViewImpl*)director->getOpenGLView())->setWindowed(1280, 720);
		global->GlobalParameter.Global_FullScreen = cocos2d::ui::CheckBox::EventType::UNSELECTED;
		break;
	}
	
	/* �Ƿ��֡�� */
	switch (userdefault->getBoolForKey("SHOWHIGHFPS"))
	{
	case true:
		director->setAnimationInterval(1.0f / 60);
		global->GlobalParameter.Global_HighFPS = cocos2d::ui::CheckBox::EventType::SELECTED;
		global->NowFps = 60;
		break;
	case false:
		director->setAnimationInterval(1.0f / 45);
		global->GlobalParameter.Global_HighFPS = cocos2d::ui::CheckBox::EventType::UNSELECTED;
		global->NowFps = 45;
		break;
	}

	/* �Ƿ�������ʾ */
	switch (userdefault->getBoolForKey("STRETCHINGSHOW"))
	{
	case true:
		global->GlobalParameter.Global_StretchingShow = cocos2d::ui::CheckBox::EventType::SELECTED;
		director->getOpenGLView()->setDesignResolutionSize(director->getWinSize().width, director->getWinSize().height, ResolutionPolicy::EXACT_FIT);
		break;
	case false:
		global->GlobalParameter.Global_StretchingShow = cocos2d::ui::CheckBox::EventType::UNSELECTED;
		director->getOpenGLView()->setDesignResolutionSize(director->getWinSize().width, director->getWinSize().height, ResolutionPolicy::SHOW_ALL);
		break;
	}

	/* �Ƿ�������� */
	switch (userdefault->getBoolForKey("CURSORHIDE"))
	{
	case true:
		global->GlobalParameter.Global_CursorNotHide = cocos2d::ui::CheckBox::EventType::SELECTED;
		break;
	case false:
		global->GlobalParameter.Global_CursorNotHide = cocos2d::ui::CheckBox::EventType::UNSELECTED;
		break;
	}
}

void LoadingScene::ShowLoadingBackGround()
{
	/* �������� */
	global->changeBgMusic("mainmusic", true);
	
	/* ��ȡ���ڴ�С */
	auto const size = Director::getInstance()->getWinSize();

	/* �������� */
	sprite[0] = Sprite::create(global->ImagesPath.find("PopCap_Logo1")->second);
	sprite[1] = Sprite::create(global->ImagesPath.find("PopCap_Logo")->second);
	sprite[7] = Sprite::create("resources/Text/txt/About.txt");
	sprite[2] = Sprite::create(global->ImagesPath.find("titlescreen")->second);

	/* Ϊ������������ */
	sprite[0]->setName("0");
	sprite[1]->setName("1");
	sprite[7]->setName("7");
	
	/* ���þ����С */
	sprite[0]->setScale(1.5f);
	sprite[1]->setScale(1.5f);
	sprite[2]->setContentSize(size);
	sprite[7]->setScale(1.5f);

	/* ���þ����λ�� */
	sprite[0]->setPosition(size / 2);
	sprite[1]->setPosition(size / 2);
	sprite[7]->setPosition(size / 2);
	sprite[2]->setPosition(size / 2);

	/* ���þ���͸���� */
	sprite[0]->setOpacity(0);
	sprite[1]->setOpacity(0);
	sprite[7]->setOpacity(0);
	sprite[2]->setOpacity(0);

	/* �Ѿ�����ص������� */
	this->addChild(sprite[0]);
	this->addChild(sprite[1]);
	this->addChild(sprite[7]);
	this->addChild(sprite[2]);

	/* ���þ��鲻�ɼ� */
	sprite[1]->setVisible(false);
	sprite[7]->setVisible(false);
	sprite[2]->setVisible(false);

	/* ���þ��鶯�� */
	sprite[0]->runAction(Sequence::create(FadeIn::create(2.0f), FadeOut::create(2.0f), CallFuncN::create(CC_CALLBACK_1(LoadingScene::RunLoGoCallBack, this, 1)), NULL));
}

void LoadingScene::RunLoGoCallBack(Node* node, const int &ID)
{
	switch (ID)
	{
	case 1:
		this->removeChildByName("0"); /* �ӳ������Ƴ�����Ϊ0�ĺ��� */
		sprite[1]->setVisible(true);  /* ���þ���1�ɼ� */
		sprite[1]->runAction(Sequence::create(FadeIn::create(2.0f), FadeOut::create(2.0f), CallFuncN::create(CC_CALLBACK_1(LoadingScene::RunLoGoCallBack, this, 5)), NULL));
		break;
	case 2:
		this->removeChildByName("7"); /* �ӳ������Ƴ�����Ϊ7�ĺ��� */
		sprite[2]->setVisible(true);  /* ���þ���2�ɼ� */
		sprite[2]->runAction(Sequence::create(FadeIn::create(2.0f),CallFuncN::create(CC_CALLBACK_1(LoadingScene::RunLoGoCallBack, this, 3)), NULL));
		break;
	case 3:
		this->ShowTileAndLoadingBar(); /* չʾ����ͽ����� */
		break;
	case 4:
		this->BeginLoadingImageAndMusic(); /* ��ʼ����ͼƬ������ */
		break;
	case 5:
		this->removeChildByName("1"); /* �ӳ������Ƴ�����Ϊ1�ĺ��� */
		sprite[7]->setVisible(true);  /* ���þ���7�ɼ� */
		sprite[7]->runAction(Sequence::create(FadeIn::create(2.0f), FadeOut::create(4.0f), CallFuncN::create(CC_CALLBACK_1(LoadingScene::RunLoGoCallBack, this, 2)), NULL));
		break;
	}
}

void LoadingScene::ShowTileAndLoadingBar()
{
	/* ��ȡ���ڴ�С */
    auto const size = director->getWinSize();

	/* �������� */
	sprite[3] = Sprite::create(global->ImagesPath.find("PvZ_Logo")->second);
	sprite[4] = Sprite::create(global->ImagesPath.find("LoadBar_dirt")->second);
	sprite[5] = Sprite::create(global->ImagesPath.find("SodRollCap")->second);
	sprite[6] = Sprite::create(global->ImagesPath.find("spark")->second);

	/* �����ü��ڵ� */
	auto clippingNode = ClippingNode::create();

	/* ��ȡ����������Ĵ�С */
	Size const SpriteSize = sprite[3]->getContentSize();

	/* Ϊ�������ó�ʼλ�� */
	sprite[4]->setPosition(Vec2(size.width / 2, -100));
	sprite[5]->setPosition(Vec2(10, 95));
	sprite[6]->setPosition(Vec2(-SpriteSize.width, 0));
	clippingNode->setPosition(Vec2(size.width / 2 + 10, 1100));

	/* Ϊ�������ô�С */
	sprite[3]->setScale(2.0f);
	sprite[3]->setScaleX(2.5f);
	sprite[4]->setScale(2.0f);
	sprite[6]->setScale(2.0f);

	/* �þ����˶����� */
	sprite[4]->runAction(Sequence::create(MoveTo::create(0.5f, Vec2(size.width / 2, 150)),CallFuncN::create(CC_CALLBACK_1(LoadingScene::RunLoGoCallBack, this, 4)), NULL));
	sprite[6]->runAction(RepeatForever::create(Sequence::create(MoveTo::create(1.0f, Vec2(SpriteSize.width, 0)), DelayTime::create(2.0f), CallFunc::create([=]() {sprite[6]->setPosition(Vec2(-SpriteSize.width, 0)); }), NULL)));
    clippingNode->runAction(MoveTo::create(0.5f, Vec2(size.width / 2, 900)));

	/* �ӵ������� */
	this->addChild(sprite[4]);
	this->addChild(clippingNode);
	sprite[4]->addChild(sprite[5],1);
	
	/* ���òü��ڵ�Ļ������� */
	clippingNode->setAlphaThreshold(0.01f);   //����alphaբֵ
	clippingNode->setContentSize(SpriteSize); //���óߴ��С
	clippingNode->setStencil(sprite[3]);      //����ģ��stencil
	clippingNode->addChild(sprite[3]);        //����ӱ���,����ȫ��ʾ����,��Ϊ��ģ��һ����С
	clippingNode->addChild(sprite[6]);        //�ᱻ�ü�

	/* �����˵���ǩ */
	label = MenuItemLabel::create(Label::createWithTTF("������......", "resources/fonts/fzse_gbk.ttf", 20), CC_CALLBACK_1(LoadingScene::BeginGameCallBack, this));
	label->setColor(Color3B::YELLOW);
	label->setEnabled(false);
	
	/* �����˵� */
	auto menu = Menu::create(label, NULL);
	menu->setPosition(150, 55);
	sprite[4]->addChild(menu);
}

void LoadingScene::BeginLoadingImageAndMusic()
{
	/* ���������� */
	loadingBar = LoadingBar::create(global->ImagesPath.find("LoadBar_grass")->second);
	loadingBar->setDirection(LoadingBar::Direction::LEFT); /* ���ü��ط��� */
	loadingBar->setPosition(Vec2(150, 70));
	sprite[4]->addChild(loadingBar);

	/* ��ʱ�� */
	scheduleUpdate();

	LoadingText(); /* �����ı� */
	
	LoadingMusic();/* �������� */
	
	LoadingAnimation(); /* ���ض��� */

	LoadingImage();/* ����ͼƬ */	
}

void LoadingScene::update(float Time)
{
	if (LoadingPrecent <= 100) 
	{
		loadingBar->setPercent(LoadingPrecent);              /* ���ü��ؽ��� */
		sprite[5]->setScale(1 - LoadingPrecent / 170);       /* ���þ����С */
		sprite[5]->setRotation(9 * LoadingPrecent);          /* ���þ���ת���� */
		sprite[5]->setPosition(Vec2(10 + 290 / 100.0*LoadingPrecent, 100 - sprite[5]->getContentSize().height / 400 * LoadingPrecent));

		if (LoadingPrecent >= 20) ShowLoadingBarFlower(0);
		if (LoadingPrecent >= 40) ShowLoadingBarFlower(1);
		if (LoadingPrecent >= 60) ShowLoadingBarFlower(2);
		if (LoadingPrecent >= 80) ShowLoadingBarFlower(3);
		if (LoadingPrecent >= 100) ShowLoadingBarFlower(4);

	}
	if(LoadingPrecent >= 100) /* ���������� */
	{
		label->setString(global->GameText.find("�����ʼ")->second);  /* �������ñ�ǩ�������� */
		auto action = TintBy::create(0.5f, 0, 255, 255);
		label->runAction(RepeatForever::create(Sequence::create(action,action->reverse(), nullptr)));
		sprite[5]->setVisible(false);  /* ���þ���5Ϊ���ɼ� */
		label->setEnabled(true);       /* ���ô������� */
	}
}

void LoadingScene::ShowLoadingBarFlower(const int &ID)
{
	srand(unsigned(time(nullptr)));
	if (!FlowerVisible[ID]) /* �������ID�ǲ��ɼ� */
	{
		/* ������ */
		auto flower = Sprite::create(global->ImagesPath.find("sprout_petal")->second);
		flower->setScale(0.1f);
		flower->setPosition(Vec2(20 + (55 + rand() % 10)* ID, 85 + rand() % 10));
		flower->runAction(ScaleTo::create(0.2f, 0.5f));
		sprite[4]->addChild(flower);
		if (ID == 4) /* ���ID==4 ������ʬͷ*/
		{
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("loadingbar_zombie")->second, false), global->GlobalMusic.SoundEffect);
			flower->setTexture(global->ImagesPath.find("ZombieHead")->second);
		}
		else  /* ���򴴽��� */
		{
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("loadingbar_flower")->second, false), global->GlobalMusic.SoundEffect);
			flower->setRotation(rand() % 180);
		}
		
		FlowerVisible[ID] = true; /* ��ID����Ϊ�ɼ� */
	}
}

void LoadingScene::CalculateFileNumbers()
{
#if MYDEBUG
	/* �ļ����� = �ı��� + ͼƬ�� + ������ + ������ */
	AllFileNumbers =
		OpenResourcesPath(global->TextPath, "resources/Text/TextPath.reanim.compiled", true) +
		OpenResourcesPath(global->ImagesPath, "resources/Text/ImagePath.reanim.compiled", true) +
		OpenResourcesPath(global->MusicsPath, "resources/Text/MusicPath.reanim.compiled", true) +
		OpenResourcesPath(global->AnimationPath, "resources/Text/AnimationPath.reanim.compiled", true);
#else
	AllFileNumbers =
		OpenResourcesPath(global->TextPath, "resources/Text/TextPath.xml", false) +
		OpenResourcesPath(global->ImagesPath, "resources/Text/ImagePath.xml", false) +
		OpenResourcesPath(global->MusicsPath, "resources/Text/MusicPath.xml", false) +
		OpenResourcesPath(global->AnimationPath, "resources/Text/AnimationPath.xml", false);
#endif
}

int LoadingScene::OpenResourcesPath(map<string, string>& Path, const std::string& xml, bool IsEncryption)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();

	if (IsEncryption)
	{
		std::string textpath = Files->getStringFromFile(xml);

		char Encryption[200000] = { 0 }, Password[200000] = { 0 };
		strcpy(Encryption, textpath.c_str());

		OpenLevelData::getInstance()->Decrypt(Encryption, Password);

		/* ����Դ·�� */
		doc->Parse(Password);
	}
	else
	{
		/* ����Դ·�� */
		doc->Parse(Files->getStringFromFile(xml).c_str());
	}

	auto root = doc->RootElement();
	for (auto e = root->FirstChildElement(); e; e = e->NextSiblingElement())
	{
		for (auto at = e->FirstAttribute(); at; at = at->Next())
		{
			Path.insert(pair<string, string>(at->Name(), at->Value()));
		}
	}
	return Path.size();
}

void LoadingScene::LoadingText()
{
	/* ѭ�������ı� */
	for (auto i : global->TextPath)
	{
		ValueVector Text = Files->getValueVectorFromFile(i.second);
		for (auto& file : Text)
		{
			auto file_map = file.asValueMap();
			global->GameText.insert(pair<string, string>(file_map.at("id").asString(), file_map.at("info").asString()));
		}
		/* ���ػص� */
		this->LoadingTextCallBack();
	}
}

void LoadingScene::LoadingImage()
{
    /* ѭ������ͼƬ */
	for (auto i : global->ImagesPath)
	{
		director->getTextureCache()->addImageAsync(i.second, CC_CALLBACK_1(LoadingScene::LoadingImageCallBack, this));
	}
}

void LoadingScene::LoadingMusic()
{
	/* ѭ���������� */
	for (auto i : global->MusicsPath)
	{
		AudioEngine::preload(i.second, CC_CALLBACK_1(LoadingScene::LoadingMusicCallBack, this));
	}
}

void LoadingScene::LoadingAnimation()
{
	/* ѭ�����ض��� */
	for (auto i : global->AnimationPath)
	{
		/* ��ʱ�洢�ļ����� */
		char JsonName[100], AtlasName[100];

		/* ת�� */
		sprintf(JsonName, "resources/Animations/Json/%s.json", (i.second).c_str());
		sprintf(AtlasName, "resources/Animations/Atlas/%s.atlas", (i.second).c_str());

		/* ���� */
		spSkeletonJson* json = spSkeletonJson_createWithLoader((spAttachmentLoader*)Cocos2dAttachmentLoader_create(spAtlas_createFromFile(AtlasName, nullptr)));
		auto skeletonData = spSkeletonJson_readSkeletonDataFile(json, JsonName);
		spSkeletonJson_dispose(json);

		/* �Ѽ��ص��Ķ�������map��*/
		global->GlobalAnimationData.insert(pair<string, spSkeletonData*>(i.second, skeletonData));

		/* ���лص� */
		this->LoadingAnimationCallBack();
	}
}

void LoadingScene::LoadingTextCallBack()
{
	LoadFileNumbers++;     /* �ļ�����һ */
	LoadingPrecent = ((LoadFileNumbers * 1.0f) / AllFileNumbers) * 100;  /* ������صİٷֱ� */
}

void LoadingScene::LoadingImageCallBack(Ref* pSender)
{
	LoadFileNumbers++;     /* �ļ�����һ */
	LoadingPrecent = ((LoadFileNumbers * 1.0f) / AllFileNumbers) * 100;  /* ������صİٷֱ� */
}

void LoadingScene::LoadingMusicCallBack(bool isSucceed)
{
	if (isSucceed)/* ������سɹ� */
	{
		LoadFileNumbers++;     /* �ļ�����һ */
		LoadingPrecent = ((LoadFileNumbers * 1.0f) / AllFileNumbers) * 100;  /* ������صİٷֱ� */
	}
}

void LoadingScene::LoadingAnimationCallBack()
{
	LoadFileNumbers++;     /* �ļ�����һ */
	LoadingPrecent = ((LoadFileNumbers * 1.0f) / AllFileNumbers) * 100;  /* ������صİٷֱ� */
}

void LoadingScene::BeginGameCallBack(Ref* pSender)
{
	AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("buttonclick")->second), global->GlobalMusic.SoundEffect);
	director->replaceScene(MainMenu::createScene()); /* �л����� */
}