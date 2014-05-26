
// Naming Rules:
// Tag Name - [Scene][Layer][layer-order][Sprite]
// Number Name - [shapr]["item"][value][".png"]

#include "GameScene.h"
#include "CCProtocols.h"
#include "CCTexture2D.h"
#include "ccTypes.h"
#define COCOS2D_DEBUG 1

USING_NS_CC;

using namespace std;
using namespace CocosDenshion;

static int cuttedState = 0;
static int OBJ_SHAPE_NUM = 0;

void gameLayer::_preloading()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("SoundEffect/GameBgMusic.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("SoundEffect/cut.wav");

	//SimpleAudioEngine::getInstance()->preloadEffect("effect1.ogg");
	//SimpleAudioEngine::getInstance()->preloadEffect("effect2.ogg");
	//SimpleAudioEngine::getInstance()->preloadEffect("effect3.ogg");
	//SimpleAudioEngine::getInstance()->preloadEffect("effect4.ogg");
	//SimpleAudioEngine::getInstance()->preloadEffect("effect5.ogg");
	//SimpleAudioEngine::getInstance()->preloadEffect("effect6.ogg");
	//SimpleAudioEngine::getInstance()->preloadEffect("effect7.ogg");
	//SimpleAudioEngine::getInstance()->preloadEffect("effect8.ogg");

	SimpleAudioEngine::getInstance()->setEffectsVolume(0.7);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameScene/numFrame.plist","GameScene/numFrame.png");
}

void gameLayer::setTarget(float p, float t)
{
	Size winSize = Director::getInstance()->getWinSize();
	
	float val = p / t;										// Setting programbar value
	string targetStr = "2"; 
	targetStr[0] = (int)p + 48;
	
	// If don't exist then create
	if(this->targetBar == NULL || this->targetLabel == NULL)
	{
		// target bar
		targetBar = Sprite::create("GameScene/targetBar.png");
		targetBar->setAnchorPoint(ccp(1,1));
		targetBar->setPosition(ccp(winSize.width*val, winSize.height-2));	// Set position of the target bar
		targetBar->setScale(winSize.width / targetBar->getContentSize().width);
		// target box
		targetLabel = LabelTTF::create(targetStr,"AdobeArabic Bold",24);			// Generate font
		targetLabel->setAnchorPoint(ccp(0.5,0.5));
		auto targetBox = Sprite::create("GameScene/targetBox.png");
		targetLabel->setPosition(targetBox->getContentSize().width/2, (targetBox->getContentSize().height-16)/2 );
		targetBox->addChild(targetLabel);
		targetBox->setPosition(ccp(winSize.width*val, 
			(winSize.height - targetBar->getContentSize().height - 35)));
		this->addChild(targetBar,1,3110);			
		this->addChild(targetBox,1,3111);		
	}
	
	else
	{
		targetBar->setPositionX(winSize.width*val);			// Set position of the target bar
		targetLabel->setString(targetStr);					// Set target value
		targetLabel->getParent()->setPositionX(winSize.width*val);
	}
					
}

