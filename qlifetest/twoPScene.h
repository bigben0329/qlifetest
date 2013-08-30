//
//  TwoPScene.h
//  qlifetest
//
//  Created by XPX on 13-8-16.
//
//

#ifndef __qlifetest__TwoPScene__
#define __qlifetest__TwoPScene__

#include "cocos2d.h"



#include "SimpleAudioEngine.h"

class twoPScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene(int imgid);
    void endScene(CCObject* pSender);
    void changeScene(CCObject *pSender);
    CREATE_FUNC(twoPScene);
};

#endif
