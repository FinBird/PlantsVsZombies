#include "PeaShooter.h"
#include "CommonZombies.h"

PeaShooter* PeaShooter::_instance = nullptr;

PeaShooter* PeaShooter::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)PeaShooter;
	}
	return _instance;
}

void PeaShooter::Initialization()
{
	PeaShooter::getInstance()->PeaShooterAnimations.clear();
	PeaShooter::getInstance()->Peas.clear();
	PeaShooter::getInstance()->PeaTag = 0;
}

void PeaShooter::CreatePeaShooterImage(const Vec2& position, Node* node)
{
	PeaShooterImage = CreateImage("PeaShooter", position, node);
	PeaShooterImage->setScale(1.5f);
}

void PeaShooter::CreatePeaShooterAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag)
{
	/* �������� */
	auto PeaShooterAnimation = CreateAnimation("PeaShooter", "PeaShooter_Normal", position, 0.8f, 1.8f);
	PeaShooterAnimation->setAnchorPoint(Vec2(0, 0));
	PeaShooterAnimation->setScale(1.1f);
	node->addChild(PeaShooterAnimation, order, tag);
	
	_PeaShooterAnimation animation;
	animation.Animation = PeaShooterAnimation;
	animation.BloodVolume = 300;
	animation.tag = tag;
	animation.RowAndColumn = RowAndColumn;
	animation.position = position;
	PeaShooterAnimations.insert(pair<int, _PeaShooterAnimation>(tag, animation));
}

void PeaShooter::CreatePeaShooterListener(Node* node)
{
	node->schedule(CC_CALLBACK_1(PeaShooter::Update, this, node), "UpdatePeaShooter");
}

void PeaShooter::Update(float Time, Node* node)
{
	JudgePeaShooterAndZombiesPosition(node); /* ��ʬ���㶹����λ���ж� */

	JudgePeaAndZombiesPosition(node);        /* ��ʬ���㶹λ���ж� */
}

