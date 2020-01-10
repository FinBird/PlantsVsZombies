#pragma once
#include "cocos2d.h"
#include "spine/spine.h"
#include "AudioEngine.h"
#include "GlobalVariable.h"
#include "spine\spine-cocos2dx.h"

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

class  Plants:public Node
{
public:
	void SetImagePosition(Node* node,const Vec2& vec2);

protected:
	virtual void PlaySoundEffect(const std::string& MusicName);
	/* ����ֲ��ͼƬ */
	virtual Sprite* CreateImage(const std::string& name, const Vec2& position, Node* node);
	/* ����ֲ�ﶯ�� */                 
	virtual SkeletonAnimation* CreateAnimation(const std::string& name, const std::string& name1, const Vec2& position, const float& scale = 1.0f, const float& scale1 = 1.0f, bool loop = true);
	/* ��ʬ��ֲ�� */
	virtual void ZombiesEatPlants(map<int, Global::_Zombies>::iterator Iter, float* plantbloodvolum, SkeletonAnimation* plantanimation);

private:
	float SetZOrder(const float& pos_y);

protected:
	Global* global = Global::getInstance();

};

extern Plants* Plant;
