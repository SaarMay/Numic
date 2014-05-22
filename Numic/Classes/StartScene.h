#ifndef _START_SCENE_H_
#define _START_SCENE_H_
#include "allScene.h"
#include <string>
#include <fstream>

USING_NS_CC;
using namespace std;

class StartScene : public Scene
{
private:
	string username;
public:
	virtual bool init();

	static cocos2d::Scene* start(string user);
	void menuCallback(cocos2d::Ref* pSender);

	void setUsername(string usr = "Mrs.Ya");
};

class startBgLayer : public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(startBgLayer);
};

class startBtnLayer : public cocos2d::Layer
{
public:
	virtual bool init();

	void gameStarting(cocos2d::Ref* pSender);

	CREATE_FUNC(startBtnLayer);
};

class startMenuLayer : public cocos2d::Layer
{
private:
	bool musicOn;
public:
	virtual bool init();

	// ÒôÐ§ÉèÖÃ£¬ musicSwitchÏìÓ¦ÊÂ¼þ
	void musicSwitching(cocos2d::Ref* pSender);
	// ÓÎÏ·ÉèÖÃ£¬ settingBtnÏìÓ¦ÊÂ¼þ
	void aboutUs(cocos2d::Ref* pSender);
	// ÏÔÊ¾ÅÅÃû£¬ rankingBtnÏìÓ¦ÊÂ¼þ
	void rankingCall(cocos2d::Ref* pSender);
	// ÓÎÏ·¹æÔò£¬ ruleBtnÏìÓ¦ÊÂ¼þ
	void ruleCall(cocos2d::Ref* pSender);
	CREATE_FUNC(startMenuLayer);
	
};

#endif