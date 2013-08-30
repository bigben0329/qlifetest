//
//  TwoPScene.cpp
//  qlifetest
//
//  Created by XPX on 13-8-16.
//
//
#include "onePScene.h"
#include "twoPScene.h"
#include "threePScene.h"
#include "ImageAdapter.h"
#include "SimpleAudioEngine.h"
#include "iostream"
using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

int twoimgid ;

CCScene* twoPScene::scene(int idx)
{
    twoimgid = idx ;
    srand((int)time(NULL));
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    twoPScene *layer = twoPScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    return scene;
}

bool twoPScene::init()
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
    char imgname1[50] , imgname2[50] ;
    snprintf(imgname1, sizeof(imgname1), "/Users/asteroid/Desktop/new/%d.jpg", twoimgid ) ;
    twoimgid ++ ;
    snprintf(imgname2, sizeof(imgname2), "/Users/asteroid/Desktop/new/%d.jpg" , twoimgid ) ;
    
    CCSprite *sp1 = CCSprite::create(imgname1);
    CCActionInterval *act1 ;
    int sw1 = sp1->getContentSize().width ;
    int sh1 = sp1->getContentSize().height ;
    double scaleRate1 = ImageAdapter::adapterFullBackGround(sp1->getContentSize(), frameSize);
    sp1->setScale( scaleRate1 );
    sw1 *= scaleRate1 ; sh1 *= scaleRate1 ;
    
    if ( sw1 - fw >= 10 )
    {
            //往左走
        int sx = fw - sw1/2 ;
        int sy = fh / 2 ;
        int tx = min(sw1/2,sx+15);
        int ty = sy ;
        sp1->setPosition( ccp( sx, sy ) ) ;
        
        act1 = CCMoveTo::create(3, ccp(tx,ty));
    }else if ( sh1 - fh >= 10 )
    {
            //往上走
        int sx = fw / 2 ;
        int sy = fh - sh1 / 2 ;
        int tx = sx ;
        int ty = min(sh1 / 2 , sy + 15 );
        sp1->setPosition(ccp(sx,sy)) ;
        act1 = CCMoveTo::create(3,ccp(tx,ty));
        
    }else
    {
        sp1->setPosition(ccp(fw/2,fh/2));
        act1 = CCScaleTo::create(3, 1.08);
    }
    
    sp1->runAction(act1) ;
    this->addChild(sp1,0) ;
    
    int animType = rand() % 2 ;
    CCSprite *sp2 = CCSprite::create(imgname2);
    CCActionInterval *act , *act2 , *act3 ;
    int sw2 = sp2->getContentSize().width ;
    int sh2 = sp2->getContentSize().height ;
    
    if ( animType == 0 )
    {
        CCSize fsize ;
        fsize.setSize( fw-120, fh+20 );
        double scaleRate2 = ImageAdapter::adapterFullBackGround(sp2->getContentSize(), fsize);
        sp2->setScale( scaleRate2 );
        sw2 *= scaleRate2 ; sh2 *= scaleRate2;
        
        sp2->setPosition(ccp(fw+sw2/2,fh-sh2/2));
        act2 = CCMoveTo::create(0.5 , ccp(max(fw-sw2,120+sw2/2),fh-sh2/2) );
        act3 = CCMoveTo::create(2, ccp(max(fw-sw2,120+sw2/2), sh2/2 ) );
    }else 
    {
        CCSize fsize ;
        fsize.setSize(fw/2, fh+20);
        double scaleRate2 = ImageAdapter::adapterFullBackGround(sp2->getContentSize(), fsize);
        sp2->setScale(scaleRate2);
        sw2 *= scaleRate2 ; sh2 *= scaleRate2 ;
        
        sp2->setPosition(ccp(fw+sw2/2,fh-sh2/2));
        act2 = CCMoveTo::create(0.5, ccp(max(fw-sw2,fw/2+sw2/2),fh-sh2/2) );
        act3 = CCMoveTo::create(2, ccp(max(fw-sw2, fw/2+sw2/2),sh2/2));
    }
    
    
    CCCallFuncN *cfn ;
    if ( twoimgid != 21 )
        cfn = CCCallFuncN::create(this, callfuncN_selector(twoPScene::changeScene));
    else
        cfn = CCCallFuncN::create(this, callfuncN_selector(twoPScene::endScene));
    
    if ( twoimgid != 21 )
        act = CCSequence::create(CCHide::create(),CCDelayTime::create(0.5),CCShow::create(),act2,act3,cfn,NULL);
    else
        act = CCSequence::create(CCHide::create(),CCDelayTime::create(0.5),CCShow::create(),act2,act3,CCFadeOut::create(1.5f),cfn,NULL);
    
    sp2->runAction(act);
    this->addChild(sp2,1);
    
    return true;
}

void twoPScene::changeScene(CCObject *pSender)
{
    int whichscene = rand()%100 + 1 ;
    CCScene *sc ;
    CCTransitionScene *trans ;
    if ( whichscene <= 20 )
    {
        sc = onePScene::scene(twoimgid+1) ;
        trans = CCTransitionSlideInB::create(1, sc);
    }else if ( whichscene <= 30 )
    {
        sc = twoPScene::scene(twoimgid+1) ;
        trans = CCTransitionMoveInR::create(1, sc) ;
    }else
    {
        sc = threePScene::scene(twoimgid+1);
        trans = CCTransitionPageTurn::create(1, sc, false);
    }
    
    //CCTransitionPageTurn *trans = CCTransitionPageTurn::create(0.5, threePScene::scene(threeimgid+1), false);
    CCDirector::sharedDirector()->replaceScene(trans);
}

void twoPScene::endScene(CCObject *pSender)
{
    CCDirector::sharedDirector()->end();
    SimpleAudioEngine::sharedEngine()->end();
}