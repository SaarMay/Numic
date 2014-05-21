#ifndef _GAME_PAUSE_SCENE_H_
#define _GAME_PAUSE_SCENE_H_

#include "allScene.h"
USING_NS_CC;

class pauseScene : public cocos2d::Scene
{
public:
	virtual bool init();
	static cocos2d::Scene* scene();
//	pauseScene : public cocos2d::Scene();
//	~pauseScene : public cocos2d::Scene();

//private:

};

class pauseBgLayer : public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(pauseBgLayer);
//	pauseBgLayer(arguments);
//	~pauseBgLayer();

	/* data */
};

class pauseLayer
{
public:
	//pauseLayer(arguments);
	//~pauseLayer();

	virtual bool init();

	// start new game
	void _restartGame(cocos2d::Ref* pSender);
	// resume 
	void _resumeGame(cocos2d::Ref* pSender);
	// back to main
	void _backToMain(cocos2d::Ref* pSender);

	CREATE_FUNC(pauseBgLayer);
	/* data */
};

#endif
