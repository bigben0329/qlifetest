//
//  onePScene.cpp
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

int oneimgid ;

CCScene* onePScene::scene(int idx)
{
    oneimgid = idx ;
    srand((int)time(NULL));
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    onePScene *layer = onePScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    return scene;
}

bool onePScene::init()
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
    snprintf(imgname, sizeof(imgname), "%d.jpg", oneimgid ) ;
    
    CCSprite *sp = CCSprite::create(imgname);
    sp->setPosition(ccp(fw/2,fh/2));
    int sw = sp->getContentSize().width;
    int sh = sp->getContentSize().height;
    
    double scaleRate = ImageAdapter::adapterFullBackGround(sp->getContentSize(), frameSize);
    sp->setScale( scaleRate );
    sw *= scaleRate ;
    sh *= scaleRate ;
    
    CCActionInterval *act1 ;
    if ( sw - fw >= 10 )
    {
        //往右走
        int sx = fw - sw/2 ;
        int sy = fh / 2 ;
        int tx = min(sw/2,sx+15) ;
        int ty = sy ;
        sp->setPosition( ccp( sx, sy ) ) ;
        
        act1 = CCMoveTo::create(3, ccp(tx,ty));
    }else if ( sh - fh >= 10 )
    {
            //往上走
        int sx = sw / 2 ;
        int sy = fh - sh / 2 ;
        int tx = sx ;
        int ty = min(sh / 2,sy + 15) ;
        
        sp->setPosition(ccp(sx,sy)) ;
        act1 = CCMoveTo::create(3,ccp(tx,ty));
        
    }else
    {
        sp->setPosition(ccp(fw/2,fh/2));
        act1 = CCScaleTo::create(3, 1.08);
    }
    
    CCSequence *act ;
    CCCallFuncN *cfn = CCCallFuncN::create(this, callfuncN_selector(onePScene::changeScene));
    
    if ( oneimgid != 21 )
        cfn = CCCallFuncN::create(this, callfuncN_selector(onePScene::changeScene));
    else
        cfn = CCCallFuncN::create(this, callfuncN_selector(onePScene::endScene));
    
    if ( oneimgid != 21 )
        act = CCSequence::create(act1,cfn,NULL);
    else
        act = CCSequence::create(act1,CCFadeOut::create(1.5f),cfn,NULL);
    
    sp->runAction(act);
    this->addChild(sp);
    
    return true;
}


void onePScene::endScene(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    SimpleAudioEngine::sharedEngine()->end();
}
void onePScene::changeScene(CCObject *pSender)
{
    int whichscene = rand()%100 + 1 ;
    CCScene *sc ;
    CCTransitionScene *trans ;
    if ( whichscene <= 20 )
    {
        sc = onePScene::scene(oneimgid+1) ;
        trans = CCTransitionSlideInB::create(1, sc);
    }else if ( whichscene <= 30 )
    {
        sc = twoPScene::scene(oneimgid+1) ;
        trans = CCTransitionMoveInR::create(1, sc) ;
    }else
    {
        sc = threePScene::scene(oneimgid+1);
        trans = CCTransitionPageTurn::create(1, sc, false);
    }
    
    //CCTransitionPageTurn *trans = CCTransitionPageTurn::create(0.5, threePScene::scene(oneimgid+1), false);
    CCDirector::sharedDirector()->replaceScene(trans);
}