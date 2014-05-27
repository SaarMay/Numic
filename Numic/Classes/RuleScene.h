#ifndef _RULE_SCENE_H_
#define _RULE_SCENE_H_

#include "allScene.h"
USING_NS_CC;


class ruleLayer : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void _backToMain(Ref* sender);
    
    // implement the "static node()" method manually
	CREATE_FUNC(ruleLayer);
};

#endif
