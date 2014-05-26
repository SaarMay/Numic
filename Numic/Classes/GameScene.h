#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "allScene.h"
#include <string>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

USING_NS_CC;
using namespace std;

class gameLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // a selector callback
	void _pauseBtnCallback(Object* pSender);

	virtual void onEnter() override;
	bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
	bool onContactBegin(PhysicsContact& contact);
	void update();

	bool cutIntoMask(Point* targets, int count, Point st, Point ed, Point** maskLPts, int* maskLNum, Point** maskRPts, int* maskRNum);

    // implement the "static create()" method manually
    CREATE_FUNC(gameLayer);

	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world){ m_world = world; };
	
	void OnceAgain(float dt);

	~gameLayer()
	{
		delete this->objShape;
	}

private:
	void _preloading();		// preloading SpriteCacheFrame

	// Timer setting part
	int t;
	LabelTTF* timer;
	void setTimer(float t);

	// Cutting part
	Point touchStart;
	Point touchEnd;
	ClippingNode* clipper;
	Sprite* slashObj;
	bool _getIntersect(Point st, Point ed, float k, float b, float tmp_k, float tmp_b, float* x, float* y);
	DrawNode* _makeDrawNode(Point* points, int count);
	bool _calcLineEquation(Point st, Point ed, float* k, float* b);
	bool _splitSprite(Sprite* sprite, Point st, Point ed, Point* shape, int count, ClippingNode** part1, ClippingNode** part2);
	ClippingNode* _makeClippingNode(Point* mask, int count, Point* physicBody, int p_count, Sprite* content);
	Sprite* _makeSmallSprite(int label);
	Sprite* _duplicateSprite(Sprite* sprite);
	bool _isInTheMiddle(float x, float x1, float x2);
	Point* objShape;				// Different objShape
	int shapeLabel;					// Record the shape of the origin shape
	MotionStreak* streak;

	// Generating part: Randomly generate number block names
	int tar[2];									// Target Information
	LabelTTF* targetLabel;
	Sprite* targetBar;
	void setTarget(float part, float total);		// Set the target bar
	bool setSlashObj();							// Set Slash object radomly

	// Marking part
	string user;						// User name
	void setMatchrate();				// Set the matchrate
	float matchRate;					// Match the result with the target
	LabelTTF* scoreLabel;
	void setScore();

	// show marks
	LabelTTF* markBox;				// Record the marks for very cut
	void setMarkBox();					// Set mark box for every part

	//virtual void keyBackClicked();
};

// game background
class gameBgLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	
	//bool cngBackground(Sprite* bgsprit);

	CREATE_FUNC(gameBgLayer);
};


#endif // __gameLayer_SCENE_H__

