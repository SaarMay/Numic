#ifndef _RANKING_BOARD_H_
#define _RANKING_BOARD_H_ 

#include "allScene.h"
#include <fstream>
#include <string>
#include <vector>
USING_NS_CC;

class RankingBoard : public Layer
{
public:
	RankingBoard();
	~RankingBoard();

	virtual bool init();

	vector<userInfo> getRankInfo();			// Get ranking information from rank.txt

	CREATE_FUNC(RankingBoard);
	/* data */
};

class rankSprite : public Sprite
{
private:
	string name;
	LabelTTF* rankNum;
	LabelTTF* score;
	LabelTTF* name;
public:
	virtual bool init();
	
	rankSprite* createSprite(int r, string s, int n, bool ifCur);
	CREATE_FUNC(rankSprite);
};

class userInfo
{
public:
	string name;
	int score;
	bool ifCur;

	userInfo(string s = "Mr.Black", int score = 0, bool cur = 0)
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

#endif