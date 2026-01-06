#ifndef __UILAYER_H__
#define __UILAYER_H__

#include "cocos2d.h" 

class UILayer : public cocos2d::Layer {
public:
    static UILayer* createLayer(int);

    virtual bool init(int);

    static UILayer* create(int);

    void onButtonPressed(cocos2d::Ref* sender);
    void onRepeatButtonPressed(cocos2d::Ref* sender);

};

#endif //__UILAYER_H__