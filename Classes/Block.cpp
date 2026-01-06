#include "Block.h"
#include <string>

USING_NS_CC;

Block* Block::create(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    Block* ret = new Block();
    if (ret && ret->init(start_position, end_position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Block::init(Vec2 start_position, Vec2 end_position, std::string sprite_name) {
    if (!Node::init()) {
        return false;
    }

    auto pos = sprite_name.find("red");
    if (pos != std::string::npos) {
        _kind2 = kind_of::Red;
    } 
    pos = std::string::npos;
    pos = sprite_name.find("blue");
    if (pos != std::string::npos) {
        _kind2 = kind_of::Blue;
    }

    float Xamount = end_position.x - start_position.x + 1.0f; //トータルのブロック数
    float Yamount = end_position.y - start_position.y + 1.0f;

    for (float j = 0.0f; j < Yamount; j++) {

        for (float i = 0.0f; i < Xamount; i++) {

            auto sprite = Sprite::create(sprite_name);
            sprite->setPosition(Vec2(48.0f * i, 48.0f * j));
            this->addChild(sprite);

        }
    }

    auto Position = Vec2(24.0f + 48.0 * start_position.x, 24.0f + 48.0f * start_position.y);
    this->setPosition(Position);


    auto platmaterial = PhysicsMaterial(1.0f, 0.0f, 0.0f);
    auto platbody = PhysicsBody::createBox(Size(48.0f * Xamount, 48.0f * Yamount), platmaterial, Vec2((Xamount / 2.0f) * 48.0f - 24.0f, (Yamount / 2.0f) * 48.0f - 24.0f));
    platbody->setDynamic(false);
    platbody->setCategoryBitmask(0x02);
    platbody->setCollisionBitmask(0x01);
    platbody->setContactTestBitmask(0x01);
    this->setPhysicsBody(platbody);

    return true;
}

void Block::setState(State state) {
    _state2 = state;

    std::string sprite_name = "Blocks/block";
    if (_kind2 == kind_of::Red) {
        sprite_name.append("_red");
    }
    else if (_kind2 == kind_of::Blue) {
        sprite_name.append("_blue");
    }

    if (state == State::Off) {
        this->setSpriteFrame("Blocks/block_trans.png");
        this->getPhysicsBody()->setEnabled(false);
    }
    else {
        this->setSpriteFrame(sprite_name);
        this->getPhysicsBody()->setEnabled(true);
    }
}