#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "cocos2d.h" 

class Platform : public cocos2d::Node {
public:
    static Platform* create(cocos2d::Vec2, cocos2d::Vec2, std::string);

    virtual bool init(cocos2d::Vec2, cocos2d::Vec2, std::string);
};

#endif //__PLATFORM_H__