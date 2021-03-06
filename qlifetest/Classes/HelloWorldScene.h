#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"



#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene(int imgid);
    void endScene(CCObject* pSender);
    void changeScene(CCObject *pSender);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
