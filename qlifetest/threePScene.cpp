    //
    //  threePScene.cpp
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

int threeimgid ;

CCScene* threePScene::scene(int idx)
{
    threeimgid = idx ;
    srand((int)time(NULL));
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    threePScene *layer = threePScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    return scene;
}

bool threePScene::init()
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
    char imgname1[50] , imgname2[50] , imgname3[50] ;
    snprintf(imgname1, sizeof(imgname1), "/Users/liuyou/Desktop/new/%d.jpg", threeimgid ) ;
    threeimgid ++ ;
    snprintf(imgname2, sizeof(imgname2), "/Users/liuyou/Desktop/new/%d.jpg" , threeimgid ) ;
    threeimgid ++ ;
    snprintf(imgname3, sizeof(imgname3), "/Users/liuyou/Desktop/new/%d.jpg",threeimgid);
    
    int aniType = rand()%2 ;
    
    CCSprite *sp1 , *sp2 , *sp3 ;
    CCActionInterval *act1 , *act2 , *act3 , *act4 , *act5 , *act ;
    sp1 = CCSprite::create(imgname1);
    sp2 = CCSprite::create(imgname2);
    sp3 = CCSprite::create(imgname3);
    
    if ( aniType <= 1 )
    {
        //sp1为背景在移动
        int sw1 = sp1->getContentSize().width , sh1 = sp1->getContentSize().height ;
        double scaleRate1 = ImageAdapter::adapterFullBackGround(sp1->getContentSize(), frameSize);
        sp1->setScale( scaleRate1 );
        sw1 *= scaleRate1 ; sh1 *= scaleRate1 ;
        
        if ( sw1 - fw >= 10 )
        {
            //往左走
            int sx = fw - sw1/2 ;
            int sy = fh / 2 ;
            int tx = sw1/2 ;
            if ( sw1 - fw > 20 )
            {
                tx -= 10 ;
            }
            int ty = sy ;
            sp1->setPosition( ccp( sx, sy ) ) ;
            
            act1 = CCMoveTo::create(3, ccp(tx,ty));
        }else if ( sh1 - fh >= 10 )
        {
                //往上走
            int sx = fw / 2 ;
            int sy = fh - sh1 / 2 ;
            int tx = sx ;
            int ty = sh1 / 2 ;
            if ( sh1 - fh > 20 )
            {
                ty -= 10 ;
            }
            sp1->setPosition(ccp(sx,sy)) ;
            act1 = CCMoveTo::create(3,ccp(tx,ty));
            
        }else
        {
            sp1->setPosition(ccp(fw/2,fh/2));
            act1 = CCScaleTo::create(3, 1.1);
        }
        
        //sp2从最左边fw/3 从下往上
        int sw2 = sp2->getContentSize().width , sh2 = sp2->getContentSize().height ;
        double scrx2 = ((double)fw/3.0)/sp2->getContentSize().width;
        double scry2 ;
        if ( sp2->getContentSize().height * scrx2 >= fh + 20.0 ) scry2 = scrx2 ;
        else scry2 = ( (double)fh + 20.0 ) / sp2->getContentSize().height ;
        sp2->setScaleX(scrx2) ; sp2->setScaleY(scry2);
        sw2 *= scrx2 ; sh2 *= scry2 ;
        
        int sx2 = sw2 / 2 , sy2 = -sh2 / 2 ;
        int tx2 = sw2 / 2 , ty2 = fh - sh2/2 ;
        sp2->setPosition(ccp(sx2,sy2));
        act2 = CCMoveTo::create(0.5, ccp(tx2,ty2));
        ty2 = sh2 / 2 ;
        act3 = CCMoveTo::create(2.5,ccp(tx2,ty2));
        
        
        //sp3从中间fw3 从上往下
        int sw3 = sp3->getContentSize().width , sh3 = sp3->getContentSize().height ;
        double scrx3 = (fw/3.0) / sp3->getContentSize().width ;
        double scry3 ;
        if ( sp3->getContentSize().height * scrx3 >= fh + 20 ) scry3 = scrx3 ;
        else scry3 = ( fh + 20 ) / sp3->getContentSize().height ;
        sp3->setScaleX(scrx3) ; sp3->setScaleY(scry3);
        sw3 *= scrx3 ; sh3 *= scry3;
        
        int sx3 = fw/3 + sw3 / 2 , sy3 = fh + sh3 / 2 ;
        int tx3 = fw/3 + sw3 / 2 , ty3 = sh3 / 2;
        sp3->setPosition(ccp(sx3,sy3));
        act4 = CCMoveTo::create(0.5,ccp(tx3,ty3));
        ty3 =  fh - sh3/2;
        act5 = CCMoveTo::create(2.5, ccp(tx3, ty3));
    }else
    {
        
    }
    
    this->addChild(sp1,0);
    this->addChild(sp2,1);
    this->addChild(sp3,2);
    
    CCCallFuncN *cfn = CCCallFuncN::create(this, callfuncN_selector(threePScene::changeScene));
    sp1->runAction(act1);
    sp2->runAction(CCSequence::create(act2,act3,NULL));
    sp3->runAction(CCSequence::create(act4,act5,cfn,NULL));
    return true;
}

void threePScene::changeScene(CCObject *pSender)
{
    int whichscene = rand()%100 + 1 ;
    CCScene *sc ;
    CCTransitionScene *trans ;
    if ( whichscene <= 20 )
    {
        sc = onePScene::scene(threeimgid+1) ;
        trans = CCTransitionSlideInB::create(1, sc);
    }else if ( whichscene <= 30 )
    {
        sc = twoPScene::scene(threeimgid+1) ;
        trans = CCTransitionMoveInR::create(1, sc) ;
    }else
    {
        sc = threePScene::scene(threeimgid+1);
        trans = CCTransitionPageTurn::create(1, sc, false);
    }
        //CCTransitionPageTurn *trans = CCTransitionPageTurn::create(0.5, threePScene::scene(threeimgid+1), false);
    CCDirector::sharedDirector()->replaceScene(trans);
}

void threePScene::endScene(CCObject *pSender)
{
    CCDirector::sharedDirector()->end();
    SimpleAudioEngine::sharedEngine()->end();
}