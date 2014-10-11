//
//  WebSprite.cpp
//  ClashOfClouds
//
//  Created by Richie Yan on 10/11/14.
//
//

#include "WebSprite.h"
#include "md5.h"

std::string WebSprite::COMPLETED = "completed";

bool WebSprite::initWithUrl(const std::string &url){
    USING_NS_CC;
    
    if(!Node::init()) return false;
    _url = url;
    
    MD5 md5(url);
    _key = md5.md5();
    auto fileUtils = FileUtils::getInstance();
    
    _path = fileUtils->getWritablePath() + "websprite_" +_key;
    
    if(fileUtils->isFileExist(_path)){
        _content = Sprite::create(_path);
        _content->setAnchorPoint(Vec2(0,0));
        addChild(_content);
        _eventDispatcher->dispatchCustomEvent(COMPLETED,this);
    }else{
        load(url);
    }
    return true;
}

void WebSprite::load(const std::string &url){
    USING_NS_CC;
    using namespace network;
    auto textureCache = Director::getInstance()->getTextureCache();
    HttpRequest* request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setUrl(url.c_str());
    request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
        if(response->isSucceed()){
            std::vector<char> *buffer = response->getResponseData();
            std::shared_ptr<Image> image(new Image);
            image->initWithImageData((unsigned char*)buffer->data(),buffer->size());
            textureCache->addImage(image.get(),_url);
            image->saveToFile(_path);
            _content = Sprite::createWithTexture(textureCache->getTextureForKey(_url));
            _content->setAnchorPoint(Vec2(0,0));
            addChild(_content);
            this->setContentSize(_content->getContentSize());
            _eventDispatcher->dispatchCustomEvent(COMPLETED,this);
        }
    });
    
    HttpClient::getInstance()->send(request);
}
