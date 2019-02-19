#include "BulletManager.h"

BulletManager::BulletManager():bulletList(Vector<Sprite *>()), bulletSpeed(700)
{
	bullet1Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet1.png");
}


BulletManager::~BulletManager()
{

}

void BulletManager::produceBullet(Scene* scene, Vec2 postion)
{
	auto bullet = Sprite::createWithSpriteFrame(bullet1Frame);
	bullet->setAnchorPoint(Vec2(0.5, 0));
	bullet->setPosition(postion);
	scene->addChild(bullet);
	bullet->setTag(1);
	bulletList.pushBack(bullet);
}

int BulletManager::getBulletSpeed() {
	return  bulletSpeed;
}

void BulletManager::setBulletSpeed(int speed) {
	this->bulletSpeed = speed;
}

Vector<Sprite *> BulletManager::getBulletList() {
	return bulletList;
}
