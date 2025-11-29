#include "TitleScene.h"
#include "StageSelectScene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    return TitleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    CCLOG("Error while loading: %s!!!!!!!!!!!!!!!!!!!!!!!!!!\n", filename);
}


bool TitleScene::init()
{
    //親クラスの初期化が失敗したら、自分の初期化も中止
    if (!Scene::init())
    {
        return false;
    }

    //画面サイズ取得
    //visibleSizeは見えている領域の幅と高さ(cocos2d::Size型←ポインタじゃない！)
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //originは見えている画面領域の左下座標(cocos2d::Vec2型←ポインタじゃない！)
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //スタートボタン
    auto startItem = MenuItemLabel::create(
        Label::createWithTTF("START", "fonts/RiiPopkkR.otf", 50),
        CC_CALLBACK_1(TitleScene::onStartButtonPressed, this));


    if (startItem == nullptr) {
        problemLoading("'fonts/RiiPopkkR.otf'");
    }
    else {
        startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, //setposition(Vec2(x,y))
            origin.y + visibleSize.height * 0.4f));
    }

    auto menu = Menu::create(startItem, nullptr); //引数が可変長のため、終端マーカーとしてnullptrを書く
    menu->setPosition(Vec2::ZERO); //Vec2::ZEROはVec2(0,0)のこと
    this->addChild(menu, 1);
    //ここでのthisはTitleScene* のことだが、多態性によってScene*としても扱える


    // ラベル表示
    auto label = Label::createWithTTF("Line Shooter", "fonts/RiiPopkkR.otf", 24);
    if (label == nullptr) {
        //読み込み失敗時のエラー処理
        problemLoading("'fonts/RiiPopkkR.otf'");
    }
    else {
        // 配置
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    return true;
}

void TitleScene::onStartButtonPressed(Ref* sender)
{

    //遷移
    auto scene = StageSelectScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));

}
