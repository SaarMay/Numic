#include "GamePauseScene.h"
USING_NS_CC;
using namespace CocosDenshion;

bool pauseLayer::init()
{
	if ( ! Layer::init() )
        return false;

	auto restartBtn = MenuItemImage::create("Buttons/pauseNewBtn.png","Buttons/pauseNewBtn.png",
											CC_CALLBACK_1(pauseLayer::_restartGame, this));
	auto resumeBtn = MenuItemImage::create("Buttons/pauseResumeBtn.png","Buttons/pauseResumeBtn.png",
											CC_CALLBACK_1(pauseLayer::_resumeGame,this));
	auto mainbackBtn = MenuItemImage::create("Buttons/pauseMainBtn.png","Buttons/pauseMainBtn.png",
											CC_CALLBACK_1(pauseLayer::_backToMain,this));
	auto musicSwitchBtn = MenuItemImage::create("Buttons/pauseMusicBtn.png","Buttons/pauseMusicBtn.png.png",
											CC_CALLBACK_1(pauseLayer::_musicSwitch,this));

    auto s = Director::getInstance()->getVisibleSize();
    auto ss = restartBtn->getContentSize();
	float hminu = restartBtn->getContentSize().height + 20;


    restartBtn->setAnchorPoint(ccp(0.5,0.5));
	restartBtn->setPosition(s.width/2, s.height/2 - hminu);

    resumeBtn->setAnchorPoint(ccp(0.5,0.5));
	resumeBtn->setPosition(s.width/2, s.height/2 + hminu);

    mainbackBtn->setAnchorPoint(ccp(0,1));
	mainbackBtn->setPosition(40, s.height-40);

	musicSwitchBtn->setAnchorPoint(ccp(1,1));
	musicSwitchBtn->setPosition(s.width-40, s.height-40);

	auto pauseMenu = Menu::create(restartBtn,resumeBtn,mainbackBtn,musicSwitchBtn,NULL);
    //pauseMenu->alignItemsVertically();
	pauseMenu->setPosition(0,0);

    this->addChild(pauseMenu);

    return true;
}

void pauseLayer::_restartGame(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, gameLayer::createScene()));
}

void pauseLayer::_resumeGame(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void pauseLayer::_backToMain(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();	
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, StartScene::start("Mr. Ya")));
}

void pauseLayer::_musicSwitch(cocos2d::Ref* pSender)
{
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("GameBgMusic.mp3");
	}
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

	this->addChild(pLayer_bg,0);
	this->addChild(pLayer_pause,1);

	return true;
}

Scene* pauseScene::scene()
{
	pauseScene* scene = new pauseScene;
	scene->init();

	return scene;
}