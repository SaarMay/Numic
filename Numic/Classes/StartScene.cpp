#include "StartScene.h"
using namespace cocos2d;
using namespace CocosDenshion;

bool startBgLayer::init()
{
	if(!Layer::init())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	auto bgSprite = Sprite::create("startBgSprite.png");
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

bool startBtnLayer::init()
{
	if ( !Layer::init() )
        return false;

	Size winSize = Director::getInstance()->getWinSize();

	auto startBtnItem = MenuItemImage::create("Buttons/startBtn.png","Buttons/startBtn.png",this,menu_selector(startBtnLayer::gameStarting));
	auto startBtn = Menu::create(startBtnItem,NULL);

	float x = winSize.width;
	float y = winSize.height;
	startBtn->setAnchorPoint(ccp(1,0.5));
	// startBtn 位置设定， 最右中心点为锚点
	startBtn->setPosition(ccp((winSize.width - 250), (winSize.height/2-10)));

	this->addChild(startBtn);
}

bool startMenuLayer::init()
{
	if ( !Layer::init() )
        return false;

	Size winSize = Director::getInstance()->getWinSize();

	// 关于菜单
	auto aboutUS = MenuItemImage::create("Buttons/aboutBtn.png","Buttons/aboutBtn.png",this,menu_selector(startMenuLayer::aboutUs));
	// 音效控制
	auto musicSwitchImg = MenuItemImage::create("Buttons/musicBtn.png","Buttons/musicBtn.png",this,menu_selector(startMenuLayer::musicSwitching));
	auto musicSwitch = MenuItemToggle::create(musicSwitchImg);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(			// 默认音乐播放
	//	"bg_music.mp3",true);
	
	// 排名
	auto rankCallBtn = MenuItemImage::create("Buttons/rankBtn.png","Buttons/rankBtn.png",this,menu_selector(startMenuLayer::rankingCall));
	// 规则
	auto ruleBtn = MenuItemImage::create("Buttons/ruleBtn.png","Buttons/ruleBtn.png",this,menu_selector(startMenuLayer::ruleCall));
	
	auto startMenu = Menu::create(ruleBtn,musicSwitch,rankCallBtn,aboutUS,NULL);
	startMenu->alignItemsHorizontally();
	// 指定间隔
	startMenu->alignItemsHorizontallyWithPadding(20);

	// 位置设置， 屏幕左下角高10位置
	startMenu->setAnchorPoint(ccp(0,0));
	startMenu->setPosition(ccp(winSize.width - 300, 100));

	this->addChild(startMenu);
}

bool StartScene::init()
{
	if(!Scene::init())
		return false;

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("StartBgMusic.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("StartBgMusic.mp3",true);

	startBgLayer* pLayer_bg = startBgLayer::create();
	startMenuLayer* pLayer_menu = startMenuLayer::create();
	startBtnLayer* pLater_btn = startBtnLayer::create();

	this->addChild( pLayer_bg , 0 );
	this->addChild( pLayer_menu, 1);
	this->addChild( pLater_btn, 2);

	return true;
}

Scene* StartScene::start(string user)
{
	StartScene* scene = new StartScene();
	scene->init();
	scene->setUsername(user);

	return scene;
}

void StartScene::setUsername(string usr)
{
	this->username = usr;
	ofstream rankout("Ranking.txt",std::ofstream::app);
	
	rankout << this->username << "\t";
}

void startMenuLayer::ruleCall(cocos2d::Ref* pSender)
{
	//Director::sharedDirector()->replaceScene(
	//	TransitionCrossFade::create(1.0f, RuleScene::scene())
}

void startMenuLayer::aboutUs(cocos2d::Ref* pSender)
{
	//Director::sharedDirector()->replaceScene(
	//	TransitionCrossFade::create(1.0f, AboutScene::scene()));
}

void startMenuLayer::rankingCall(cocos2d::Ref* pSender)
{
	//Director::sharedDirector()->replaceScene(
	//	TransitionCrossFade::create(1.0f, RankingScene::scene()));
}

void startBtnLayer::gameStarting(cocos2d::Ref* pSender)
{
	Director::sharedDirector()->replaceScene(
		TransitionCrossFade::create(1.0f, gameLayer::createScene()));
}

void startMenuLayer::musicSwitching(cocos2d::Ref* pSender)
{
	this->musicOn = !(this->musicOn);			// 音乐开关状态反转
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"bg_music.mp3",this->musicOn);
}