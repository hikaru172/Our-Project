#include "StageSelectScene.h"
//#include "GameScene.h"

USING_NS_CC;

Scene* StageSelectScene::createScene()
{
    return StageSelectScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    CCLOG("Error while loading: %s!!!!!!!!!!!!!!!!!!!!!!!!!!\n", filename);
}


bool StageSelectScene::init()
{
    //親クラスの初期化が失敗したら、自分の初期化も中止
    if (!Scene::init()) {
        return false;
    }

    //画面サイズ取得
    //visibleSizeは見えている領域の幅と高さ(cocos2d::Size型←ポインタじゃない！)
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //originは見えている画面領域の左下座標(cocos2d::Vec2型←ポインタじゃない！)
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //VectorはCocos2d-x 独自のコンテナクラスで、型がMenuItem*なので、メニュー項目（ボタンなど）のポインタをまとめて管理する入れ物buttonsを定義している
    Vector<MenuItem*> buttons;

    //buttonWidthを取得するための仮のSprite
    auto tempSprite = Sprite::create("stageselect.png");
    float buttonWidth = tempSprite->getContentSize().width;
    float buttonHeight = tempSprite->getContentSize().width;
    float spaceX = (visibleSize.width - 6 * buttonWidth) / 7;
    float spaceY = 0.0; //labelのheightによって値を決めるため下で代入


    // ラベル表示
    auto label = Label::createWithTTF(u8"ステージ選択", "fonts/RiiPopkkR.otf", 50);
    if (label == nullptr) {
        //読み込み失敗時のエラー処理
        problemLoading("'fonts/RiiPopkkR.otf'");
    }
    else {
        // 配置
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        spaceY = (visibleSize.height - label->getContentSize().height - 3 * buttonHeight) / 3.5;

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 6; j++) {
            //ステージごとのボタン
            //Cocos2d-x では 同じSpriteインスタンスを複数のノードに addChild することはできない
            auto stage_normal_Sprite = Sprite::create("stageselect.png");
            auto stage_selected_Sprite = Sprite::create("stageselect2.png");

            //この内部ではSpriteをMenuItemSpriteの子ノードとして追加している
            auto stage_select_Item = MenuItemSprite::create(
                stage_normal_Sprite,
                stage_selected_Sprite,
                CC_CALLBACK_1(StageSelectScene::onButtonPressed, this)
            );

            if (stage_select_Item == nullptr) {
                problemLoading("'stageselect.png' and 'stageselect2.png'");
            }
            else
            {
                stage_select_Item->setPosition(Vec2(origin.x + spaceX * j + buttonWidth * (j - 0.5f),
                    origin.y + spaceY * (4 - i) + buttonHeight * (4 - i - 0.5f)));
            }

            //どのボタンが押されたかの判別用にタグ付け
            stage_select_Item->setTag((i - 1) * 6 + j);

            // ボタンのラベルを作成
            auto button_label = Label::createWithTTF(std::to_string((i - 1) * 6 + j), "fonts/RiiPopkkR.otf", 50); //std::string(i) … C++標準ライブラリの関数で、数値(i)を文字列に変換
            button_label->setPosition(stage_normal_Sprite->getContentSize() / 2); // ボタン中央に配置
            stage_select_Item->addChild(button_label);

            //Menu にまとめて追加するためにベクターに入れる
            //pushBack() は buttons に要素を追加する関数
            buttons.pushBack(stage_select_Item);
        }
    }

    //auto menu = Menu::create(stage_select_Item,nullptr);
    auto menu = Menu::createWithArray(buttons);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}


//Ref*はcocos2d-xの基底クラス、senderはイベントを発生させたオブジェクト
void StageSelectScene::onButtonPressed(Ref* sender)
{
    ////dynamic_castを使ってRef* をMenuItem*にキャストしている
    //auto item = dynamic_cast<MenuItem*>(sender);
    ////タグを取得
    //int stageNumber = item->getTag();

    //auto scene = GameScene::createScene(stageNumber);
    //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));

    Director::getInstance()->end();
}
