#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void onEnter() override;
	bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

	bool cutIntoMask(Point* targets, int count, Point st, Point ed, Point** maskLPts, int* maskLNum, Point** maskRPts, int* maskRNum);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world){ m_world = world; };

	void OnceAgain(float);
private:

	Point touchStart;
	Point touchEnd;
	ClippingNode* clipper;
	Sprite* slashObj;
	bool _getIntersect(Point st, Point ed, float k, float b, float tmp_k, float tmp_b, float* x, float* y);
	DrawNode* _makeDrawNode(Point* points, int count);
	bool _calcLineEquation(Point st, Point ed, float* k, float* b);
	bool _splitSprite(Sprite* sprite, Point st, Point ed, Point* shape, int count, ClippingNode** part1, ClippingNode** part2);
	ClippingNode* _makeClippingNode(Point* mask, int count, Point* physicBody, int p_count, Sprite* content);
	Sprite* _duplicateSprite(Sprite* sprite);
	static const int OBJ_SHAPE_NUM = 5;
	Point objShape[OBJ_SHAPE_NUM];
};

#endif // __HELLOWORLD_SCENE_H__

