#ifndef _ENDING_SCENE_H_
#define _ENDING_SCENE_H_

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "SimpleAudioEngine.h"
#include "allScene.h"
#include <fstream>
#include <string>
#include <vector>

USING_NS_CC;
using namespace std;

class userInfo
{
public:
	string name;
	int score;
	bool ifCur;

	userInfo(string s = "Mr. Ya", int score = 0, bool cur = 0)
	{
		this->name = s;
		this->score = score;
		this->ifCur = cur;
	}
	bool operator<(userInfo& u){
		return this->score < u.score;
	}

	bool operator>(userInfo& u){
		return this->score > u.score;
	}

	bool operator==(userInfo& u){
		return (this->score == u.score);	
	}
};

class RankingBoard : public Sprite
{
private:
	int curScore;
public:
	//RankingBoard();
	//~RankingBoard();

	virtual bool init();

	vector<userInfo> getRankInfo();			// Get ranking information from rank.txt
	
	int getCurScore(){
		return this->curScore;
	}

	CREATE_FUNC(RankingBoard);
	/* data */
};

class rankSprite : public Sprite
{
private:
	string name;
	LabelTTF* rankNumLabel;
	LabelTTF* scoreLabel;
	LabelTTF* nameLabel;
public:
	virtual bool init();
	
	void createSprite(int r = 0, string s = "", int n = 0, bool ifCur = false);
	CREATE_FUNC(rankSprite);
};

class endLayer : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
	void backToMain(Ref* pSender);
	void getRank();
	void newgame(Ref* pSender);
	void getScore();

	CREATE_FUNC(endLayer);
private:
	int curScore;
	RankingBoard* rankBoard;
};

#endif