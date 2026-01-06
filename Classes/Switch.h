#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "cocos2d.h" 

enum class State {
    On,
    Off
};

enum class kind_of {
    Normal,
    Red,
    Blue
};

class Switch : public cocos2d::Sprite {
public:
    ~Switch();

    static Switch* create(cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, std::string);

    void setState(State);

private:
    State _state = State::Off; //Switch凹み、ブロック透明状態がOn
    kind_of _kind = kind_of::Normal;

    cocos2d::PhysicsBody* _body = nullptr;
    cocos2d::PhysicsShapeBox* _extraShape = nullptr;
};

#endif //__SWITCH_H__