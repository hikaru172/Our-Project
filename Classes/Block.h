#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h" 
#include "Switch.h"

class Block : public cocos2d::Sprite {
public:
    static Block* create(cocos2d::Vec2, cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, cocos2d::Vec2, std::string);

    void setState(State state);

private:
    State _state2 = State::Off;
    kind_of _kind2 = kind_of::Normal;
};

#endif //__BLOCK_H__