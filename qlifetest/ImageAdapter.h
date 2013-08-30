//
//  ImageAdapter.h
//  qlifetest
//
//  Created by XPX on 13-8-16.
//
//

#ifndef __qlifetest__ImageAdapter__
#define __qlifetest__ImageAdapter__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


class ImageAdapter
{
public:
    static double adapterFullBackGround(cocos2d::CCSize img,cocos2d::CCSize bgi);
    static double adapterBackGround(cocos2d::CCSize img,cocos2d::CCSize bgi);
};

#endif /* defined(__qlifetest__ImageAdapter__) */