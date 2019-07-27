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

#include "HelloWorldScene.h"
#include "AudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	//printf("Error while loading: %s\n", filename);
	//printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	/*auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
*/
	
	//背景
	Sprite* haikei = Sprite::create("haikei2.png");//宇宙
	this->addChild(haikei);
	haikei->setScale(2.5f);
	haikei->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// Spriteの生成
	Sprite* spr1 = Sprite::create("Kirby.png");//カービィ
	this->addChild(spr1);
	spr1->setScale(0.5f);
	spr1->setPosition(Vec2(1200.0f, visibleSize.height / 1.5));

	Sprite* spr2 = Sprite::create("muteki.png");//キャンディ
	this->addChild(spr2);
	spr2->setScale(0.25);
	spr2->setPosition(Vec2(980.0f, visibleSize.height / 1.5));

	Sprite* spr = Sprite::create("soul.png");//マルクソウル
	this->addChild(spr);
	spr->setScale(2.0f);
	spr->setPosition(Vec2(100.0f, visibleSize.height / 1.5));

	Sprite* spr3 = Sprite::create("nova.png");//ギャラクティック・ノヴァ
	this->addChild(spr3);
	spr3->setScale(3.0f);
	spr3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2-100));

	Sprite* spr4 = Sprite::create("tobe.png");//ToBeContinued...
	this->addChild(spr4);
	spr4->setScale(0.7f);
	spr4->setPosition(Vec2(visibleSize.width+320.0f, 100.0f));//280 100

	//Spawn 同時アクション
	//Sequence 順番アクション
	spr3->setVisible(0);

	//ノヴァアクション
	DelayTime* novataiki = DelayTime::create(10.0f);
	Show* novashow = Show::create();
	Sequence* novalast = Sequence::create(novataiki, novashow, nullptr);
	//ノヴァ終わり

	//カービィアクション
	MoveTo* action1 = MoveTo::create(5.0f,Vec2(visibleSize.width/2+50,visibleSize.height/1.5));
	EaseIn* action4 = EaseIn::create(action1, 2.0f);
    Hide*hideK = Hide::create();
	DelayTime*Kdel = DelayTime::create(5.0f);
	Sequence* Ksp = Sequence::create(Kdel, hideK, nullptr);
	Sequence*Kact = Sequence::create(action4, Ksp, nullptr);

	DelayTime*dk = DelayTime::create(3.0f);
	Blink* bk = Blink::create(6.5f, 20);
	Sequence* kact1 = Sequence::create(dk, bk, nullptr);
	
	//マルクアクション
	MoveTo* Mstart = MoveTo::create(5.0f, Vec2(visibleSize.width / 2-50, visibleSize.height / 1.5));
	RotateTo* action6 = RotateTo::create(1.0f, -150.0f);
	MoveTo* Mdown = MoveTo::create(5.0f, Vec2(visibleSize.width / 2 - 50, -100.0f));
	Spawn* Mds = Spawn::create(action6, Mdown, nullptr);
	Sequence* Mac1 = Sequence::create(Mstart, Mds, nullptr);
	Place*Mp = Place::create(Vec2(visibleSize.width / 2, visibleSize.height + 86));
	Sequence* Mac2 = Sequence::create(Mac1, Mp, nullptr);
	DelayTime*Md = DelayTime::create(1.0f);
	MoveTo*Ml = MoveTo::create(1.0f,Vec2(visibleSize.width / 2, visibleSize.height - 50));
	Sequence* Mac3 = Sequence::create(Mac2, Md, nullptr);
	Sequence* Mac4 = Sequence::create(Mac3, Ml, nullptr);

	DelayTime*hai = DelayTime::create(12.1f);
	TintTo*htin = TintTo::create(0.1, 153, 153, 102);
	Sequence*hact1 = Sequence::create(hai, htin, nullptr);
	

	//キャンディアクション
	DelayTime* mutekitaiki = DelayTime::create(3.0f);
	RemoveSelf* mutekikesi = RemoveSelf::create();
	Sequence*muteki = Sequence::create(mutekitaiki, mutekikesi, nullptr);
	//キャンディ終わり

	//Tobeアクション
	DelayTime* td = DelayTime::create(12.0f);
	MoveTo* tm = MoveTo::create(0.1f, Vec2(280.0f, 100.0f));
	Sequence* tact1 = Sequence::create(td, tm, nullptr);
	
	DelayTime*nai = DelayTime::create(12.1f);
	TintTo*ntin = TintTo::create(0.1, 153, 153, 102);
	Sequence*nact1 = Sequence::create(nai, ntin, nullptr);
	
	DelayTime*mai = DelayTime::create(12.1f);
	TintTo*mtin = TintTo::create(0.1, 153, 153, 102);
	Sequence*mact1 = Sequence::create(mai, mtin, nullptr);

	
	
	experimental::AudioEngine::play2d("To.mp3");
	
	
	// アクションの実行
	//カービィ 
	spr1->runAction(Kact);
	spr1->runAction(kact1);
	//マルク
	spr->runAction(Mac4);
	spr->runAction(mact1);
	//キャンディ　
	spr2->runAction(muteki);
	//ノヴァ　
	spr3->runAction(novalast);
	spr3->runAction(nact1);
	//
	spr4->runAction(tact1);

	haikei->runAction(hact1);
	


	// update関数を有効にする
	this->scheduleUpdate();

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::update(float delta)
{

}