bool gameLayer::setSlashObj()
{
	auto s = Director::getInstance()->getWinSize();
	
	ParticleSystem* explode = ParticleSystemQuad::create("ParticleSys/exploding.plist");
	explode->retain();
	explode->setAutoRemoveOnFinish(true);
	explode->setSpeed(300);
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(explode->getTexture());
	batch->addChild(explode);
	batch->setPosition(s.width/2, s.height/2);
	this->addChild(batch);

	string numName = "titem7.png";

	srand((unsigned)time(NULL));

	// Genrate number block type
	int type = rand() % 3;
	switch (type)
	{
	case 0:
		numName[0] = 'r';
		break;
	case 1:
		numName[0] = 'c';
		break;
	case 2:
		numName[0] = 't';
		break;
	default:
		CCLog("Type generate failed.");
		return false;
		break;
	}

	// Generate target
	int total = rand() % 5 + 5;
	int part = rand() % (total-1) + 1;
	
	numName[5] = total+48;

	this->tar[0] = total;
	this->tar[1] = part;
	this->shapeLabel = type;

	// Set slash object
	this->slashObj = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(numName));
	
	auto fadein = FadeIn::create(0.5f);

	slashObj->setAnchorPoint(Point(0.5,0.5));
	slashObj->setPosition( Point(s.width / 2, s.height / 2) );
	slashObj->setTag(315);
	slashObj->setOpacity(0);
	slashObj->runAction(fadein);
	
	float width = slashObj->getContentSize().width;
	float height = slashObj->getContentSize().height;
	
	if(type == 2)
	{
		this->objShape = new Point[3];
		objShape[2] = Point(0, height/-2 -10);
		objShape[1] = Point(width/2 + 10, (height/2));
		objShape[0] = Point(width/-2 -10, (height/2));
		OBJ_SHAPE_NUM = 3;
	}

	else 
	{
		this->objShape = new Point[4];
		objShape[3] = Point(width/-2, height/-2);
		objShape[2] = Point(width/2, height/-2);
		objShape[1] = Point(width/2, height/2);
		objShape[0] = Point(width/-2, height/2);
		OBJ_SHAPE_NUM = 4;
	}
	
	return true;
}

void gameLayer::setScore()
{	
	if(this->scoreLabel == NULL)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();

		scoreLabel = LabelTTF::create("0","AdobeArabic Bold",30);
		scoreLabel->setColor(Color3B(255,255,255));
		scoreLabel->setAnchorPoint(ccp(1,0.5));
		scoreLabel->setPosition(visibleSize.width-100 , visibleSize.height - 100);
		
		this->addChild(scoreLabel);
	}
	
	else{
		this->setMatchrate();
		this->setMarkBox();
		int score = atoi(scoreLabel->getString().c_str());
		stringstream ss;
		string tstr;
		
		score += abs(matchRate)*15;
		//CCLog("Origin: %d",score);

		ss << score;
		ss >> tstr;

		scoreLabel->setString(tstr);

		/*auto fadeOut = FadeOut::create(0.5);
		markBox->runAction(fadeOut);*/
	}
}

//void gameLayer::keyBackClicked()
//{
//
////        JniMethodInfo minfo;
////        bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/Numic/Numic/NumicAndroid",
////"sendCloseAppMessage","()V");
////        
////       if(!isHave){
////           CCLog("jni:此方法不存在");
////        }else{
////            minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID);
////        }
////        
////        CCLog("jni:jni-java执行完毕");
//
//}

void gameLayer::setMarkBox()
{
	auto winSize = Director::getInstance()->getWinSize();
	if(this->markBox == NULL){
		//auto winSize = Director::getInstance()->getWinSize();
		markBox = LabelTTF::create("","AdobeArabic Bold",70);
		auto color = Color3B(255,0,0);
		markBox->setColor(color);
		markBox->setAnchorPoint(ccp(0,1));
		this->addChild(markBox);
	}

	else
	{
		markBox->setOpacity(100);
		stringstream ss;
		string curStr;
		int curScore = abs(this->matchRate)*15;

		ss << curScore;
		ss >> curStr;

		markBox->setString(curStr);
		//auto fadein = FadeIn::create(0.2);
		auto fadeOut = FadeOut::create(1);
		
		auto jump = JumpTo::create(1,this->scoreLabel->getPosition(),winSize.height/3,1);

		auto spwAct = Spawn::create(jump,fadeOut,NULL);
		//markBox->runAction(jump);

		markBox->runAction(spwAct);
	}

	markBox->setPosition(winSize.width/2 + 130, winSize.height/2);	
}

