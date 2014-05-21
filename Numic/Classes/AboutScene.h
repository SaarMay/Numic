#ifndef _ABOUT_SCENE_H_
#define _ABOUT_SCENE_H_

#include "allScene.h"

class aboutLayer : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
	void backTostart(cocos2d::Ref* pSender);

	CREATE_FUNC(aboutLayer);
};


#endif