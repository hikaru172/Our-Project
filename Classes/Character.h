#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h" 

enum class AnimState {
    Idle,
    Walk,
    Jump
};

struct CharacterInput {
    bool left = false;
    bool right = false;
    bool jump = false;
};

class Character : public cocos2d::Sprite {
public:

    virtual ~Character();

    static Character* create(cocos2d::Vec2 ,std::string);

    virtual bool init(cocos2d::Vec2, std::string);


    void update(float, const CharacterInput&);

    void onGround();
    void onHitLeft();
    void onHitRight();

    void onReleaseGround();
    void onReleaseLeft();
    void onReleaseRight();

    void reset_flip();

    bool canMoveLeft() const;
    bool canMoveRight() const;
    bool canJump() const;

private:

    AnimState _state = AnimState::Idle;
    AnimState _prevState = AnimState::Idle;

    cocos2d::Animate* _idleAnim1;
    cocos2d::Animate* _idleAnim2;
    cocos2d::Animate* _walkAnim1;
    cocos2d::Animate* _walkAnim2;
    cocos2d::Animate* _jumpAnim1;
    cocos2d::Animate* _jumpAnim2;

    void initAnimations1();
    void initAnimations2();
    void changeAnimation(AnimState state);

    bool _leftlimited = false;
    bool _rightlimited = false;
    bool _jumplimited = false;
};

#endif //__CHARACTERS_H__