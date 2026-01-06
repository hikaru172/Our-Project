#include "BGLayer.h"

USING_NS_CC;

BGLayer* BGLayer::createLayer(int stageNumber)
{
    auto layer = BGLayer::create(stageNumber);
    return layer;
}

BGLayer* BGLayer::create(int stageNumber) {
    BGLayer* ret = new BGLayer();
    if (ret && ret->init(stageNumber)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool BGLayer::init(int stageNumber) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i <= 4; i++) {
        auto BGsprite1 = Sprite::create("BG/background_fade_trees.png");
        BGsprite1->setPosition(180.0f + 360.0f * i, 180.0f);
        this->addChild(BGsprite1);
        auto BGsprite2 = Sprite::create("BG/background_clouds.png");
        BGsprite2->setPosition(180.0f + 360.0f * i, 540.0f);
        this->addChild(BGsprite2);
        //auto BGsprite3 = Sprite::create("BG/background_solid_sky.png");
        //BGsprite3->setPosition(128.0f + 256.0f * i, 640.0f);
        //this->addChild(BGsprite3);
    }

    return true;
}