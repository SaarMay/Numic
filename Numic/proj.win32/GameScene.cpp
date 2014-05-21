#include "GameScene.h"
#define COCOS2D_DEBUG 1
USING_NS_CC;


bool GameScene::init()
{
	if(!Scene::init())
		return false;
	
	this->createWithPhysics();
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
;

	auto gameL = gameLayer::create();
	gameL->setPhyWorld(this->getPhysicsWorld());

	return true;
}

Scene* GameScene::scene()
{
    //// 'scene' is an autorelease object
    //auto scene = Scene::create();
    //
    //// 'layer' is an autorelease object
    //auto layer = HelloWorld::create();

    //// add layer as a child to scene
    //scene->addChild(layer);

    //// return the scene
    //return scene;
	auto scene = new GameScene;
	scene->init();

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

	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 0);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody); this->addChild(edgeSp); edgeSp->setTag(0);

	/*auto shape = DrawNode::create();
    static Point polyMask[4];
	float width = slashObj->getContentSize().width * slashObj->getScale();
	float height = slashObj->getContentSize().height * slashObj->getScale();
	polyMask[0] = Point(0, 0);
    polyMask[1] = Point(width/2, 0);
    polyMask[2] = Point(width/2, height);
	polyMask[3] = Point(0, height);
	
	static Color4F green(0, 1, 0, 1);
    shape->setAnchorPoint(Point(0.5,0.5));
	shape->drawPolygon(polyMask, 4, green, 0, green);*/
	
	/*clipper = ClippingNode::create();
	clipper->setPosition( Point(s.width / 2 - 50, s.height / 2 - 50) );
	clipper->setInverted(true);
	clipper->addChild(slashObj);
	clipper->setStencil(shape);
	clipper->setAnchorPoint(Point(0.5,0.5));*/
	
	auto s = Director::getInstance()->getWinSize();
	slashObj = Sprite::create("grossini.png");
	slashObj->setPosition( Point(s.width / 2 , s.height / 2) );
	//slashObj->setScale(1.5);
	slashObj->setAnchorPoint(Point(0.5,0.5));

	float width = slashObj->getContentSize().width;
	float height = slashObj->getContentSize().height;
	objShape[3] = Point(0, 0);
    objShape[2] = Point(width, 0);
    objShape[1] = Point(width, height);
	objShape[0] = Point(0, height);
	//objShape[0] = Point(-20, height/2);
	auto physicsBody = PhysicsBody::createPolygon(objShape, OBJ_SHAPE_NUM, PHYSICSBODY_MATERIAL_DEFAULT, Point(width/-2, height/-2));
	

	slashObj->setPhysicsBody(physicsBody);
	//slashObj->addChild(_makeDrawNode(objShape, OBJ_SHAPE_NUM));
	//clipper->setPhysicsBody(physicsBody);

	this->addChild(slashObj);
	//slashObj->addChild(shape);
	//this->addChild(slashObj);
	//slashObj->runAction(RepeatForever::create(RotateBy::create(1.0f, 90.0f)));
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
				if( (targets[i].x-ed.x)*(targets[i].x-st.x)<0)  // intersect with vertical line
				{
					intersectPoints[count_intersect] = Point(targets[i].x, k*targets[i].x+b); 
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
				if( (targets[count-1].x-ed.x)*(targets[count-1].x-st.x)<0)  // intersect with vertical line
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
				if( (ed.x - targets[i].x)*(ed.x - targets[i+1].x)<0)  // intersect with vertical line
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
				if( (ed.x - targets[count-1].x)*(ed.x - targets[count-1].x)<0)  // intersect with vertical line
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

	
	Point st, ed;
	st = slashObj->convertToNodeSpace(this->convertToWorldSpace(this->touchStart));
	ed = slashObj->convertToNodeSpace(this->convertToWorldSpace(this->touchEnd));
	ClippingNode* part1=nullptr;
	ClippingNode* part2=nullptr;

	//slashObj->getPhysicsBody()->getFirstShape()->bodyInfo

	if(_splitSprite(slashObj, st, ed, objShape, OBJ_SHAPE_NUM, &part1, &part2))
	{
		this->addChild(part1);
		this->addChild(part2);
		this->removeChild(slashObj);
	}
}

bool gameLayer::_splitSprite(Sprite* sprite, Point st, Point ed, Point* shape, int count, ClippingNode** part1, ClippingNode** part2)
{
	Point* maskL = nullptr;
	Point* maskR = nullptr;
	int maskLNum=0, maskRNum=0;

	if(cutIntoMask(shape, count, st, ed, &maskL, &maskLNum, &maskR, &maskRNum))
	{
		*part1 = _makeClippingNode(maskL, maskLNum, maskR, maskRNum, sprite);
		*part2 = _makeClippingNode(maskR, maskRNum, maskL, maskLNum, sprite);

		/*this->addChild(ml);
		this->addChild(mr);*/
		return true;
	}else {
		return false;
	}
}

Sprite* gameLayer::_duplicateSprite(Sprite* sprite)
{
	auto duplicate = Sprite::createWithTexture(sprite->getTexture());
	duplicate->setPosition(sprite->getPosition().x - sprite->getContentSize().width/2,
		sprite->getPosition().y - sprite->getContentSize().height/2);
	duplicate->setScale(sprite->getScale());
	duplicate->setAnchorPoint(sprite->getAnchorPoint());

	return duplicate;
}

ClippingNode* gameLayer::_makeClippingNode(Point* mask, int count, Point* physicBody, int p_count, Sprite* content)
{
	auto sprite = _duplicateSprite(content);
	
	
	auto _clipper = ClippingNode::create();
	_clipper->setPosition(sprite->getPosition());
	_clipper->setInverted(true);
	_clipper->setOpacity(0);
	sprite->setPosition(Point::ZERO);
	sprite->setAnchorPoint(Point::ZERO);
	_clipper->addChild(sprite);
	auto shape = _makeDrawNode(mask, count);
	//_clipper->addChild(shape);
	_clipper->setStencil(shape);
	//_clipper->setAnchorPoint(sprite->getAnchorPoint());
	_clipper->setPhysicsBody(PhysicsBody::createPolygon(physicBody, p_count,
														PHYSICSBODY_MATERIAL_DEFAULT));/*,
														Point(sprite->getContentSize().width/-2,
														sprite->getContentSize().height/-2)));*/

	return _clipper;
}


void gameLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
