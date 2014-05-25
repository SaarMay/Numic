#include "EndingScene.h"
USING_NS_CC;
using namespace CocosDenshion;


bool endLayer::init()
{
	return true;
}

Scene* endLayer::scene()
{
	Scene* scene = Scene::create();
	auto bgSprite = Sprite::create("rankBgSprite.png");

	auto winSize = Director::getInstance()->getWinSize();
	auto spriteSize = bgSprite->getContentSize();

	bgSprite->setAnchorPoint(ccp(0.5,0.5));
	bgSprite->setPosition(winSize.width/2, winSize.height/2);
	bgSprite->setScale(winSize.width/spriteSize.width, winSize.height / spriteSize.height);

	scene->addChild(bgSprite);

	return scene;
}

void endLayer::backToMain(cocos2d::Ref* pSender)
{
	//Director::getInstance()->replaceScene(
		//TransitionCrossFade::create(1.0f, startScene::start()));	
}

void endLayer::getRank()
{
	//auto rb = RankBo
}

void endLayer::newgame()
{

}