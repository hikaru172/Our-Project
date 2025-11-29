#ifndef __STAGE_SELECT_SCENE_H__
#define __STAGE_SELECT_SCENE_H__

#include "cocos2d.h" 

class StageSelectScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onButtonPressed(cocos2d::Ref* sender);

    CREATE_FUNC(StageSelectScene);
};

#endif //__STAGE_SELECT_SCENE_H__