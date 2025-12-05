#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h" 

class GameScene : public cocos2d::Scene
{
public:
    //基本クラスのcocos2d::Scene*型にしても動きはする
    static GameScene* createScene(int);

    virtual bool init(int);

    // 通常のCREATE_FUNCでは引数が渡せないので自前で用意
    static GameScene* create(int);

private:
    int _stageNumber = 0;
};

#endif //__GAME_SCENE_H__