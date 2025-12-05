#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h" 

class GameLayer : public cocos2d::Layer {
public:
    //CREATE_FUNCマクロはcreate()に引数を持たせられないので自分で定義
    static GameLayer* create(int);

    virtual bool init(int);

    void update(float dt);

    bool _leftPressed = false;
    bool _rightPressed = false;

private:
    cocos2d::Sprite* _chara;

    int _stageNumber;

    void setupStage(); // ステージ初期化用
};

#endif //__GAME_LAYER_H__