//
//  ImageAdapter.cpp
//  qlifetest
//
//  Created by XPX on 13-8-16.
//
//

#include "ImageAdapter.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;

double ImageAdapter::adapterFullBackGround(cocos2d::CCSize img,cocos2d::CCSize bgi)
{
    int iw = img.width , ih = img.height ;
    int bw = bgi.width , bh = bgi.height ;
    if ( iw * bh > ih * bw ) //比背景更宽
    {
        return bh * 1.0 / ih ; //让高度一致,牺牲部分图片
    }else
    {
        return bw * 1.0 / iw ;
    }
}
double ImageAdapter::adapterBackGround(cocos2d::CCSize img,cocos2d::CCSize bgi)
{
    int iw = img.width , ih = img.height ;
    int bw = bgi.width , bh = bgi.height ;
    if ( iw * bh < ih * bw )
    {
        return bh * 1.0 / ih ;
    }else
    {
        return bw * 1.0 / iw ;
    }
}