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

	auto backBtn = MenuItemImage::create("Buttons/backBtn.png","Buttons/backBtn.png",this->getParent(),menu_selector(rankLayer::backTostart));
	backBtn->setAnchorPoint(ccp(1,1));
	backBtn->setPosition(visibleSize.width-50, visibleSize.height-50);
	auto menu = Menu::create(backBtn,NULL);

    // add the sprite as a child to this layer
    this->addChild(bgSprite);
	this->addChild(menu);
    
    return true;
}

void rankLayer::backTostart(cocos2d::Ref* pSender)
{
	Director::sharedDirector()->replaceScene(
		TransitionCrossFade::create(1.0f, StartScene::start()));
}
