//
//  onePScene.h
//  qlifetest
//
//  Created by XPX on 13-8-16.
//
//

#ifndef qlifetest_onePScene_h
#define qlifetest_onePScene_h

#include "cocos2d.h"



#include "SimpleAudioEngine.h"

class onePScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene(int imgid);
    void endScene(CCObject* pSender);
    void changeScene(CCObject *pSender);
    CREATE_FUNC(onePScene);
};

#endif
