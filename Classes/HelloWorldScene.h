/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


//同じヘッダが2回以上読み込まれるのを防ぐ仕組み
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h" //#include"xxx.h" と書いたときに、コンパイラが「xxx.h」を探しに行く場所のリスト(インクルードパス)が設定されているため、このように書ける


//cocos2d名前空間にあるSceneクラスを継承
class HelloWorld : public cocos2d::Scene
{
public: //クラス内のメソッドはcppファイルで定義されている

    //シーンを生成して返す「工場メソッド」
    //インスタンス化前に呼ばれるためstatic
    static cocos2d::Scene* createScene();

    //シーンやノードの初期化処理を行うメソッド
    //Cocos2d-x が autorelease などの独自メモリ管理をしているため、コンストラクタではなく init() にまとめる
    virtual bool init();
    
    //メニューやボタンを押したときに呼ばれる(コールバック)関数
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    //create()を自動で作っており、これによりcreateScene()が定義されている
    //これによってHelloWorld::create()と書ける
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