Scene* gameLayer::createScene()
{
    //// 'scene' is an autorelease object
    //auto scene = Scene::create();
    //
    //// 'layer' is an autorelease object
    //auto layer = gameLayer::create();

    //// add layer as a child to scene
    //scene->addChild(layer);

    //// return the scene
    //return scene;


	auto scene = Scene::createWithPhysics();

    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setSpeed(4.0);

	auto bgLayer = gameBgLayer::create();
    auto layer = gameLayer::create();

    layer->setPhyWorld(scene->getPhysicsWorld());

	scene->addChild(bgLayer);
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool gameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
	// My Code Starts here
	this->_preloading();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("SoundEffect/GameBgMusic.mp3",true);

	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	boundBody->setContactTestBitmask(true);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody); 
	this->addChild(edgeSp); 
	edgeSp->setTag(0);
	
	auto s = Director::getInstance()->getWinSize();
	
	this->timer = NULL;
	this->targetBar = NULL;
	this->targetLabel = NULL;
	this->scoreLabel = NULL;
	this->matchRate = 1.5;
	this->user = "UnKnown";
	
	this->setSlashObj();
	this->addChild(slashObj);


	auto pauseBtn = MenuItemImage::create("Buttons/pauseBtn.png","Buttons/pauseBtn.png",
						CC_CALLBACK_1(gameLayer::_pauseBtnCallback, this));
	pauseBtn->setAnchorPoint(ccp(1,0));
	pauseBtn->setPosition(ccp(Director::getInstance()->getWinSize().width - 50, 50));
	auto pauseMenu = Menu::create(pauseBtn,NULL);
	pauseMenu->setPosition(0,0);
	this->addChild(pauseMenu);

	//auto pauseBtn = MenuItemImage("pauseBtn.png","pauseBtn.png",
	//							CC_CALLBACK_1(gameLayer::pauseBtnCallBack, this));

	this->setTarget(this->tar[1], this->tar[0]);
	this->setScore();

	//
	this->streak = MotionStreak::create(1,3,15,Color3B(255,255,255),"cutLight.png");
	this->addChild(streak);
	streak->setPosition(visibleSize.width/2,visibleSize.height/2);

	this->markBox = NULL;
	this->setMarkBox();

	return true;
}

bool gameLayer::_getIntersect(Point st, Point ed, float k, float b, float tmp_k, float tmp_b, float* x, float* y)
{
	if(abs(k - tmp_k) < 0.0001f) { return false; }

	*x = (tmp_b - b) / (k - tmp_k);
	*y = (tmp_k*b - k*tmp_b) / (tmp_k - k);
		
	if(((abs(tmp_k) < 0.0001f) || (abs(k) < 0.0001f)) && (*x-st.x)*(*x-ed.x)<0)
	{
		return true;
	}

	if( (*x-st.x)*(*x-ed.x)<0 && // x in the middle of two points
		(*y-st.y)*(*y-ed.y)<0)  // y in the middle of two points
	{
		return true;
	}else
	{
		return false;
	}
}

