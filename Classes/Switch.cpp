#include "Switch.h"
#include <string>

USING_NS_CC;

Switch* Switch::create(Vec2 position, std::string sprite_name) {
    Switch* ret = new Switch();
    if (ret && ret->init(position, sprite_name)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

bool Switch::init(Vec2 position, std::string sprite_name) {
    if (!Sprite::initWithFile(sprite_name)) {
        return false;
    }

    auto pos = sprite_name.find("red");
    if (pos != std::string::npos) {
        _kind = kind_of::Red;
    }
    else {
        _kind = kind_of::Blue;
    }

    position.x = position.x * 48.0f + 24.0f;
    position.y = position.y * 48.0f + 15.0f;

    this->setPosition(position);

    _body = PhysicsBody::create();

    auto baseShape = PhysicsShapeBox::create(Size(48.0f, 21.0f),PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2(0.0f, -4.5f));
    _body->addShape(baseShape);

    _extraShape = PhysicsShapeBox::create(Size(48.0f, 9.0f),PHYSICSSHAPE_MATERIAL_DEFAULT, Vec2(0.0f, 10.5f));
    _extraShape->retain();

    _body->setDynamic(false);
    _body->setCategoryBitmask(0x04);
    _body->setContactTestBitmask(0x01);
    _body->setCollisionBitmask(0x01);

    this->setPhysicsBody(_body);

    _state = State::Off;

    return true;
}

void Switch::setState(State state) { 
    if (_state == state) return;

    _state = state;
    std::string sprite_name = "gimic/switch";
    if (_kind == kind_of::Red) {
        sprite_name.append("_red");
    }
    else if (_kind == kind_of::Blue) {
        sprite_name.append("_blue");
    }


    if (_state == State::On) { // ‰Ÿ‚³‚ê‚½ó‘Ô
        sprite_name.append("_pressed.png");
        _extraShape->setSensor(true); //“–‚½‚è”»’è‚ðÁ‚·
    }
    else { // ‰Ÿ‚³‚ê‚Ä‚È‚¢ó‘Ô
        sprite_name.append(".png");
        _extraShape->setSensor(false);
    }

    this->setTexture(sprite_name);

}

Switch::~Switch() {
    CC_SAFE_RELEASE(_extraShape);
}