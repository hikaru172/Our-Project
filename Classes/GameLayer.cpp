#include "GameLayer.h"
#include "GameScene.h"
#include "Platform.h"
#include "Block.h"
#include "Character.h"
#include "Switch.h"
#include <iostream>
#include <cmath>

USING_NS_CC;

GameLayer* GameLayer::createLayer(int stageNumber) {
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


    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [&](PhysicsContact& contact) {

        auto bodyA = contact.getShapeA()->getBody();
        auto bodyB = contact.getShapeB()->getBody();

        PhysicsBody* chara = nullptr;
        PhysicsBody* platform = nullptr;
        PhysicsBody* Switch = nullptr;

        // 衝突情報を取得
        auto contactData = contact.getContactData();
        float normalX = contactData->normal.x; //normalはAがBを押す方向
        float normalY = contactData->normal.y;

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x02){
            chara = bodyA;
			platform = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x02 && bodyB->getCategoryBitmask() == 0x01) {
			chara = bodyB;
			platform = bodyA;
            normalX *= -1.0f;
            normalY *= -1.0f;
        } 
        
        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x04) {
            chara = bodyA;
            Switch = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x04 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Switch = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        auto vel = chara->getVelocity();

        if (normalY < -0.5f && chara->getVelocity().y <= 0) { //キャラクターの足と下のオブジェクトが接触
            _chara->onGround();
            chara->setVelocity(Vec2(vel.x, 0.0f));
            if (Switch) {
                _switchPressed = true;
            }
        }

        if (normalX < -0.6f) { //キャラクターの左側と左のオブジェクトが接触
            _chara->onHitLeft();
        }

        if (normalX > 0.6f) { //キャラクターの右側と右のオブジェクトが接触
			_chara->onHitRight();
        }

        return true; //trueを返すと衝突処理継続
    };

    contactListener->onContactSeparate = [&](PhysicsContact& contact) {

        auto bodyA = contact.getShapeA()->getBody();
        auto bodyB = contact.getShapeB()->getBody();
        PhysicsBody* chara = nullptr;
        PhysicsBody* platform = nullptr;
        PhysicsBody* Switch = nullptr;

        auto contactData = contact.getContactData();
        float normalX = contactData->normal.x;
        float normalY = contactData->normal.y;

        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x02) {
            chara = bodyA;
            platform = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x02 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            platform = bodyA;
            normalX *= -1;
            normalY *= -1;
        }
        if (bodyA->getCategoryBitmask() == 0x01 && bodyB->getCategoryBitmask() == 0x04) {
            chara = bodyA;
            Switch = bodyB;
        }
        else if (bodyA->getCategoryBitmask() == 0x04 && bodyB->getCategoryBitmask() == 0x01) {
            chara = bodyB;
            Switch = bodyA;
            normalX *= -1;
            normalY *= -1;
        }

        if (normalY < -0.5f) {
            _chara->onReleaseGround();
            if (Switch) {
                _switchPressed = false;
            }
        }
        if (normalX < -0.6f) {
            _chara->onReleaseLeft();
        }
        if (normalX > 0.6f) {
            _chara->onReleaseRight();
        }
    };

    //contactlistener登録
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


    //キー入力listener↓
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) { //[]はラムダ式(無名関数)
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
            _leftPressed = true;
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
            _rightPressed = true;
        if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
            if(_chara->canJump())
                _jumpPressed = true;
        };


    listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
            _leftPressed = false;
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
            _rightPressed = false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    _stageRoot = Node::create();
    _stageRoot->setPosition(Vec2::ZERO);
    this->addChild(_stageRoot);

    // ステージ初期化処理
    //init()とsetupStage()を分けることで、ステージごとに異なるものはsetupStage()を呼べば初期化できるように
    setupStage();

    return true;
}


