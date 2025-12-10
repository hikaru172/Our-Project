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

    this->scheduleUpdate();  //これを書かないとupdate()が呼ばれない

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


    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [&](PhysicsContact& contact) {

        auto bodyA = contact.getShapeA()->getBody();
        auto bodyB = contact.getShapeB()->getBody();

        PhysicsBody* chara = nullptr;
        PhysicsBody* platform = nullptr;

        // 衝突情報を取得
        auto contactData = contact.getContactData();
        float normalX = contactData->normal.x; //normalはAがBを押す方向
        float normalY = contactData->normal.y;

        // ここに処理を書いていく
        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x02){
            chara = bodyA;
			platform = bodyB;
        }
        else if (bodyA->getCategoryBitmask() & 0x02 && bodyB->getCategoryBitmask() & 0x01) {
			chara = bodyB;
			platform = bodyA;
            normalX *= -1;
        }

        if (normalX < -0.5f) {
            _leftlimited = true;
        }

        if (normalX > 0.5f) {
			_rightlimited = true;
        }

        return true; //trueを返すと衝突処理継続
    };

    contactListener->onContactSeparate = [&](PhysicsContact& contact) {
        _leftlimited = false;
        _rightlimited = false;
        return true;
    };

    // リスナー登録
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    // ステージ初期化処理
    //init()とsetupStage()を分けることで、ステージごとに異なるものはsetupStage()を呼べば初期化できるように
    setupStage();

    return true;
}


//ステージごとのオブジェクト配置(初期化)処理
void GameLayer::setupStage() {

    _chara = Sprite::create("characters/character_green_front.png");
    _chara->setPosition(250, 700);

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

    //ここから下にステージごとのオブジェクト配置処理を追加していく

    for (int i = 2; i <= 5; i++) {
        auto platform = Platform::create(Vec2(48.0f*i, 500.0f-(48.0f*i)), "Platforms/terrain_grass_block.png");
        auto platmaterial = PhysicsMaterial(1.0f, 0.0f, 0.0f);
        auto platbody = PhysicsBody::createBox(Size(48.0f, 48.0f),platmaterial);
        platbody->setDynamic(false);
        platbody->setCategoryBitmask(0x02);
        //接触イベントを発生させたいので、テスト対象に 0x01 を指定
        platbody->setContactTestBitmask(0x01);
        platform->setPhysicsBody(platbody);
        this->addChild(platform);
    }

	auto charamaterial = PhysicsMaterial(1.0f, 0.0f, 0.0f); //摩擦係数、反発係数、密度
    //キャラクターの見た目にぴったり合う長方形の当たり判定を作っている
    auto charabody = PhysicsBody::createBox(Size(40.0f,50.0f),charamaterial);
    //setDynamic(true)にすると、重力・衝突など物理シミュレーションの影響を受ける
    //(false) にすると、固定オブジェクト（Static Body）になり、壁や地面のように動かない
    charabody->setDynamic(true);
    charabody->setRotationEnable(false);
    charabody->setCategoryBitmask(0x01);
    //地面(0x02) と接触イベントを発生させたいので、テスト対象に 0x02 を指定
    charabody->setContactTestBitmask(0x02);
    //作った物理ボディをスプライトにアタッチ（紐付け）
    _chara->setPhysicsBody(charabody);
    this->addChild(_chara);
}

void GameLayer::update(float dt){

    auto body = _chara->getPhysicsBody();
    Vec2 vel = body->getVelocity();
    float speed = 200.0f;

    if (_leftPressed && !_leftlimited)
        vel.x = -speed;
    else if (_rightPressed && !_rightlimited)
        vel.x = speed;
    else
        vel.x = 0;



    body->setVelocity(vel);
}