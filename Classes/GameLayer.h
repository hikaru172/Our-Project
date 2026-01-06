#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h" 
#include "Character.h"
#include "Switch.h"

class GameLayer : public cocos2d::Layer {
public:
    //CREATE_FUNCマクロはcreate()に引数を持たせられないので自分で定義
    static GameLayer* createLayer(int);

    virtual bool init(int);

    void update(float);

    void chara_change();

    void setupStage(); // ステージ初期化用


    Character* _chara;
    Character* _chara1;
    Character* _chara2;

    Switch* _switch;

    Node* _stageRoot;

private:

    int _stageNumber;

    bool _leftPressed = false;
    bool _rightPressed = false;
    bool _jumpPressed = false;

    bool _switchPressed = false;

    bool _charafixed = false;
    bool _chara1fixed = false;
    bool _chara2fixed = false;

    bool _charaswitchPressed = false;
    bool _chara1switchPressed = false;
    bool _chara2switchPressed = false;

    float _diff = 0.0f;
    float _total = 0.0f;
    float _total1 = 0.0f;
    float _total2 = 0.0f;
};

#endif //__GAME_LAYER_H__