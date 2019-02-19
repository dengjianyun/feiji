#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	void produceBullet(Scene* scene, Vec2 postion);
	int getBulletSpeed();
	void setBulletSpeed(int speed);
    Vector<Sprite*> getBulletList();
private:
	SpriteFrame* bullet1Frame;
	Vector<Sprite*> bulletList;
	int bulletSpeed;
};

