//
//  threePScene.h
//  qlifetest
//
//  Created by XPX on 13-8-16.
//
//

#ifndef __qlifetest__threePScene__
#define __qlifetest__threePScene__
#include "cocos2d.h"



#include "SimpleAudioEngine.h"

class threePScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene(int imgid);
    void endScene(CCObject* pSender);
    void changeScene(CCObject *pSender);
    CREATE_FUNC(threePScene);
};
#endif /* defined(__qlifetest__threePScene__) */
