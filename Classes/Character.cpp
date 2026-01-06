#include "Character.h"

USING_NS_CC;

Character* Character::create(Vec2 position, std::string sprite_name) {
    Character* ret = new Character();
    if (ret && ret->init(position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Character::init(Vec2 position , std::string sprite_name) {

    if (!Sprite::initWithFile(sprite_name)) {
        return false;
    }

    this->setPosition(position);


    auto material = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto body = PhysicsBody::createBox(Size(42.0f , 50.0f), material);
    body->setDynamic(true);
    body->setRotationEnable(false);
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x02 | 0x04);
    body->setContactTestBitmask(0x02 | 0x04);
    body->setVelocityLimit(550.0f);
    this->setPhysicsBody(body);


    size_t pos = sprite_name.find("green");
    if (pos != std::string::npos) {
        initAnimations1();
    }
    else {
        initAnimations2();
    }

    return true;
}

void Character::initAnimations1() {
    Vector<SpriteFrame*> idleFrames1;
    idleFrames1.pushBack(SpriteFrame::create("Characters/character_green_idle.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> walkFrames1;
    walkFrames1.pushBack(SpriteFrame::create("Characters/character_green_walk_a.png", Rect(0, 0, 42, 50)));
    walkFrames1.pushBack(SpriteFrame::create("Characters/character_green_walk_b.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> jumpFrames1;
    jumpFrames1.pushBack(SpriteFrame::create("Characters/character_green_jump.png", Rect(0, 0, 42, 50)));

    auto idleAnimation1 = Animation::createWithSpriteFrames(idleFrames1, 0.5f);
    idleAnimation1->setLoops(-1);

    auto walkAnimation1 = Animation::createWithSpriteFrames(walkFrames1, 0.2f);
    walkAnimation1->setLoops(-1);

    auto jumpAnimation1 = Animation::createWithSpriteFrames(jumpFrames1, 0.2f);
    jumpAnimation1->setLoops(-1);


    _idleAnim1 = Animate::create(idleAnimation1);
    _walkAnim1 = Animate::create(walkAnimation1);
    _jumpAnim1 = Animate::create(jumpAnimation1);

    _idleAnim1->retain();
    _walkAnim1->retain();
    _jumpAnim1->retain();


}

void Character::initAnimations2() {

    Vector<SpriteFrame*> idleFrames2;
    idleFrames2.pushBack(SpriteFrame::create("Characters/character_beige_idle.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> walkFrames2;
    walkFrames2.pushBack(SpriteFrame::create("Characters/character_beige_walk_a.png", Rect(0, 0, 42, 50)));
    walkFrames2.pushBack(SpriteFrame::create("Characters/character_beige_walk_b.png", Rect(0, 0, 42, 50)));

    Vector<SpriteFrame*> jumpFrames2;
    jumpFrames2.pushBack(SpriteFrame::create("Characters/character_beige_jump.png", Rect(0, 0, 42, 50)));

    auto idleAnimation2 = Animation::createWithSpriteFrames(idleFrames2, 0.5f);
    idleAnimation2->setLoops(-1);

    auto walkAnimation2 = Animation::createWithSpriteFrames(walkFrames2, 0.2f);
    walkAnimation2->setLoops(-1);

    auto jumpAnimation2 = Animation::createWithSpriteFrames(jumpFrames2, 0.2f);
    jumpAnimation2->setLoops(-1);


    _idleAnim2 = Animate::create(idleAnimation2);
    _walkAnim2 = Animate::create(walkAnimation2);
    _jumpAnim2 = Animate::create(jumpAnimation2);

    _idleAnim2->retain();
    _walkAnim2->retain();
    _jumpAnim2->retain();

}

void Character::changeAnimation(AnimState state) {

    stopAllActions();

    auto chara_tag = this->getTag();
    auto idleAnim = _idleAnim1;
    auto walkAnim = _walkAnim1;
    auto jumpAnim = _jumpAnim1;

    if (chara_tag == 2) {
        idleAnim = _idleAnim2;
        walkAnim = _walkAnim2;
        jumpAnim = _jumpAnim2;
    }


    switch (state) {
    case AnimState::Idle:
        runAction(idleAnim);
        break;

    case AnimState::Walk:
        runAction(walkAnim);
        break;

    case AnimState::Jump:
        runAction(jumpAnim);
        break;
    }

}


void Character::update(float dt, const CharacterInput& input) {

    auto body = this->getPhysicsBody();
    Vec2 vel = body->getVelocity();
    float speed = 200.0f;


    if (input.left && !_leftlimited) {
        vel.x = -speed;
        setFlippedX(true);
        if(!_jumplimited)
            _state = AnimState::Walk;
    }
    else if (input.right && !_rightlimited) {
        vel.x = speed;
        setFlippedX(false);
        if (!_jumplimited)
            _state = AnimState::Walk;
    }
    else{
        vel.x = 0;
        if (_state != AnimState::Jump) {
            _state = AnimState::Idle;
        }
    }


    if (input.jump && !_jumplimited) {
        vel.y = 500.0f;
        _jumplimited = true;
        _state = AnimState::Jump;
    }  

    body->setVelocity(vel);

    if (_state != _prevState) {
        changeAnimation(_state);
        _prevState = _state;
    }

}

void Character::onGround() {
    _jumplimited = false;
    if (_state == AnimState::Jump) {
        _state = AnimState::Idle;
    }
}

void Character::onHitLeft() {
    _leftlimited = true;
}

void Character::onHitRight() {
    _rightlimited = true;
}

void Character::onReleaseLeft() {
    _leftlimited = false;
}

void Character::onReleaseRight() {
    _rightlimited = false;
}

void Character::onReleaseGround() {
    _jumplimited = true;
}

bool Character::canMoveLeft() const {
    return !_leftlimited;
}

bool Character::canMoveRight() const {
    return !_rightlimited;
}

bool Character::canJump() const {
    return !_jumplimited;
}

void Character::reset_flip() {
    setFlippedX(false);
}

Character::~Character() {
    CC_SAFE_RELEASE(_idleAnim1);
    CC_SAFE_RELEASE(_walkAnim1);
    CC_SAFE_RELEASE(_jumpAnim1);
    CC_SAFE_RELEASE(_idleAnim2);
    CC_SAFE_RELEASE(_walkAnim2);
    CC_SAFE_RELEASE(_jumpAnim2);
}