void GameLayer::setupStage() {
    if (_stageRoot != nullptr) {
        _stageRoot->removeAllChildren();
    }

    _chara1 = Character::create(Vec2(120.0f, 280.0f), "characters/character_green_idle.png");
    _chara2 = Character::create(Vec2(70.0f, 280.0f), "characters/character_beige_idle.png");
    _stageRoot->addChild(_chara1, 1);
    _stageRoot->addChild(_chara2, 0);

    _chara1->onGround();
    _chara2->onGround();

    _chara1->reset_flip();
    _chara2->reset_flip();

    _chara = _chara1;
    _chara->setTag(1);

    _total = 0.0f;
    _total1 = 0.0f;
    _total2 = 0.0f;

    _charafixed = false;
    _chara1fixed = false;
    _chara2fixed = false;

    _charaswitchPressed = false;
    _chara1switchPressed = false;
    _chara2switchPressed = false;

    //ここから下にステージごとのオブジェクト配置処理を追加していく

    auto start_position = Vec2(0.0f, 0.0f);
    auto end_position = Vec2(10.0f, 3.0f);
    auto platform = Platform::create(start_position, end_position, "Platforms/terrain_grass_block");
    _stageRoot->addChild(platform);


    start_position = Vec2(12, 2);
    end_position = Vec2(16, 5);
    platform = Platform::create(start_position, end_position, "Platforms/terrain_grass_block");
    _stageRoot->addChild(platform);

    start_position = Vec2(17, 2);
    end_position = Vec2(20, 7);
    auto Block = Block::create(start_position, end_position, "Blocks/block_normal.png");
    _stageRoot->addChild(Block);


    start_position = Vec2(21, 2);
    end_position = Vec2(24, 5);
    platform = Platform::create(start_position, end_position, "Platforms/terrain_grass_block");
    _stageRoot->addChild(platform);

    start_position = Vec2(25, 2);
    end_position = Vec2(26, 7);
    Block = Block::create(start_position, end_position, "Blocks/block_normal.png");
    _stageRoot->addChild(Block);

    auto position = Vec2(15, 6);
    _switch = Switch::create(position, "gimic/switch_red.png");
    _stageRoot->addChild(_switch);

}



void GameLayer::update(float dt){

    CharacterInput input;
    input.left = _leftPressed;
    input.right = _rightPressed;
    input.jump = _jumpPressed;

    _chara->update(dt, input);
    _jumpPressed = false;

    float screenHalf = Director::getInstance()->getVisibleSize().width * 0.5f;
    float charaX = _chara->getPositionX();
    float speed = 200.0f;
    if (charaX > screenHalf) {
        if (_leftPressed && _chara->canMoveLeft()) {
            _total += dt;
        }
        else if (_rightPressed && _chara->canMoveRight()) {
            _total -= dt;
        }
    }

    if (_total * speed > 0.0f) {
        _total = 0.0f;
        this->setPositionX(0.0f);
    }
    else {
        this->setPositionX(_total * speed);
    }

    if (_switchPressed || _charaswitchPressed) {
        _switch->setState(State::On);
    }
    else {
        _switch->setState(State::Off);
    }
}


void GameLayer::chara_change() {
    auto now_chara_num = _chara->getTag();

    float screenHalf = Director::getInstance()->getVisibleSize().width * 0.5f;

    if (now_chara_num == 1) {
        _chara1 = _chara;
        _chara = _chara2;
        _chara->setTag(2);
        _total1 = _total;
        _total = _total2;
        _chara1fixed = _charafixed;
        _charafixed = _chara2fixed;
        _chara1->setLocalZOrder(0);
        _chara2->setLocalZOrder(1); //数字大きいほど手前に来る
        _chara1switchPressed = _switchPressed;
        _charaswitchPressed = _chara1switchPressed;
        _switchPressed = _chara2switchPressed;
    }
    else if (now_chara_num == 2) {
        _chara2 = _chara;
        _chara = _chara1;
        _chara->setTag(1);
        _total2 = _total;
        _total = _total1;
        _chara2fixed = _charafixed;
        _charafixed = _chara1fixed;
        _chara2->setLocalZOrder(0);
        _chara1->setLocalZOrder(1);
        _chara2switchPressed = _switchPressed;
        _charaswitchPressed = _chara2switchPressed;
        _switchPressed = _chara1switchPressed;
    }

}