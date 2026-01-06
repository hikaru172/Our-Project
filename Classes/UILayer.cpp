#include "UILayer.h"
#include "GameLayer.h"

USING_NS_CC;

UILayer* UILayer::createLayer(int stageNumber)
{
    auto layer = UILayer::create(stageNumber);
    return layer;
}

UILayer* UILayer::create(int stageNumber) {
    UILayer* ret = new UILayer();
    if (ret && ret->init(stageNumber)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool UILayer::init(int stageNumber) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto label = Label::createWithTTF(
        StringUtils::format("Stage %d", stageNumber), //文字列をフォーマットする関数
        "fonts/RiiPopkkR.otf",
        32
    );
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);



    auto normal_Sprite = Sprite::create("UI/stageselect.png");
    auto selected_Sprite = Sprite::create("UI/stageselect2.png");

    //この内部ではSpriteをMenuItemSpriteの子ノードとして追加している
    auto chara_change_Item = MenuItemSprite::create(
        normal_Sprite,
        selected_Sprite,
        CC_CALLBACK_1(UILayer::onButtonPressed, this)
    );
    chara_change_Item->setPosition(Vec2(1200.0f, 670.0f));


    auto repeat_Sprite = Sprite::create("UI/icon_repeat_outline.png");
    auto Repeat_Item = MenuItemSprite::create(
        repeat_Sprite,
        repeat_Sprite,
        CC_CALLBACK_1(UILayer::onRepeatButtonPressed, this)
    );
    Repeat_Item->setPosition(Vec2(50.0f, 690.0f));


    auto menu = Menu::create(chara_change_Item, Repeat_Item, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void UILayer::onButtonPressed(Ref* sender)
{

    auto gameLayer = dynamic_cast<GameLayer*>(
        this->getParent()->getChildByName("GameLayer")
        );

    if (gameLayer)
    {
        gameLayer->chara_change();
    }
}

void UILayer::onRepeatButtonPressed(Ref* sender)
{

    auto gameLayer = dynamic_cast<GameLayer*>(
        this->getParent()->getChildByName("GameLayer")
        );

    if (gameLayer)
    {
        gameLayer->setupStage();
    }

}