void PeaShooter::JudgePeaShooterAndZombiesPosition(Node* node)
{
	for (iter = PeaShooterAnimations.begin(); iter != PeaShooterAnimations.end(); /*++iter*/)
	{
		for (global->Iter = global->Zombies.begin(); global->Iter != global->Zombies.end(); ++global->Iter)
		{
			if (global->Iter->second.BloodVolume > 0 && global->Iter->second.ZombiesAnimation->isVisible() &&                          /* ��ʬû������ */
				global->Iter->second.ZombiesAnimation->getPositionX() <= 1730 &&                                                       /* ��ʬ�����ͼ */
				global->Iter->second.ZombiesAnimation->getPositionX() >= iter->second.Animation->getPositionX() &&                     /* ��ʬ��ֲ���ǰ�� */
				fabs((global->Iter->second.ZombiesAnimation->getPositionY() - 10) - iter->second.Animation->getPositionY()) <= 10)     /* ��ʬ��ֲ����ͬһ�� */
			{
				if (iter->second.BloodVolume > 0 &&                                                                                    /* ֲ��û���� */
					fabs(global->Iter->second.ZombiesAnimation->getPositionX() - iter->second.Animation->getPositionX()) <= 80)        /* ��ʬ����ֲ�� */
				{
					ZombiesEatPlants(global->Iter, &iter->second.BloodVolume, iter->second.Animation);
				} 
				if (iter->second.BloodVolume <= 0 && !global->Iter->second.Speed && global->Iter->second.IsEat)
				{
					global->Iter->second.IsEat = false;
					if (global->Iter->second.AnimationID != 10)
					{
						global->Iter->second.ZombiesAnimation->setMix("Zombies_Eat", Zombie::getInstance()->ZombiesTypeAniamtion(global->Iter->second.ZombiesType), 1.3f);
						global->Iter->second.ZombiesAnimation->addAnimation(1, Zombie::getInstance()->ZombiesTypeAniamtion(global->Iter->second.ZombiesType), true);
						global->Iter->second.Speed = global->Iter->second.CaveSpeed;
					}
				}

				iter->second.IsCreatePea = true; /* ��ʾ�н�ʬ��ֲ����ͬһ�� */
				if (!iter->second.IsChanged)     /* �ж϶����Ƿ��Ѿ��ı� */
				{
					iter->second.Animation->addAnimation(0, "PeaShooter_Shoot", true);
					iter->second.IsChanged = true;
				}
				Vec2 pos = iter->second.Animation->getPosition();
				iter->second.Animation->setEventListener([=](spTrackEntry* entry, spEvent* event)
					{
						if (strcmp(event->data->name, "shoot") == 0)
						{
							rand() % 2 == 0 ? PlaySoundEffect("throw") : PlaySoundEffect("throw2");
							CreatePea(pos, node);
						}
					});
			}
		}
		if (!iter->second.IsCreatePea) /* �ж��Ƿ��н�ʬ���㶹������ͬһ�� */
		{
			if (iter->second.IsChanged)
			{
				iter->second.Animation->addAnimation(0, "PeaShooter_Normal", true);
				iter->second.IsChanged = false;
			}
		}

		iter->second.IsCreatePea = false; /* ÿѭ��һ�ξͳ�ʼ�� */

		/* ɾ���㶹���� */
		if (iter->second.BloodVolume <= 0)
		{
			global->MapSize.PlantsMap[(int)iter->second.RowAndColumn.y][(int)iter->second.RowAndColumn.x] = -1;
			node->getParent()->removeChildByTag(iter->second.tag);
			PeaShooterAnimations.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
}

void PeaShooter::JudgePeaAndZombiesPosition(Node* node)
{
	for (PeaIter = Peas.begin(); PeaIter != Peas.end(); /*++PeaIter*/)
	{
		/* ɾ�������㶹 */
		if (PeaIter->second.Pea->getPositionX() > 2000)
		{
			PeaIter->second.Pea->setOpacity(0);
		}
		
		for (global->Iter = global->Zombies.begin(); global->Iter != global->Zombies.end(); ++global->Iter)
		{
			if (!PeaIter->second.IsUsed &&                                                                                          /* �㶹û�б�ʹ�� */
				global->Iter->second.ZombiesAnimation->isVisible() && global->Iter->second.BloodVolume > 0 &&                       /* ��ʬû������ */
				global->Iter->second.ZombiesAnimation->getPositionX() < 1730 &&                                                     /* ��ʬ�����ͼ�� */
				fabs((global->Iter->second.ZombiesAnimation->getPositionY() + 83) - PeaIter->second.Pea->getPositionY()) <= 5 &&    /* �㶹�뽩ʬ��ͬһ�� */
				fabs(global->Iter->second.ZombiesAnimation->getPositionX() - PeaIter->second.Pea->getPositionX()) <= 25)            /* �㶹�뽩ʬ��ײ */
			{
				PeaIter->second.IsFire == true ? PlayPeaExplodeMusic(2) : PlayPeaExplodeMusic(global->Iter->second.MusicType); /* ����ָ������ */

				PeaIter->second.Pea->setOpacity(0);
				PeaIter->second.Pea->getChildByName("shadow")->setOpacity(0);
				
				global->Iter->second.ZombiesAnimation->runAction(Sequence::create(TintTo::create(0.2f, Color3B(100, 100, 100)), TintTo::create(0.2f, Color3B::WHITE), nullptr));

				if (global->Iter->second.ShieldVolume1 > 0)
				{
					global->Iter->second.ShieldVolume1 -= PeaIter->second.Attack;
				}
				else if (global->Iter->second.ShieldVolume > 0)
				{
					global->Iter->second.ShieldVolume -= PeaIter->second.Attack;
				}
				else
				{
					global->Iter->second.BloodVolume -= PeaIter->second.Attack;
				}

				CreatePeaExplode(PeaIter->second.Pea->getPosition(), node, PeaIter->second.IsFire == false ? 0 : 1);

				PeaIter->second.Attack = 0;
				PeaIter->second.IsUsed = true;

				break; /* һ���㶹ֻ�ܻ���һ����ʬ */
			}
		}

		/* ɾ�� */
		if (PeaIter->second.Pea->isVisible() == false)
		{
			Peas.erase(PeaIter++);
		}
		else
		{
			PeaIter++;
		}
	}
}

void PeaShooter::PlayPeaExplodeMusic(const int& MusicType)
{
	switch (MusicType)
	{
	case 0:
		rand() % 2 == 0 ? PlaySoundEffect("kernelpult") : PlaySoundEffect("kernelpult2");
		break;
	case 1:
		rand() % 2 == 0 ? PlaySoundEffect("shieldhit") : PlaySoundEffect("shieldhit2");
		break;
	case 2:
		PlaySoundEffect("firepea");
		break;
	}
}

void PeaShooter::CreatePea(const Vec2& position, Node* node)
{
	PeaTag++;

	auto Pea = SkeletonAnimation::createWithData(global->GlobalAnimationData.find("FirePea")->second);
	Pea->setAnimation(0, "normal", true);
	Pea->setPosition(position + Vec2(70, 90));
	Pea->setScale(0.5f);
	Pea->setTag(PeaTag);
	Pea->setGlobalZOrder(SetZOrder(position.y + 90));
	node->addChild(Pea);
	Pea->runAction(Sequence::create(MoveBy::create(2.5f, Vec2(1500, 0)), 
		CallFunc::create([=]() 
			{
				Pea->setVisible(false);
			}),nullptr));

	/* ����Ӱ�� */
	auto shadow = Sprite::create(global->ImagesPath.find("plantshadow")->second);
	shadow->setScale(1.7f);
	shadow->setName("shadow");
	shadow->setPosition(Vec2(0, -155));
	shadow->setGlobalZOrder(Pea->getGlobalZOrder());
	Pea->addChild(shadow, -1);

	_Pea pea;
	pea.Pea = Pea;
	pea.IsFire = false;
	pea.tag = PeaTag;
	pea.IsUsed = false;
	Peas.insert(pair<int, _Pea>(PeaTag, pea));
}

float PeaShooter::SetZOrder(const float& pos_y)
{
	const int pos[5] = { 765,627,489,351,213 };
	for (int i = 0; i < 5; i++)
		if (pos[i] == pos_y)
			return (i + 1) * 2;
	return 0;
} 

void PeaShooter::CreatePeaExplode(const Vec2& position, Node* node, const int& ID)
{
	static string Skin[] = { {"skin"},{"skin1"},{"skin2"},{"skin3"} };
	static string Animation[] = { {"Explode"},{"Explode1"},{"Explode2"},{"Explode3"},{"Explode4"} };

	auto PeaExplode = SkeletonAnimation::createWithData(global->GlobalAnimationData.find("PeaExplode")->second);
	PeaExplode->setPosition(position);
	PeaExplode->setAnimation(0, Animation[ID == 0 ? 4 : 3], false);
	PeaExplode->setScale(ID == 0 ? 1.0f : 1.4f);
	PeaExplode->setGlobalZOrder(SetZOrder(position.y));
	PeaExplode->setName("PeaExplode");
	if (!ID)
	{
		PeaExplode->setColor(Color3B(102, 206, 26));
	}
	node->addChild(PeaExplode);

	/*PeaExplode->setEventListener([=](spTrackEntry* entry, spEvent* event)
		{
			if (!strcmp(event->data->name, "Finished"))
			{
				PeaExplode->setEmptyAnimation(1, 0.1f);
				PeaExplode->setVisible(false);
			}
		});*/

	PeaExplode->runAction(Sequence::create(DelayTime::create(0.9f), CallFunc::create([=]()
		{
		    node->removeChildByName("PeaExplode");
		}), nullptr));
}
