#include "BucketZombies.h"

BucketZombies* BucketZombies::_instance = nullptr;

BucketZombies* BucketZombies::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)BucketZombies;
	}
	return _instance;
}

void BucketZombies::CreateBucketZombies(Node* node, const Vec2& Position,const int& AnimationID, const int& tag)
{
	static string AnimationName[] = { {"Zombies_Stand"},{"Zombies_Stand1"} ,{"Zombies_Walk"},{"Zombies_Walk2"},{"Zombies_Walk2"} };

	auto animation = SkeletonAnimation::createWithData(global->GlobalAnimationData.find("Zombies")->second);
	animation->setPosition(Position);
	animation->setContentSize(Size(40, 40));
	animation->setAnchorPoint(Vec2(0, 0));
	animation->setTag(tag);
	animation->setTimeScale(0.8f);
	animation->addEmptyAnimation(0, rand() % 2, rand() % 2);
	animation->addAnimation(0, AnimationName[AnimationID], true);
	animation->setGlobalZOrder(SetZOrder(Position.y));
	animation->setOpacity(0);
	node->addChild(animation);

	/* ������ʬӰ�� */
	auto shadow = Sprite::create(global->ImagesPath.find("plantshadow")->second);
	shadow->setScale(2.0f);
	shadow->setName("shadow");
	shadow->setPosition(Vec2(0, 10));
	shadow->setOpacity(0);
	animation->addChild(shadow, -1);

	animation->setAttachment("Zombie_bucket", "Zombie_bucket1");

	Global::_Zombies zombies;
	zombies.BloodVolume = 200;
	zombies.ShieldVolume = 1200;
	zombies._BloodVolume = 200;
	zombies._ShieldVolume = 1200;
	zombies.Speed = 30;
	zombies.CaveSpeed = 30;
	zombies.ZombiesAnimation = animation;
	zombies.ShieldVolume1 = 0;
	zombies.ZombiesType = Global::ZombiesType::BucketZombies;
	zombies.MusicType = 1;
	zombies.AnimationID = 1;
	zombies.IsHaveShield = true;
	zombies.IsEat = false;
	zombies.IsUseForGameType = false;
	zombies.Tag = tag;

	global->Zombies.insert(pair<int, Global::_Zombies>(tag, zombies));
}

void BucketZombies::CreateBucketZombiesAniamton(map<int, Global::_Zombies>::iterator Iter, Node* node)
{
	if (Iter->second.IsHaveShield) /* ����л��� */
	{
		if (Iter->second.ShieldVolume <= Iter->second._ShieldVolume * 2.0f / 3) /* ����һ������ */
		{
			SetShieldPrimaryInjure(Iter, node);
		}
		if (Iter->second.ShieldVolume <= Iter->second._ShieldVolume * 1.0f / 3) /* ���ܶ������� */
		{
			SetShieldSecondaryInjure(Iter, node);
		}
		if (Iter->second.ShieldVolume <= 0)   /* ������ʧ */
		{
			SetShieldThirdInjure(Iter, node);
		}
	}
	if (Iter->second.BloodVolume <= Iter->second._BloodVolume / 2.0f)  /* ��ʬѪ��С��һ��ֵ����ʬ���첲 */
	{
		SetZombiesPrimaryInjure(Iter, node);
	}
	if (Iter->second.BloodVolume <= 0)   /* ��ʬѪ��С���㣬��ʬ���� */
	{
		SetZombiesSecondaryInjure(Iter, node);
	}
}

void BucketZombies::SetShieldPrimaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node)
{
	if (iter->second.AnimationID == 1) /* ����һ���˺� */
	{
		iter->second.ZombiesAnimation->setAttachment("Zombie_bucket", "Zombie_bucket2");
		iter->second.AnimationID = 2;
	}
}

void BucketZombies::SetShieldSecondaryInjure(map<int, Global::_Zombies>::iterator iter, Node* node)
{
	if (iter->second.AnimationID == 2) /* ���ܶ����˺� */
	{
		iter->second.ZombiesAnimation->setAttachment("Zombie_bucket", "Zombie_bucket3");
		iter->second.AnimationID = 3;
	}
}

void BucketZombies::SetShieldThirdInjure(map<int, Global::_Zombies>::iterator iter, Node* node)
{
	if (iter->second.AnimationID == 3) /* ���������˺� */
	{
		iter->second.ZombiesAnimation->setAttachment("Zombie_bucket", "tt_innerleg_foot3");
		iter->second.AnimationID = 5;
		iter->second.IsHaveShield = false;
		iter->second.MusicType = 0;

		/* ��ʬ������ */
		ZombiesLoseShieldAnimation(iter, node, "Zombie_bucket");
	}
}

void BucketZombies::ZombiesKilledByCar(map<int, Global::_Zombies>::iterator iter, Node* node)
{
	iter->second.ZombiesAnimation->setVisible(false);


	/* ��ʬ������ */
	if (iter->second.IsHaveShield)
	{
		ZombiesLoseShieldAnimation(iter, node, "Zombie_bucket");
	}
	
	/* ��ʬ��ͷ */
	ZombiesLoseHeadAnimation(iter, node, "CommonZombieHead");

	/* ��ʬ���첲 */
	ZombiesLoseArmAnimation(iter, node, "ZombieArm");

	/* ��ʬ������ */
	//ZombiesBodyAnimation(iter, node, "ZombiesBody");
}