#include "RankingScene.h"
using namespace cocos2d;


Scene* rankLayer::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    rankLayer *layer = rankLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool rankLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto bgSprite = Sprite::create("rankBgSprite.png");
	bgSprite->setAnchorPoint(ccp(0.5,0.5));
	bgSprite->setPosition(visibleSize.width/2, visibleSize.height/2);
	float width = bgSprite->getContentSize().width;
	float height = bgSprite->getContentSize().height;
	float scaleRateW = visibleSize.width / width;
	float scaleRateH = visibleSize.height / height;
	bgSprite->setScale(scaleRateW,scaleRateH);

	auto backBtn = MenuItemImage::create("Buttons/backBtn.png","Buttons/backBtn.png",
								  CC_CALLBACK_1(rankLayer::backTostart,this));
	
	backBtn->setAnchorPoint(ccp(1,1));
	backBtn->setPosition(visibleSize.width-50, visibleSize.height-50);
	auto menu = Menu::create(backBtn,NULL);
	menu->setPosition(Point::ZERO);

	auto rankBoard = RankingBoard::create();
	rankBoard->setAnchorPoint(ccp(0.5,0.5));
	rankBoard->setPosition(visibleSize.width/2, visibleSize.height/2);

    // add the sprite as a child to this layer
	this->addChild(bgSprite);
	this->addChild(rankBoard);
	this->addChild(menu);
    
    return true;
}

void rankLayer::backTostart(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
