#include "RankingBoard.h"
#include <algorithm>
#include <sstream>
USING_NS_CC;

bool rankSprite::init()
{
	if(!Sprite::init())
		return false;
	
	auto winSize = Director::getInstance()->getWinSize();
	this->setContentSize(Size(winSize.height*0.6,30.0f));
	this->setAnchorPoint(ccp(0,0));
	this->setPosition(10,10);

	this->rankNum = LabelTTF::create("","AdobeArabic Bold",30);
	this->score = LabelTTF::create("","AdobeArabic Bold",30);
	this->name = LabelTTF::create("","AdobeArabic Bold",30);

	this->addChild(rankNum);
	this->addChild(name);
	this->addChild(score);

	return true;
}

rankSprite* rankSprite::createSprite(int r, string n, int s, bool ifCur)
{
	rankSprite* rs = rankSprite::create();

	stringstream ss;
	string tstr;
	ss << r;
	ss >> tstr;

	rs->rankNum->setString(tstr);
	
	stringstream ss;
	string tstr;
	ss << r;
	ss >> tstr;	
	
	rs->name->setString(n);
	rs->score->setString(tstr);
	rs->setPositionY(40*(r-1)+10);

	if(ifCur)
	{
		auto Bgcolor = Color3B(255,155,155);
		rs->setColor(Bgcolor);
	}

	return rs;
}

vector<userInfo> RankingBoard::getRankInfo()
{
	vector<userInfo> uInfo;
	ifstream rankin("Ranking.txt");
	string name;
	int score;
	int cur = 0;
	while (rankin >> name)
	{
		rankin >> score;
		uInfo.push_back(userInfo(name,score,0));
		cur++;
	}
	uInfo[cur].ifCur = 1;

	sort(uInfo.begin(),uInfo.end());

	return uInfo;
}

bool RankingBoard::init()
{
	if(!Layer::init())
		return false;

	vector<userInfo> v = this->getRankInfo();
	int l = v.size();

	for(int i = 0; i < v.size() && i < 5; i++)
	{
		rankSprite* r;
		r->createSprite(l-i,v[i].name,v[i].score,v[i].ifCur);

		this->addChild(r);
	}

	return true;
}