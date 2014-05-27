#include "EndingScene.h"
#include <algorithm>
#include <sstream>
USING_NS_CC;
using namespace std;

bool rankSprite::init()
{
	if(!Sprite::init())
		return false;
	
	auto winSize = Director::getInstance()->getWinSize();
	this->setContentSize(Size(winSize.height*0.5,40.0f));
	this->setAnchorPoint(ccp(0,0));
	this->setPosition(10,10);

	this->rankNumLabel = LabelTTF::create("","AdobeArabic Bold",30);
	this->scoreLabel = LabelTTF::create("","AdobeArabic Bold",30);
	this->nameLabel = LabelTTF::create("","AdobeArabic Bold",30);

	this->addChild(rankNumLabel);
	this->addChild(nameLabel);
	this->addChild(scoreLabel);

	return true;
}

rankSprite* rankSprite::createSprite(int r, string n, int s, bool ifCur)
{
	auto rs = rankSprite::create();

	if(r == 0 || s == 0)
	{
		rs->rankNumLabel->setString("");
		rs->scoreLabel->setString("");
	}

	else
	{
		stringstream ss;
		string tstr;
		ss << r;
		ss >> tstr;

		rs->rankNumLabel->setString(tstr);
		rs->nameLabel->setString(n);

		ss << s;
		ss >> tstr;
		rs->scoreLabel->setString(tstr);
	}

	if(ifCur)
	{
		auto Bgcolor = Color3B(255,155,155);
		rs->setColor(Bgcolor);
	}

	rs->setAnchorPoint(ccp(0,0));

	return rs;
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

	uInfo[cur].ifCur = 1;
	this->curScore = uInfo[cur].score;

	sort(uInfo.begin(),uInfo.end());

	return uInfo;
}

bool RankingBoard::init()
{
	if(!Sprite::init())
		return false;

	vector<userInfo> v = this->getRankInfo();
	int l = v.size();

	for(int i = 0; i < 5; i++)
	{
		rankSprite* r;
		if(i < v.size())
			r->createSprite(l-i,v[i].name,v[i].score,v[i].ifCur);
		else
			r->createSprite();

		r->setPosition(10, 45*i-40);

		this->addChild(r);
	}

	return true;
}