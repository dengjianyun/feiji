#pragma once

#include "cocos2d.h"
#include "BulletManager.h"
#include "EnenemyManager.h"

USING_NS_CC;

class MainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	void updateBullet(float dt);
	void update(float) override;
private:
	Sprite *ownerSprite;
	BulletManager mBulletManger;
	EnenemyManager mEnenemyManager;
	Sprite* bg1;
	Sprite* bg2;
	Size size;
};