// 200+ lines ... too Dirty ...
bool gameLayer::cutIntoMask(Point* targets, int count, Point st, Point ed, Point** maskLPts, int* maskLNum, Point** maskRPts, int* maskRNum)
{
	float tmp_k, tmp_b;
	float k, b;
	Point intersectPoints[2];
	int intersectIndex[2];
	float x, y;
	int count_intersect = 0;

	if(_calcLineEquation(st, ed, &k, &b))
	{
		for(int i=0; i<count-1; i++)
		{
			if(_calcLineEquation(targets[i], targets[i+1], &tmp_k, &tmp_b))
			{
				if(_getIntersect(targets[i], targets[i+1], k, b, tmp_k, tmp_b, &x, &y))
				{
					intersectPoints[count_intersect] = Point(x,y); 
					intersectIndex[count_intersect] = i;

					count_intersect++;
					
				}
			}else if(abs(targets[i].x - targets[i+1].x) < 0.0001f)
			{
				float _y = k*targets[i].x+b;
				if(_isInTheMiddle(_y, targets[i].y, targets[i+1].y))  // intersect with vertical line
				{
					intersectPoints[count_intersect] = Point(targets[i].x, _y); 
					intersectIndex[count_intersect] = i;

					count_intersect++;
				}
			}else {
				return false;
			}

			if(count_intersect >= 2)
			{
				break;
			}
		}
		// Dirty Code =_=||| But I don't wanna refactor it.
		if(count_intersect <2) 
		{
			if(_calcLineEquation(targets[count-1], targets[0], &tmp_k, &tmp_b))
			{
				if(_getIntersect(targets[count-1], targets[0], k, b, tmp_k, tmp_b, &x, &y))
				{
					intersectPoints[count_intersect] = Point(x,y); 
					intersectIndex[count_intersect] = count-1;

					count_intersect++;
					
				}
			}else if(abs(targets[count-1].x - targets[0].x) < 0.0001f)
			{
				float _y = k*targets[count-1].x+b;
				if(_isInTheMiddle(_y, targets[count-1].y, targets[0].y))  // intersect with vertical line
				{
					intersectPoints[count_intersect] = Point(targets[count-1].x, k*targets[count-1].x+b); 
					intersectIndex[count_intersect] = count-1;

					count_intersect++;
				}
			}else {
				return false;
			}
		}
	}else // if draw line is vertical
	{
		for(int i=0; i<count-1; i++)
		{
			if(_calcLineEquation(targets[i], targets[i+1], &tmp_k, &tmp_b))
			{
				float _y = tmp_k*ed.x+tmp_b;
				if(_isInTheMiddle(_y, targets[i].y, targets[i+1].y))  // intersect with vertical line
				{
					intersectPoints[count_intersect] = Point(ed.x, tmp_k*x+tmp_b); 
					intersectIndex[count_intersect] = i;

					count_intersect++;
				}
			}
			if(count_intersect >= 2)
			{
				break;
			}
		}
		if(count_intersect <2) 
		{
			if(_calcLineEquation(targets[count-1], targets[0], &tmp_k, &tmp_b))
			{
				float _y = tmp_k*ed.x+tmp_b;
				if(_isInTheMiddle(_y, targets[count-1].y, targets[0].y))  // intersect with vertical line
				{
					intersectPoints[count_intersect] = Point(ed.x, tmp_k*x+tmp_b); 
					intersectIndex[count_intersect] = count-1;

					count_intersect++;
				}
			}
		}
	}

	if(count_intersect < 2)
	{
		return false;
	}

	// Split intersectPoints into maskL & maskR
	*maskRNum = intersectIndex[1] - intersectIndex[0] + 2;
	*maskLNum = count - *maskRNum + 4;
	*maskLPts = new Point[*maskLNum];
	*maskRPts = new Point[*maskRNum];

	// add to maskL
	int j = 0;
	for(int i=0; i<=intersectIndex[0]; i++,j++)
	{
		(*maskLPts)[j] = targets[i];
	}

	(*maskLPts)[j++] = intersectPoints[0];
	(*maskLPts)[j++] = intersectPoints[1];

	for(int i=intersectIndex[1]+1; i<count; i++,j++)
	{
		(*maskLPts)[j] = targets[i];
	}

	// add to maskR
	j = 0;
	(*maskRPts)[j++] = intersectPoints[1];
	(*maskRPts)[j++] = intersectPoints[0];

	for(int i=intersectIndex[0]+1; i<=intersectIndex[1]; i++,j++)
	{
		(*maskRPts)[j] = targets[i];
	}	
}

// judge if the x is in the middle of [x1, x2]
bool gameLayer::_isInTheMiddle(float x, float x1, float x2)
{
	return (x-x1)*(x-x2) <= 0;
}

DrawNode* gameLayer::_makeDrawNode(Point* points, int count)
{
	auto shape = DrawNode::create();
	static Color4F green(0, 1, 0, 1);
    shape->setAnchorPoint(Point(0.5,0.5));
	shape->drawPolygon(points, count, green, 0, green);
	return shape;
}

bool gameLayer::_calcLineEquation(Point st, Point ed, float* k, float* b)
{
	if(st.equals(ed))
		return false;
	else
	{
		if(abs(st.x - ed.x) < 0.0001f)
		{
			return false;
		}
		else
		{
			*k = (st.y - ed.y) / (st.x - ed.x);
			*b = ed.y - (*k) * ed.x;
			return true;
		}
	}
}

void gameLayer::onEnter()
{
	Layer::onEnter();

	// Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(gameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(gameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(gameLayer::onTouchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(gameLayer::onContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->schedule(schedule_selector(gameLayer::setTimer),1);
	this->setKeypadEnabled(true);
}

