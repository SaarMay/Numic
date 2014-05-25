#ifndef _ENDING_SCENE_H_
#define _ENDING_SCENE_H_

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "SimpleAudioEngine.h"

class endLayer : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
	void backToMain(cocos2d::Ref* pSender);
	void getRank();
	void newgame();

	CREATE_FUNC(endLayer);
};
#endif