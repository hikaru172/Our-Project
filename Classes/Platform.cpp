#include "Platform.h"

USING_NS_CC;

Platform* Platform::create(Vec2 position, std::string sprite_name) {
    Platform* ret = new Platform();
    if (ret && ret->init(position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Platform::init(Vec2 position, std::string sprite_name) {
    if (!Node::init()) {
        return false;
    }

    _sprite = Sprite::create(sprite_name);

    // sprite の位置はローカル座標で OK
    _sprite->setPosition(Vec2::ZERO);
    this->addChild(_sprite);

    // Platform 自体を目的の位置に
    this->setPosition(position);
    
    return true;
}