bool gameLayer::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    /*if (_state != kPaddleStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
    
    _state = kPaddleStateGrabbed;*/

	this->touchStart = touch->getLocation();

    CCLOG("return true");
    return true;
}

void gameLayer::onTouchMoved(Touch* touch, Event* event)
{
	SimpleAudioEngine::getInstance()->playEffect("SoundEffect/cut.wav",false);

	auto pos = touch->getLocation();
	this->streak->setPosition(pos);
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get Sets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
}

void gameLayer::onTouchEnded(Touch* touch, Event* event)
{
	CCLOG("Paddle::onTouchEnd id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
	this->touchEnd = touch->getLocation();

	auto _emitter = ParticleFlower::create();
	_emitter->retain();
	this->addChild(_emitter,5,5555);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png"));
	_emitter->setPosition(touchEnd);
	_emitter->setLife(0.5);
	_emitter->setSpeed(300);
	_emitter->setAutoRemoveOnFinish(true);
	_emitter->update(2);

	//auto fadeout = FadeOut::create(0.5f);
	//_emitter->runAction(fadeout);

	Point st, ed;
	st = slashObj->convertToNodeSpaceAR(this->convertToWorldSpace(this->touchStart));
	ed = slashObj->convertToNodeSpaceAR(this->convertToWorldSpace(this->touchEnd));
	ClippingNode* part1=nullptr;
	ClippingNode* part2=nullptr;

	if(_splitSprite(slashObj, st, ed, objShape, OBJ_SHAPE_NUM, &part1, &part2))
	{
		if(this->matchRate <= 1.1 && this->matchRate >= 0.9)
		{
			this->addChild(_makeSmallSprite(1),1,3151);
			this->addChild(_makeSmallSprite(2),1,3152);
		}

		else{
			this->addChild(part1,1,3151);
			this->addChild(part2,1,3152);
		}

		this->removeChild(slashObj);
	}
	
	this->setScore();
	//this->markBox->setPosition(touchEnd);
}

bool gameLayer::onContactBegin(PhysicsContact& contact)
{
	//if (cuttedState == 2)
	//{
	//	this->removeChildByTag(3151);
	//	this->removeChildByTag(3152);
	//	this->setSlashObj();
	//	this->addChild(slashObj);
	//	
	//	cuttedState = 0;
	//	return true;
	//}
	//else if (cuttedState == 0)
	//{
	//	cuttedState++;
	//	return false;
	//}

	//else 
	//	return true;

	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if(nodeA->getTag() + nodeB->getTag() == 6303)
		return true;

	if(nodeA->getTag() == 3151 || nodeA->getTag() == 3152)
		this->removeChild(nodeA);
	string effect = "effect0.ogg";
	int match;

	if(0.2-abs(matchRate-1) < 0)
		match = 0;
	else
		match = 1;

	switch (nodeA->getTag())
	{
	case 3151:
		this->removeChild(nodeA);
		effect[6] = tar[1]*match + 48;
		SimpleAudioEngine::getInstance()->playEffect(effect.c_str());
		break;
	case 3152:
		this->removeChild(nodeA);
		effect[6] = (tar[0]-tar[1])*match + 48;
		SimpleAudioEngine::getInstance()->playEffect(effect.c_str());
		break;
	default:
		break;
	}

	switch (nodeB->getTag())
	{
	case 3151:
		this->removeChild(nodeB);
		effect[6] = tar[1]*match + 48;
		SimpleAudioEngine::getInstance()->playEffect(effect.c_str());
		break;
	case 3152:
		this->removeChild(nodeB);
		effect[6] = (tar[0]-tar[1])*match + 48;
		SimpleAudioEngine::getInstance()->playEffect(effect.c_str());
		break;
	default:
		break;
	}
	
	if(this->getChildByTag(3151) == NULL && this->getChildByTag(3152) == NULL)
	{
		this->setSlashObj();
		this->setTarget((float)this->tar[1], (float)this->tar[0]);
		this->addChild(slashObj);
	}

	return false;
}

void gameLayer::setTimer(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if(this->timer == NULL)
	{
		this->t = 60;
		timer = LabelTTF::create("","AdobeArabic Bold",24);			// Generate font
		timer->setColor(Color3B(255,255,255));
		timer->setAnchorPoint(ccp(0,0.5));
		timer->setPosition(30,visibleSize.height-100);
		timer->setTag(3100);
		this->addChild(timer,0);
	}

	stringstream ss;
	string tstr;
	ss << t;
	ss >> tstr;
	timer->setString("00:"+tstr);
	
	if(this->t < 10)
	{
		// Set color red
		this->timer->setColor(Color3B(220, 0, 0));
		timer->setString("00:0"+tstr);
	}

	if(this->t <= 0)
	{
		// Remove number block, remove time lable, show timeUp, keep score
		this->removeChild(slashObj);			// Remove number block
		//this->removeChild(timer);			// Remove time lable
		
		timer->setString("");
		auto tup = Sprite::create("GameScene/timeUp.png");
		tup->setAnchorPoint(ccp(0.5,0.5));
		tup->setPosition(visibleSize.width/2, visibleSize.height/2);
		this->addChild(tup, 9, 319);

		// store the current rank info into the file
		ofstream rankout("Ranking.txt",std::ofstream::app);
		rankout << this->scoreLabel->getString() << "\n";

		// Enter the game ending scene
		Director::getInstance()->replaceScene(
			TransitionCrossFade::create(1.0f, endLayer::scene()));
		//Director::getInstance()->replaceScene(
			//TransitionCrossFade::create(1.0f, EndingScene::scene());
	}

	ss << t;
	ss >> tstr;
	timer->setString("00:"+tstr);
	
	if(this->t < 10)
	{
		// Set color red
		this->timer->setColor(Color3B(220, 0, 0));
		timer->setString("00:0"+tstr);
	}
	
	this->t--;
}

/*
 * sprite: Sprite to be splited
 * st, ed: two endians of the split line 
 * shape: the shape of Sprite's PhysicsBody
 * count: length of shape
 * part1, part2: the result;
 *
 * RETURN: split or not
 */
bool gameLayer::_splitSprite(Sprite* sprite, Point st, Point ed, Point* shape, int count, ClippingNode** part1, ClippingNode** part2)
{
	Point* maskL = nullptr;
	Point* maskR = nullptr;
	int maskLNum=0, maskRNum=0;

	if(cutIntoMask(shape, count, st, ed, &maskL, &maskLNum, &maskR, &maskRNum))
	{
		*part1 = _makeClippingNode(maskL, maskLNum, maskR, maskRNum, sprite);
		*part2 = _makeClippingNode(maskR, maskRNum, maskL, maskLNum, sprite);

		(*part1)->setRotation(15);
		(*part2)->setRotation(-15);
		
		this->scheduleOnce(schedule_selector(gameLayer::OnceAgain), 2.0f);

		return true;
	}
	
	else {
		return false;
	}
}

Sprite* gameLayer::_duplicateSprite(Sprite* sprite)
{
	auto duplicate = Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
	duplicate->setPosition(sprite->getPosition());
	duplicate->setScale(sprite->getScale());
	duplicate->setAnchorPoint(sprite->getAnchorPoint());

	return duplicate;
}

Sprite* gameLayer::_makeSmallSprite(int label)
{
	string numName = "ritem1.png";
	Vect vVect;
	float scale;
	switch (rand()%3)
	{
	case 0:
		numName[0] = 'r';
		break;
	case 1:
		numName[0] = 'c';
		break;
	case 2:
		numName[0] = 't';
		break;
	default:
		break;
	}

	if(label == 1){
		numName[5] = this->tar[1] + 48;
		vVect = Vect(1,0);
		scale = sqrt((float)tar[1] / (float)tar[0]);
	}
	else if(label == 2){
		numName[5] = this->tar[0] - tar[1] + 48;
		vVect = Vect(-2,0);
		scale = sqrt((float)(tar[0]-tar[1])/(float)tar[0]);
	}

	auto _sprite = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(numName));
	_sprite->setPosition(slashObj->getPosition());
	_sprite->setScale(scale);

	float width = _sprite->getContentSize().width;
	float height = _sprite->getContentSize().height;
	
	Point objBox[4];
	objBox[3] = Point(width/-2, height/-2);
	objBox[2] = Point(width/2, height/-2);
	objBox[1] = Point(width/2, height/2);
	objBox[0] = Point(width/-2, height/2);

	auto physicsBody = PhysicsBody::createPolygon(objBox, 4 , PHYSICSBODY_MATERIAL_DEFAULT);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setVelocity(vVect);
	physicsBody->setRotationEnable(true);

	_sprite->setPhysicsBody(physicsBody);

	auto rotate = RotateBy::create(1.5f,270);

	_sprite->runAction(rotate);

	return _sprite;
}

