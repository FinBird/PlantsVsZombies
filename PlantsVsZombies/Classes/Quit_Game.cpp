#include "Quit_Game.h"

Scene* Quit_Game::CreateScene()
{
	return Quit_Game::create();
}

bool Quit_Game::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->CreateBackGroundImage();

	this->Create_Dialog();

	return true;
}

void Quit_Game::Create_Dialog()
{
	Option = Sprite::createWithTexture(director->getTextureCache()->getTextureForKey(global->ImagesPath.find("LevelObjiectivesBg")->second));
	Option->setPosition(director->getWinSize() / 2);
	Option->setScale(0.9f);
	this->addChild(Option);

	auto PauseAnimation = SkeletonAnimation::createWithData(global->GlobalAnimationData.find("PauseAnimation")->second);
	PauseAnimation->setAnimation(0, "animation", true);
	PauseAnimation->setPosition(Vec2(530, 650));
	Option->addChild(PauseAnimation);

	/* �����ƶ����� */
	TouchListener = CreateTouchtListener(Option);

	/* ���������� */
	auto musicslider = CreateSlider(Vec2(600, 500), Vec2(150, 500), global->GameText.find("����")->second, 1,
		Sprite::create(global->ImagesPath.find("bgFile")->second),
		Sprite::create(global->ImagesPath.find("progressFile")->second),
		Sprite::create(global->ImagesPath.find("thumbFile")->second),
		true);
	auto SoundEffectslider = CreateSlider(Vec2(600, 410), Vec2(150, 410), global->GameText.find("��Ч")->second, 2,
		Sprite::create(global->ImagesPath.find("bgFile")->second),
		Sprite::create(global->ImagesPath.find("progressFile")->second),
		Sprite::create(global->ImagesPath.find("thumbFile")->second),
		true);

	musicslider->setScale(1.2f);
	SoundEffectslider->setScale(1.2f);

	/* ������ѡ�� */
	auto check = CreateCheckBox(Vec2(350, 340), Vec2(150, 340), global->GameText.find("��Ϣ")->second, 1, "CheckBox2", "CheckBox", true);
	auto check1 = CreateCheckBox(Vec2(800, 340), Vec2(600, 340), global->GameText.find("ȫ��")->second, 2, "CheckBox2", "CheckBox", true);
	auto check2 = CreateCheckBox(Vec2(350, 265), Vec2(150, 265), global->GameText.find("��֡��")->second, 3, "CheckBox2", "CheckBox", true);
	auto check3 = CreateCheckBox(Vec2(800, 265), Vec2(600, 265), global->GameText.find("�����ʾ")->second, 4, "CheckBox2", "CheckBox", true);
	auto check4 = CreateCheckBox(Vec2(350, 190), Vec2(150, 190), global->GameText.find("������ʾ")->second, 5, "CheckBox2", "CheckBox", true);

	check->setScale(0.6f);
	check1->setScale(0.6f);
	check2->setScale(0.6f);
	check3->setScale(0.6f);
	check4->setScale(0.6f);

	/* ������ť */
	this->CreateOwnButton(Vec2(210, 100), global->GameText.find("�鿴ͼ��")->second, 0);
	this->CreateOwnButton(Vec2(830, 100), global->GameText.find("�˳���Ϸ")->second, 2);
	this->CreateOwnButton(Vec2(520, 100), global->GameText.find("������Ϸ")->second, 4);
}