#include "MainScene.h"

cocos2d::Scene *MainScene::createScene() {
    return MainScene::create();
}

bool MainScene::init() {
    size = Director::getInstance()->getVisibleSize();

    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("gameArts.plist");

    auto bgFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("background_2.png");
    bg1 = Sprite::createWithSpriteFrame(bgFrame);
    bg1->setPosition(Vec2(0, 0));
    bg1->setAnchorPoint(Vec2(0,0));
    this->addChild(bg1);

    bg2 = Sprite::createWithSpriteFrame(bgFrame);
    bg2->setPosition(Vec2(0, size.height - 1));
    bg2->setAnchorPoint(Vec2(0,0));
    this->addChild(bg2);


    auto ownerFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_fly_1.png");
    auto ownerFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_fly_2.png");
    this->ownerSprite = Sprite::createWithSpriteFrame(ownerFrame1);

    Vector<SpriteFrame*> animFrames;
    animFrames.pushBack(ownerFrame1);
    animFrames.pushBack(ownerFrame2);
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    Animate* animate = Animate::create(animation);
    this->ownerSprite->runAction(RepeatForever::create(animate));

    ownerSprite->setAnchorPoint(Vec2(0.5, 0.5));
    ownerSprite->setPosition(size.width / 2, 200);
    this->addChild(ownerSprite);

    log("KK size width:%f height:%f", size.width, size.height);

    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [=](Touch *touch, Event *event) {
        return ownerSprite->getBoundingBox().containsPoint(touch->getLocation());
    };

    listener->onTouchMoved = [=](Touch *touch, Event *event) {
        log("KK ownerSprite x:%f y:%f", ownerSprite->getPosition().x, ownerSprite->getPosition().y);
        log("KK touch x:%f y:%f", touch->getLocation().x, touch->getLocation().y);
        ownerSprite->setPosition(touch->getLocation());
        return true;
    };


    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    mBulletManger = BulletManager();
    mEnenemyManager = EnenemyManager();

    schedule(schedule_selector(MainScene::updateBullet), 0.5);
    scheduleUpdate();

    return true;
}

void MainScene::updateBullet(float dt) {
    mBulletManger.produceBullet(this, ownerSprite->getPosition() + Vec2(0, ownerSprite->getContentSize().height / 2));
}

void MainScene::update(float dt) {
    log("before bg1 postion x %f y %f , bg2 postion x %f  y %f", bg1->getPosition().x, bg1->getPosition().y, bg2->getPosition().x, bg2->getPosition().y);
    bg1->setPosition(bg1->getPosition() - Vec2(0,dt * 100));
    bg2->setPosition(bg2->getPosition() - Vec2(0,dt * 100));

    log("bg1 postion x %f y %f , bg2 postion x %f  y %f", bg1->getPosition().x, bg1->getPosition().y, bg2->getPosition().x, bg2->getPosition().y);

    if(bg1->getPosition().y + size.height < 1){
        bg1->setPosition(Vec2(0,size.height * 2  +  bg1->getPosition().y - 2));
    }else if(bg2->getPosition().y + size.height < 1){
        bg2->setPosition(Vec2(0,size.height * 2  +  bg2->getPosition().y - 2));
    }

    for (Sprite *bullet : mBulletManger.getBulletList()) {
        bullet->setPosition(bullet->getPosition() + Vec2(0, dt * mBulletManger.getBulletSpeed()));
    }


    log("total bullet is : %d", mBulletManger.getBulletList().size());
}
