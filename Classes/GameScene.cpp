#include "GameScene.h"
#include "GameLayer.h"

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
    world->setGravity(Vec2(0, -980));


    // ゲーム用のLayerを追加
    auto gameLayer = GameLayer::create(_stageNumber);
    this->addChild(gameLayer);

    return true;
}