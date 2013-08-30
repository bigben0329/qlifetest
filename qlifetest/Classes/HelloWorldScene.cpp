#include "HelloWorldScene.h"
#include "onePScene.h"
#include "ImageAdapter.h"
#include "SimpleAudioEngine.h"
#include "string"
#include "cstdlib"
#include "ctime"
using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

int imgid ;

CCScene* HelloWorld::scene(int idx)
{
    imgid = idx ;
    srand((int)time(NULL));
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


void HelloWorld::endScene(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    SimpleAudioEngine::sharedEngine()->end();
}

void HelloWorld::changeScene(CCObject* pSender)
{
        //CCTransitionPageTurn *trans = CCTransitionPageTurn::create(1, onePScene::scene(imgid+1), false );
    CCTransitionMoveInT *trans = CCTransitionMoveInT::create(1, onePScene::scene(imgid+1));
    CCDirector::sharedDirector()->replaceScene(trans);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    CCSize frameSize = pEGLView->getFrameSize();
    int fw = frameSize.width , fh = frameSize.height ;
    
    //效果3,需要包含4种Scene,4种切换效果
    
    char imgname[50] ;
    sprintf(imgname, "%d.png", imgid ) ;
    
    CCSprite *sp = CCSprite::create(imgname);
    sp->setScale( ImageAdapter::adapterFullBackGround(sp->getContentSize(), frameSize ));
    sp->setPosition(ccp(fw/2,fh/2));
    
    CCActionInterval *act1 = CCScaleBy::create(2.0, 1.1);
    CCCallFuncN *cfn = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::changeScene));
    CCSequence *act = CCSequence::create(act1,cfn,NULL);
    sp->runAction(act);
    
    this->addChild(sp);
    
        //最简单的效果
//    CCSprite *sp1 = CCSprite::create(pnow);
//    sp1->setScale(adaptionScaleAuto(sp1->getContentSize()));
//    sp1->setPosition(ccp(fw/2,fh/2));
//    this->addChild(sp1,1);
//    
//    
//    if ( pcount != 10 )
//    {
//        CCCallFuncN *nexts = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::nextScene));
//        CCSequence *csq = CCSequence::create(CCDelayTime::create(3.0),nexts,NULL);
//        sp1->runAction(csq);
//    }else
//    {
//        sp1->runAction(CCSequence::create( CCDelayTime::create(3.0) , CCFadeOut::create(0.7f) , NULL ));
//    }
        //效果2
        //    CCSprite *bgi = CCSprite::create("bgi.jpg");
        //    bgi->setScale(fw*2.0/bgi->getContentSize().width);
        //    bgi->setPosition(ccp((pcount-1)*48, bgi->getContentSize().height/2-fh/2));
        //    this->addChild(bgi,0);
        //    CCActionInterval *bgiact = CCMoveBy::create(4, ccp(48, 0));
        //    bgi->runAction(CCRepeatForever::create(bgiact));
//    int t = 0 ;
//    CCSprite *sp[10] ;
//    CCSequence *act[10] ;
//    for ( int i = 0 ; i < 10 ; i ++ )
//    {
//        sprintf(pnow, "%d.jpg",i);
//        sp[i] = CCSprite::create(pnow);
//        
//        sp[i]->setScale(adaptionScaleAuto(sp[i]->getContentSize()));
//        
//        
//        int x = rand()%(int)(fw - sp[i]->getContentSize().width) + sp[i]->getContentSize().width/2 ;
//        int y = rand()%(int)(fh - sp[i]->getContentSize().height) + sp[i]->getContentSize().height/2 ;
//        sp[i]->setPosition(ccp(x,y));
//        sp[i]->setRotation(rand()%30-14) ;
//        sp[i]->setVisible(false);
//        this->addChild(sp[i]);
//        CCActionInterval *act1 = CCRotateBy::create(4, sp[i]->getRotation()<0?15:-15);
//        CCActionInterval *act2 = CCMoveBy::create(4, ccp(x<fw/2?rand()%(fw/3):-rand()%(fw/3), y<fh/2?rand()%(fh/3):-rand()%(fh/3)));
//        CCActionInterval *act3 = CCFadeOut::create(2);
//        CCAction *act4 = CCShow::create();
//        CCSpawn *spw = CCSpawn::create(act1,act2,CCSequence::create(CCDelayTime::create(2),act3,NULL),NULL);
//        if ( i == 9 )
//        {
//            CCCallFuncN *nexts = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::endScene));
//            act[i] = CCSequence::create(CCDelayTime::create(t),act4, spw, nexts,NULL);
//        }else
//        {
//            act[i] = CCSequence::create(CCDelayTime::create(t),act4, spw,NULL);
//        }
//        t += 4 ;
//    }
//    for ( int i = 0 ; i < 10 ; i ++ ) sp[i]->runAction(act[i]);
    
    
    
    return true;
}


