#include "RuleScene.h"
USING_NS_CC;

Scene* ruleLayer::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	auto winSize = Director::getInstance()->getWinSize();
    
    // 'layer' is an autorelease object
    ruleLayer *layer = ruleLayer::create();
	auto ruleBgSprite = Sprite::create("ruleBgSprite.png");
	float width = ruleBgSprite->getContentSize().width;
	float height = ruleBgSprite->getContentSize().height;
	float scaleRateW = winSize.width / width;
	float scaleRateH = winSize.height / height;
	ruleBgSprite->setAnchorPoint(ccp(0.5,0.5));
	ruleBgSprite->setScale(scaleRateW,scaleRateH);
	ruleBgSprite->setPosition(winSize.width/2, winSize.height/2);
	// add layer as a child to scene

	scene->addChild(ruleBgSprite);
	scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ruleLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto backItem = MenuItemImage::create(
                                        "Buttons/ruleBackBtn.png",
                                        "Buttons/ruleBackBtn.png",
										CC_CALLBACK_1(ruleLayer::_backToMain,this));
    
	backItem->setAnchorPoint(ccp(1,1));
	backItem->setPosition(visibleSize.width-20, visibleSize.height-20);

    // create menu, it's an autorelease object
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Point::ZERO);
    
	this->addChild(menu, 1);
    
    return true;
}

void ruleLayer::_backToMain(Ref* pSender)
{
	Director::getInstance()->popScene();
}