#ifndef _START_SCENE_H_
#define _START_SCENE_H_
#include "allScene.h"
USING_NS_CC;

class StartScene : public cocos2d::Scene
{
public:
	virtual bool init();

	static cocos2d::Scene* start();
	void menuCallback(cocos2d::Ref* pSender);
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