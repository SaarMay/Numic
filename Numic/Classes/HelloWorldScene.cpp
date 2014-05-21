#include "HelloWorldScene.h"
#define COCOS2D_DEBUG 1
USING_NS_CC;

enum{
	leftPart = 10,
	rightPart = 11
};

static int cuttedState = 0;

Scene* HelloWorld::createScene()
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


	auto scene = Scene::createWithPhysics();

    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = HelloWorld::create();

    layer->setPhyWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	
    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
	


	// My Code Starts here

	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody); this->addChild(edgeSp); edgeSp->setTag(0);
	
	auto s = Director::getInstance()->getWinSize();
	slashObj = Sprite::create("remio.png");
	
	slashObj->setAnchorPoint(Point(0.5,0.5));
	slashObj->setPosition( Point(s.width / 2, s.height / 2) );
	slashObj->setScale(0.5);
	//slashObj->setRotation(90);

	float width = slashObj->getContentSize().width;
	float height = slashObj->getContentSize().height;
	objShape[4] = Point(width/-2, height/-2);
    objShape[3] = Point(width/2, height/-2);
    objShape[2] = Point(width/2, height/2);
	objShape[1] = Point(width/-2, height/2);
	objShape[0] = Point(-20+width/-2, 0);
	//auto physicsBody = PhysicsBody::createPolygon(objShape, OBJ_SHAPE_NUM, PHYSICSBODY_MATERIAL_DEFAULT);
	

	//slashObj->setPhysicsBody(physicsBody);

	this->addChild(slashObj);
    return true;
}

bool HelloWorld::_getIntersect(Point st, Point ed, float k, float b, float tmp_k, float tmp_b, float* x, float* y)
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
bool HelloWorld::cutIntoMask(Point* targets, int count, Point st, Point ed, Point** maskLPts, int* maskLNum, Point** maskRPts, int* maskRNum)
{
	float tmp_k, tmp_b;
	float k, b; // 直线的斜率 截距
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

DrawNode* HelloWorld::_makeDrawNode(Point* points, int count)
{
	auto shape = DrawNode::create();
	static Color4F green(0, 1, 0, 1);
    shape->setAnchorPoint(Point(0.5,0.5));
	shape->drawPolygon(points, count, green, 0, green);

	return shape;
}

bool HelloWorld::_calcLineEquation(Point st, Point ed, float* k, float* b)
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

void HelloWorld::onEnter()
{
	Layer::onEnter();

	// Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	if (cuttedState == 2)
	{
		this->removeChildByTag(leftPart);
		this->removeChildByTag(rightPart);
		auto s = Director::getInstance()->getWinSize();
		slashObj = Sprite::create("remio.png");
		slashObj->setAnchorPoint(Point(0.5, 0.5));
		slashObj->setPosition(Point(s.width / 2, s.height / 2));
		slashObj->setScale(0.5);
		this->addChild(slashObj);
		cuttedState = 0;
		return false;
	}
	else if (cuttedState == 0)
	{
		CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);

		/*if (_state != kPaddleStateUngrabbed) return false;
		if ( !containsTouchLocation(touch) ) return false;

		_state = kPaddleStateGrabbed;*/

		this->touchStart = touch->getLocation();
		cuttedState++;
		CCLOG("return true");
		return true;
	}
	else return false;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get Sets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	CCLOG("Paddle::onTouchEnd id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
	this->touchEnd = touch->getLocation();

	
	Point st, ed;
	st = slashObj->convertToNodeSpaceAR(this->convertToWorldSpace(this->touchStart));
	ed = slashObj->convertToNodeSpaceAR(this->convertToWorldSpace(this->touchEnd));
	ClippingNode* part1=nullptr;
	ClippingNode* part2=nullptr;

	if(_splitSprite(slashObj, st, ed, objShape, OBJ_SHAPE_NUM, &part1, &part2)) //cut into 2 parts
	{
		this->addChild(part1,1,leftPart);
		this->addChild(part2,1,rightPart);       //add 2 new parts
		this->removeChild(slashObj); // remove old
	}
    
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
bool HelloWorld::_splitSprite(Sprite* sprite, Point st, Point ed, Point* shape, int count, ClippingNode** part1, ClippingNode** part2)
{
	Point* maskL = nullptr;
	Point* maskR = nullptr;
	int maskLNum=0, maskRNum=0;

	if(cutIntoMask(shape, count, st, ed, &maskL, &maskLNum, &maskR, &maskRNum)) // cut into  2 masks
	{
		*part1 = _makeClippingNode(maskL, maskLNum, maskR, maskRNum, sprite);
		Size winSize = Director::getInstance()->getWinSize();
		auto* jumptoL = CCJumpTo::create(1, Point(winSize.width*4/5,-shape[2].y), 70, 1);
		(*part1)->runAction(jumptoL);
		*part2 = _makeClippingNode(maskR, maskRNum, maskL, maskLNum, sprite);
		CCActionInterval* jumptoR = CCJumpTo::create(1, Point(winSize.width / 5, -shape[2].y), 70, 1);
		(*part2)->runAction(jumptoR);

		this->scheduleOnce(schedule_selector(HelloWorld::OnceAgain), 2.0f);
		//calculate Area
		//(*part1)->getPhysicsBody()->getFirstShape()->getArea();
		//(*part2)->getPhysicsBody()->getFirstShape()->getArea();

		return true;
	}else {
		return false;
	}
}

Sprite* HelloWorld::_duplicateSprite(Sprite* sprite)
{
	auto duplicate = Sprite::createWithTexture(sprite->getTexture());
	duplicate->setPosition(sprite->getPosition());
	duplicate->setScale(sprite->getScale());
	duplicate->setAnchorPoint(sprite->getAnchorPoint());

	return duplicate;
}

ClippingNode* HelloWorld::_makeClippingNode(Point* mask, int count, Point* physicBody, int p_count, Sprite* content)
{
	auto sprite = _duplicateSprite(content);	//复制精灵
	
	
	auto _clipper = ClippingNode::create();
	_clipper->setPosition(content->getPosition());
	_clipper->setInverted(true);// //显示切割后剩余部分
	_clipper->setOpacity(0);	//设置透明度
	_clipper->setAnchorPoint(Point::ZERO); //设置定位点，显示图层  参考http://www.cnblogs.com/pengyingh/articles/2433081.html
	_clipper->addChild(sprite);
	auto shape = _makeDrawNode(mask, count);	//这里画形状
	_clipper->addChild(shape);	//然后将这形状模板加到遮罩类子类里，这步可能只是用来保存遮罩形状，以免以后用到吧
	_clipper->setStencil(shape);//创建裁剪模板  参考 http://www.gulumiao.com/blog/2013/11/%E5%85%B3%E4%BA%8Ecocos2dx%E9%81%AE%E7%BD%A9ccclippingnode/
	
	//_clipper->setPhysicsBody(PhysicsBody::createPolygon(physicBody, p_count,
	//													PHYSICSBODY_MATERIAL_DEFAULT));
	sprite->setPosition(Point::ZERO);

	return _clipper;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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


void HelloWorld::OnceAgain(float dt)
{
	cuttedState++;
}