#include "GameLayer.h"
#include "Platform.h"

USING_NS_CC;

GameLayer* GameLayer::create(int stageNumber) {
    GameLayer* ret = new GameLayer();
    if (ret && ret->init(stageNumber)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool GameLayer::init(int stageNumber) {
    if (!Layer::init()) {
        return false;
    }

    this->scheduleUpdate();  // ← これを書かないと update が呼ばれない！

    _stageNumber = stageNumber;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF(
        StringUtils::format("Stage %d", _stageNumber), //文字列をフォーマット（整形）する関数
        "fonts/RiiPopkkR.otf",
        32
    );

    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);




    // ステージ初期化処理
    //init()とsetupStage()を分けることで、ステージごとに異なるものはsetupStage()を呼べば初期化できるように
    setupStage();

    return true;
}


//ステージごとのオブジェクト配置(初期化)処理
void GameLayer::setupStage() {

    _chara = Sprite::create("human_front.png");
    _chara->setPosition(250, 300);
    this->addChild(_chara);

    // キーイベント（PC用）
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) { //[]はラムダ式(無名関数)
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
            _leftPressed = true;
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
            _rightPressed = true;
        };

    listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
            _leftPressed = false;
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
            _rightPressed = false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    for (int i = 0; i <= 50; i++) {
        auto platform = Platform::create(Vec2(30*i, 213), "human_front.png");
        this->addChild(platform);
    }
}

void GameLayer::update(float dt){
    float speed = 200;
    Vec2 pos = _chara->getPosition();

    if (_leftPressed)
        pos.x -= speed * dt;

    if (_rightPressed)
        pos.x += speed * dt;

    _chara->setPosition(pos);

}