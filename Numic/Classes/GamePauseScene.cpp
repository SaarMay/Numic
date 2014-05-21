#include "GamePauseScene.h"

using namespace  cocos2d;
using namespace CocosDension;

#ifndef _GAME_PAUSE_SCENE_H_
#define _GAME_PAUSE_SCENE_H_

bool pauseLayer::init()
{
	if ( !Layer::init() )
        return false;

	auto restartBtn = MenuItemImage::create("Buttons/restartBtn.png","Buttons/restartBtn.png",
											CC_CALLBACK_1(pauseLayer::_restartGame, this));
	auto resumeBtn = MenuItemImage::create("Buttons/resumeBtn.png","Buttons/resumeBtn.png",
											CC_CALLBACK_1(pauseLayer::_resumeGame,this));
	auto mainbackBtn = MenuItemImage::create("Buttons/mainbackBtn.png","Buttons/mainbackBtn.png",
											CC_CALLBACK_1(pauseLayer::_backToMain,this)); 

    auto s = Director::getInstance()->getWinSize();
    auto ss = restartBtn->getContentSize();


    restartBtn->setAnchorPoint(ccp(0.5,0.5));
    restartBtn->setPosition(s.width, s.height);

    resumeBtn->setAnchorPoint(ccp(0.5,0.5));
    resumeBtn->setPosition(s.width, s.height + 1.2*ss.height);

    mainbackBtn->setAnchorPoint(ccp(0.5,0.5));
    mainbackBtn->setPosition(s.width, s.height - 1.2*ss.height);


	auto pauseMenu = Menu::create(restartBtn,resumeBtn,mainbackBtn,NULL);
    pauseMenu->alignItemsVertically();

    this->addChild(pauseMenu);

    return true;
}

void pauseLayer::_restartGame(cocos2d::Ref* pSender)
{
	Director::getInstance()->poptoRootScene();
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, gameLayer::createScene()));
}

void pauseLayer::_resumeGame(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void pauseLayer::_backToMain(cocos2d::Ref* pSender)
{
	Director::getInstance()->poptoRootScene();	
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, StartScene::start()));
}

bool pauseBgLayer::init()
{
	if ( !Layer::init() )
        return false;

	Size winSize = Director::getInstance()->getWinSize();

	auto bgSprite = Sprite::create("pauseBgSprite.png");
	float width = bgSprite->getContentSize().width;
	float height = bgSprite->getContentSize().height;
	float scaleRateW = winSize.width / width;
	float scaleRateH = winSize.height / height;
	bgSprite->setScale(scaleRateW,scaleRateH);
	bgSprite->setPosition(Point(winSize/2));
	
	this->addChild(bgSprite);
}

bool pauseScene::init()
{
	if(!Scene::init())
		return false;

	auto pLayer_pause = pauseLayer::create();
	auto pLayer_bg = pauseBgLayer::create();

	this->addChild(pLayer_bg);
	this->addChild(pLayer_pause);

	return true;
}

Scene* pauseScene::scene()
{
	pauseScene* scene = new pauseScene();
	scene->init();

	return true;
}