#ifndef __BGLAYER_H__
#define __BGLAYER_H__

#include "cocos2d.h" 

class BGLayer : public cocos2d::Layer {
public:
    static BGLayer* createLayer(int);

    virtual bool init(int);

    static BGLayer* create(int);

};

#endif //__BGLAYER_H__