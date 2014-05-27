#include "AboutScene.h"

USING_NS_CC;

Scene* aboutLayer::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    aboutLayer *layer = aboutLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool aboutLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto bgSprite = Sprite::create("aboutBgSprite.png");
	bgSprite->setAnchorPoint(ccp(0.5,0.5));
	bgSprite->setPosition(visibleSize.width/2, visibleSize.height/2);
	float width = bgSprite->getContentSize().width;
	float height = bgSprite->getContentSize().height;
	float scaleRateW = visibleSize.width / width;
	float scaleRateH = visibleSize.height / height;
	bgSprite->setScale(scaleRateW,scaleRateH);

	auto backBtn = MenuItemImage::create("Buttons/aboutBackBtn.png","Buttons/aboutBackBtn.png",this->getParent(),menu_selector(aboutLayer::backTostart));
	backBtn->setAnchorPoint(ccp(1,1));
	backBtn->setPosition(visibleSize.width-50, visibleSize.height-50);
    auto menu = Menu::create(backBtn,NULL);
	menu->setPosition(Point::ZERO);
	
	this->addChild(bgSprite);
	this->addChild(menu);
    return true;
}

void aboutLayer::backTostart(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
