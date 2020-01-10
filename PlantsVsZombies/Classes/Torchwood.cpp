#include "Torchwood.h"

Torchwood* Torchwood::_instance = nullptr;

Torchwood* Torchwood::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)Torchwood;
	}
	return _instance;
}


void Torchwood::Initialization()
{
	Torchwood::getInstance()->TorchwoodAnimation.clear();
}

void Torchwood::CreateTorchwoodImage(const Vec2& position, Node* node)
{
	TorchwoodImage = CreateImage("Torchwood", position, node);
	TorchwoodImage->setScale(1.5f);
}

void Torchwood::CreateTorchwoodAnimation(const Vec2& RowAndColumn, const Vec2& position, Node* node, const int& order, const int& tag)
{
	/* �������� */
	auto TorchwoodAnimations = CreateAnimation("Torchwood", "animation", position, 0.8f, 1.5f);
	TorchwoodAnimations->setAnchorPoint(Vec2(0, 0));
	TorchwoodAnimations->setScale(1.6f);
	TorchwoodAnimations->getChildByName("plantshadow")->setPosition(Vec2(0, 10));
	node->addChild(TorchwoodAnimations, order, tag);

	_TorchwoodAnimation animation;
	animation.Animation = TorchwoodAnimations;
	animation.BloodVolume = 300;
	animation.tag = tag;
	animation.RowAndColumn = RowAndColumn;
	animation.position = position;

	TorchwoodAnimation.insert(pair<int, _TorchwoodAnimation>(tag, animation));
}

void Torchwood::CreateTorchwoodListener(Node* node)
{
	node->schedule(CC_CALLBACK_1(Torchwood::Update, this, node), "UpdateTorchwood");
}

void Torchwood::Update(float Time, Node* node)
{
	JudgeTorchwoodAndPeaPosition(node);     /* �㶹������׮λ���ж� */

	JudgeTorchwoodAndZombiesPosition(node); /* ��ʬ������׮λ���ж� */
}

void Torchwood::JudgeTorchwoodAndZombiesPosition(Node* node)
{
	for (TorchwoIter = TorchwoodAnimation.begin(); TorchwoIter != TorchwoodAnimation.end(); /*++TorchwoIter*/)
	{
		for (global->Iter = global->Zombies.begin(); global->Iter != global->Zombies.end(); ++global->Iter)
		{
			if (global->Iter->second.BloodVolume > 0 && global->Iter->second.ZombiesAnimation->isVisible() &&                                 /* ��ʬû������ */
				fabs((global->Iter->second.ZombiesAnimation->getPositionY() - 10) - TorchwoIter->second.Animation->getPositionY()) <= 10)     /* ��ʬ��ֲ����ͬһ�� */
			{
				if (TorchwoIter->second.BloodVolume > 0 &&                                                                                    /* ֲ��û���� */
					fabs(global->Iter->second.ZombiesAnimation->getPositionX() - TorchwoIter->second.Animation->getPositionX()) <= 80)        /* ��ʬ����ֲ�� */
				{
					ZombiesEatPlants(global->Iter, &TorchwoIter->second.BloodVolume, TorchwoIter->second.Animation);
				}
				if (TorchwoIter->second.BloodVolume <= 0 && !global->Iter->second.Speed && global->Iter->second.IsEat)
				{
					global->Iter->second.IsEat = false;
					if (global->Iter->second.AnimationID != 10)
					{
						global->Iter->second.ZombiesAnimation->setMix("Zombies_Eat", Zombie::getInstance()->ZombiesTypeAniamtion(global->Iter->second.ZombiesType), 1.3f);
						global->Iter->second.ZombiesAnimation->addAnimation(1, Zombie::getInstance()->ZombiesTypeAniamtion(global->Iter->second.ZombiesType), true);
						global->Iter->second.Speed = global->Iter->second.CaveSpeed;
					}
				}
			}
		}
		/* ɾ�������׮ */
		if (TorchwoIter->second.BloodVolume <= 0)
		{
			global->MapSize.PlantsMap[(int)TorchwoIter->second.RowAndColumn.y][(int)TorchwoIter->second.RowAndColumn.x] = -1;
			node->getParent()->removeChildByTag(TorchwoIter->second.tag);
			TorchwoodAnimation.erase(TorchwoIter++);
		}
		else
		{
			TorchwoIter++;
		}
	}
}

void Torchwood::JudgeTorchwoodAndPeaPosition(Node* node)
{
	for (TorchwoIter = TorchwoodAnimation.begin(); TorchwoIter != TorchwoodAnimation.end(); ++TorchwoIter)
	{
		for (PeaShooters->PeaIter = PeaShooters->Peas.begin(); PeaShooters->PeaIter != PeaShooters->Peas.end(); ++PeaShooters->PeaIter)
		{
			if (fabs(TorchwoIter->second.Animation->getPositionY() + 90 - PeaShooters->PeaIter->second.Pea->getPositionY()) <= 10 &&       /* �㶹������׮��ͬһ�� */
				fabs(TorchwoIter->second.Animation->getPositionX() - PeaShooters->PeaIter->second.Pea->getPositionX()) <= 20)              /* �㶹���������׮ */
			{	
				if (!PeaShooters->PeaIter->second.IsFire)                                                                                  /* �㶹û��ȼ�� */
				{
					PeaShooters->PeaIter->second.Pea->setAnimation(0, "fire", true);
					PeaShooters->PeaIter->second.Pea->setScale(1.5f); 
					PeaShooters->PeaIter->second.Pea->getChildByName("shadow")->setPosition(Vec2(0, -52));
					PeaShooters->PeaIter->second.Pea->getChildByName("shadow")->setScaleY(0.7f);
					PeaShooters->PeaIter->second.Pea->getChildByName("shadow")->setScaleX(1.0f);
					PeaShooters->PeaIter->second.Attack *= 2.0f;
					PeaShooters->PeaIter->second.IsFire = true;
				}
				if (PeaShooters->PeaIter->second.TorchwoodTag != TorchwoIter->second.tag)
				{
					PlaySoundEffect("firepea");
					PeaShooters->PeaIter->second.TorchwoodTag = TorchwoIter->second.tag;
					PeaShooters->PeaIter->second.FireNumbers++;
				}
				if (PeaShooters->PeaIter->second.FireNumbers > 1)
				{
					PeaShooters->PeaIter->second.Attack = 0;
					PeaShooters->PeaIter->second.IsUsed = true;
					PeaShooters->PeaIter->second.Pea->setOpacity(0);
					PeaShooters->PeaIter->second.Pea->getChildByName("shadow")->setVisible(false);
				}
			}
		}

		for (FirePeaShooters->FirePeaIter = FirePeaShooters->FirePeas.begin(); FirePeaShooters->FirePeaIter != FirePeaShooters->FirePeas.end(); ++FirePeaShooters->FirePeaIter)
		{
			if (fabs(TorchwoIter->second.Animation->getPositionY() + 90 - FirePeaShooters->FirePeaIter->second.Pea->getPositionY()) <= 10 &&       /* ���㶹������׮��ͬһ�� */
				fabs(TorchwoIter->second.Animation->getPositionX() - FirePeaShooters->FirePeaIter->second.Pea->getPositionX()) <= 20)              /* ���㶹���������׮ */
			{
				FirePeaShooters->FirePeaIter->second.Attack = 0;
				FirePeaShooters->FirePeaIter->second.IsUsed = true;
				FirePeaShooters->FirePeaIter->second.Pea->setOpacity(0);
				FirePeaShooters->FirePeaIter->second.Pea->getChildByName("shadow")->setVisible(false);
			}
		}
	}
}
