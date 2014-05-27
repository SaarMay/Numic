#include "EndingScene.h"
#include <algorithm>
#include <sstream>

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

bool rankSprite::init()
{
	if(!Sprite::init())
		return false;

	this->setAnchorPoint(ccp(0,0));
	this->setContentSize(Size(280,35));
	auto winSize = Director::getInstance()->getWinSize();
	auto spriteSize = this->getContentSize();

	this->setContentSize(Size(winSize.height*0.5,40.0f));
	this->setAnchorPoint(ccp(0,0));
	this->setPosition(10,10);

	this->rankNumLabel = LabelTTF::create("","AdobeArabic Bold",30);
	this->rankNumLabel->setAnchorPoint(ccp(0,0.5));
	this->rankNumLabel->setPosition(20, spriteSize.height/2);

	this->scoreLabel = LabelTTF::create("","AdobeArabic Bold",30);
	this->scoreLabel->setAnchorPoint(ccp(1,0.5));
	this->scoreLabel->setPosition(spriteSize.width - 20, spriteSize.height/2);

	this->nameLabel = LabelTTF::create("","AdobeArabic Bold",30);
	this->nameLabel->setAnchorPoint(ccp(0.5,0.5));
	this->nameLabel->setPosition(spriteSize.width/2, spriteSize.height/2);


	this->addChild(rankNumLabel);
	this->addChild(nameLabel);
	this->addChild(scoreLabel);

	return true;
}

void rankSprite::createSprite(int r, string n, int s, bool ifCur)
{

	if(r == 0 || s == 0)
	{
		this->rankNumLabel->setString("");
		this->scoreLabel->setString("");
	}

	else
	{
		char tstr[5];
		itoa(r,tstr,10);

		this->rankNumLabel->setString(tstr);
		this->nameLabel->setString(n);
		this->name = n;


		itoa(s,tstr,10);
		this->scoreLabel->setString(tstr);
	}

	if(ifCur)
	{
		auto Bgcolor = Color3B(255,155,155);
		this->setColor(Bgcolor);
	}

	this->setAnchorPoint(ccp(0,0));
	
}

vector<userInfo> RankingBoard::getRankInfo()
{
	vector<userInfo> uInfo;
	ifstream rankin("Ranking.txt");
	string userName;
	int userScore;
	int cur = 0;
	while (rankin >> userName)
	{
		rankin >> userScore;
		uInfo.push_back(userInfo(userName,userScore,0));
		cur++;
	}

	uInfo[--cur].ifCur = 1;
	this->curScore = uInfo[cur].score;

	sort(uInfo.begin(),uInfo.end());

	return uInfo;
}

bool RankingBoard::init()
{
	if(!Sprite::init())
		return false;

	auto winSize = Director::getInstance()->getWinSize();

	vector<userInfo> v = this->getRankInfo();
	for(int i = 1; i < 6 ; i++)
	{
		auto r = rankSprite::create();
		int l = v.size()-i;
		
		if(l >= 0)
			r->createSprite(i,v[l].name,v[l].score,v[l].ifCur);
		else
			r->createSprite();

		r->setPosition(10, 45*(5-i)+5);
	
		this->addChild(r);
	}
	
	this->setContentSize(Size(300,225));
	this->setAnchorPoint(ccp(0,0));
	this->setPosition(80,100);
	
	return true;
}

bool endLayer::init()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto backMain = MenuItemImage::create("Buttons/mainBtn.png","Buttons/mainBtn.png",
									CC_CALLBACK_1(endLayer::backToMain, this));
	auto resumeGame = MenuItemImage::create("Buttons/replayBtn.png","Buttons/replayBtn.png",
									CC_CALLBACK_1(endLayer::newgame,this));

	resumeGame->setAnchorPoint(ccp(0.5,0.5));
	resumeGame->setPosition(winSize.width*0.75, winSize.height*2/5);

	backMain->setAnchorPoint(ccp(0,1));
	backMain->setPosition(50,winSize.height-50);

	auto menu = Menu::create(backMain,resumeGame,NULL);
	menu->setPosition(Point::ZERO);

	rankBoard = RankingBoard::create();

	this->addChild(menu);
	this->addChild(rankBoard);
	this->getScore();

	return true;
}

Scene* endLayer::scene()
{
	Scene* scene = Scene::create();
	auto bgSprite = Sprite::create("endBgSprite.png");
	auto contentSprite = endLayer::create();

	auto winSize = Director::getInstance()->getWinSize();
	auto spriteSize = bgSprite->getContentSize();

	bgSprite->setAnchorPoint(ccp(0.5,0.5));
	bgSprite->setPosition(winSize.width/2, winSize.height/2);
	bgSprite->setScale(winSize.width/spriteSize.width, winSize.height / spriteSize.height);

	scene->addChild(bgSprite);
	scene->addChild(contentSprite);

	return scene;
}

void endLayer::backToMain(Ref* pSender)
{
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, StartScene::start("Mr. Ya")));	
}


void endLayer::newgame(Ref* pSender)
{
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, gameLayer::createScene()));
}

void endLayer::getScore()
{
	auto winSize = Director::getInstance()->getWinSize();
	this->curScore = this->rankBoard->getCurScore();
	auto scoreBox = LabelTTF::create("","AdobeArabic Bold",30);
	scoreBox->setAnchorPoint(ccp(1,1));
	scoreBox->setPosition(winSize.width - 125, winSize.height -190);

	char tstr[5];
	itoa(curScore,tstr,10);
	scoreBox->setString(tstr);
	
	this->addChild(scoreBox);
}