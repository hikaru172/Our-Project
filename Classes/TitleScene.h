#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h" 

class TitleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onStartButtonPressed(cocos2d::Ref* sender);

    CREATE_FUNC(TitleScene);
};

#endif // __TITLE_SCENE_H__