ClippingNode* gameLayer::_makeClippingNode(Point* mask, int count, Point* physicBody, int p_count, Sprite* content)
{
	auto sprite = _duplicateSprite(content);
	
	auto _clipper = ClippingNode::create();
	_clipper->setPosition(content->getPosition());
	_clipper->setInverted(true);
	_clipper->setOpacity(0);
	_clipper->setAnchorPoint(Point::ZERO);
	_clipper->addChild(sprite);
	auto shape = _makeDrawNode(mask, count);

	_clipper->addChild(shape);
	_clipper->setStencil(shape);
	
	auto physicsBody = PhysicsBody::createPolygon(physicBody, p_count,PHYSICSBODY_MATERIAL_DEFAULT);
	physicsBody->setContactTestBitmask(true);
	physicsBody->applyTorque(0.5);
	//physicsBody->setVelocity(Vect(50,150));

	_clipper->setPhysicsBody(physicsBody);


	sprite->setPosition(Point::ZERO);
	
	return _clipper;
}

void gameLayer::setMatchrate()
{
	Point startPoint = this->touchStart;
	Point endPoint = this->touchEnd;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// this->objShape stores the vertex information
	float k,b,d,angle,per,likelihood,l;
	k=(endPoint.y-startPoint.y)/(endPoint.x-startPoint.x);

	b=startPoint.y-k*startPoint.x;
    d=abs(visibleSize.height / 2-k*visibleSize.width / 2-b)/sqrt(1+k*k);
	if(d<80){
	angle=2*acos(d/80);
	per=((angle-sin(angle))/(2*3.14159));//(1-(angle-sin(angle))/(2*3.14159));
     if(2*tar[1]<tar[0])
	this->targetBar->setPositionX(Director::getInstance()->getWinSize().width*per);
	 else
    this->targetBar->setPositionX(Director::getInstance()->getWinSize().width*(1-per));
	likelihood=per/min((float)tar[1]/(float)tar[0],1-(float)tar[1]/(float)tar[0]);
	l=min(likelihood,1/likelihood);

	//if(this->objShape);
	//else
	

	switch (this->shapeLabel)
	{
	case 0:
		// If it is a rectangle
		matchRate =l ;
		break;
	case 1:
		// If it is a circle
	   matchRate =l;
	
		break;
	case 2:
		// If it is a triangle
		matchRate=l;
		break;
	default:
		//matchRate=0.7;
		break;
	}
	}
	else
	{//if(this->objShape);
	//else
		this->targetBar->setPositionX(0);
		matchRate=0;	 }
}

void gameLayer::OnceAgain(float dt)
{
	cuttedState++;
}

bool gameBgLayer::init()
{
	if ( !Layer::init() )
        return false;

	auto winSize = Director::getInstance()->getWinSize();

	auto bgSprite = Sprite::create("GameScene/gameBg.png");
	float width = bgSprite->getContentSize().width;
	float height = bgSprite->getContentSize().height;
	float scaleRateW = winSize.width / width;
	float scaleRateH = winSize.height / height;
	bgSprite->setScale(scaleRateW,scaleRateH);
	//bgSprite->setContentSize(winSize);
	bgSprite->setPosition(Point(winSize/2));

	this->addChild(bgSprite);

	return true;
}

void gameLayer::_pauseBtnCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->pushScene(pauseScene::scene());
}
//void gameLayer::_pauseBtnCallBack(cocos2d::Ref* pSender)
//{
//	Director::getInstance()->pushScene(pauseScene::scene());
//}

