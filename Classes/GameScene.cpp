#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "BGLayer.h"

USING_NS_CC;

GameScene* GameScene::createScene(int stageNumber) {
    auto scene = GameScene::create(stageNumber);
    return scene;
}

//CREATE_FUNCが使えない代わりに自分で定義
GameScene* GameScene::create(int stageNumber) {
    GameScene* ret = new GameScene();
    if (ret && ret->init(stageNumber)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool GameScene::init(int stageNumber) {
    if (!Scene::initWithPhysics()) {  //物理付きシーンを作成
        return false;
    }

    _stageNumber = stageNumber;

    //重力を設定
    auto world = this->getPhysicsWorld();
    world->setGravity(Vec2(0, -750));


    // ゲーム用のLayerを追加
    auto gameLayer = GameLayer::createLayer(_stageNumber);
    gameLayer->setName("GameLayer");
    this->addChild(gameLayer, 1);

    auto UILayer = UILayer::createLayer(_stageNumber);
    this->addChild(UILayer, 2);

    auto BGLayer = BGLayer::createLayer(_stageNumber);
    this->addChild(BGLayer, 0);

    return true;
}