#include "HelloScene.h"
using namespace cocos2d;
using namespace CocosDenshion;

bool bgLayer::init()
{
	if ( !Layer::init() )
        return false;
	
	auto winSize = Director::getInstance()->getWinSize();

	auto bgSprite = Sprite::create("helloBgSprite.png");
	float width = bgSprite->getContentSize().width;
	float height = bgSprite->getContentSize().height;
	float scaleRateW = winSize.width / width;
	float scaleRateH = winSize.height / height;
	bgSprite->setScale(scaleRateW,scaleRateH);
	//bgSprite->setContentSize(winSize);
	bgSprite->setPosition(Point(winSize/2));
	
	this->addChild(bgSprite);

	return true;
}

bool logoLayer::init()
{
	if ( !Layer::init() )

        return false;

	Size winSize = Director::getInstance()->getWinSize();

	auto logoSprite = Sprite::create("");

	float scalerate = winSize.height / ( 4*(logoSprite->getContentSize().height));

	logoSprite->setScale(scalerate,scalerate);
	logoSprite->setAnchorPoint(ccp(0.5,0.5));
	logoSprite->setPosition(Point(winSize)/2);

	this->addChild(logoSprite);

	return true;
}

bool HelloScene::init()
{
	if ( !Scene::init() )
        return false;

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("SoundEffect/GameBgMusic.mp3");

	//winSize = Director::getInstance()->getWinSize();

	bgLayer* pLayer_bg = bgLayer::create();
	//logoLayer* pLayer_logo = logoLayer::create();

	this->addChild( pLayer_bg, 0 );
	//this->addChild( pLayer_logo, 1 );
	
	this->scheduleOnce(schedule_selector(HelloScene::enterGame),2.0f);
	//Director::sharedDirector()->replaceScene(
	//	TransitionCrossFade::create(3.0f, StartScene::start()));

	return true;
}

void HelloScene::enterGame(float dt)
{
	Director::sharedDirector()->replaceScene(
		TransitionCrossFade::create(0.5f, StartScene::start()));
}

Scene* HelloScene::Hello()
{
	HelloScene* scene = new HelloScene();
	scene->init();

	return scene;
}

//Scene* startScene::scene()
//{
//	auto scene = Scene::create();
//
//	startScene *bgLayer = startScene::create();
//	startScene *logoLayer = startScene::create();
//
//	scene->addChild(bgLayer);
//	scene->addChild(logoLayer);
//
//	return scene;
//}
//
//bool startScene::init()
//{
//	if( !Layer::init() )
//	{
//		return false;
//	}
//
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	auto origin = Director::getInstance()->getVisibleOrigin();
//
//	auto bgSprite = Sprite::create("bg.png");
//	bgSprite->setPosition(Point(visibleSize / 2) + origin);
//
//	auto logoSprite = Sprite::create("0.png");
//	logoSprite->setPosition(Point(visibleSize / 2) + origin);
//
//}