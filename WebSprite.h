//
//  WebSprite.h
//  ClashOfClouds
//
//  Created by Richie Yan on 10/11/14.
//
//

#ifndef __ClashOfClouds__WebSprite__
#define __ClashOfClouds__WebSprite__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include <string>

class WebSprite : public cocos2d::Node {
    
private:
    cocos2d::Sprite* _content;
    std::string _key;
    std::string _url;
    std::string _path;
    
public:
    static std::string COMPLETED;
    bool initWithUrl(const std::string & url);
    
private:
    void load(const std::string & url);
    std::string getOutputFilePath();
};

#endif /* defined(__ClashOfClouds__WebSprite__) */
