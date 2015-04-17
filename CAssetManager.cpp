//
//  CAssetManager.cpp
//  Third
//
//  Created by Didrik Munther on 17/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CAssetManager.h"
#include <iostream>
#include "NFile.h"

CAssetManager::CAssetManager() {
}


CSprite* CAssetManager::addSprite(std::string name, std::string spriteSheetKey, SDL_Rect source) {
    if(SpriteVector.find(name) != SpriteVector.end()) {
        std::cout << "w: Couldn't add sprite: \"" << name << "\", because it already exists.\n";
        return SpriteVector[name];
    } else if(SpriteSheetVector.find(spriteSheetKey) == SpriteSheetVector.end()) {
        std::cout << "w: Couldn't add sprite: \"" << name << "\", because the spritesheet \"" << spriteSheetKey << "\" didn't exist.\n";
        return nullptr;     // Replace with null texture
    } else {
        SpriteVector[name] = new CSprite(SpriteSheetVector[spriteSheetKey], source);
        return SpriteVector[name];
    }
}

CSpriteSheet* CAssetManager::addSpriteSheet(std::string name, std::string fileName, SDL_Renderer* renderer) {
    if(SpriteSheetVector.find(name) != SpriteSheetVector.end()) {
        std::cout << "w: Couldn't add spritesheet: \"" << name << "\", because it already exists.\n";
        return SpriteSheetVector[name];
    } else {
        CSpriteSheet* temp = new CSpriteSheet(renderer, fileName);
        if(temp->getTexture() == nullptr) {
            std::cout << "w: Couldn't add spritesheet: \"" << name << "\", could not open file \"" << fileName << "\".\n";
            return nullptr;
        } else {
            SpriteSheetVector[name] = temp;
            return SpriteSheetVector[name];
        }
    }
}

CSprite* CAssetManager::getSprite(std::string key) {
    auto it = SpriteVector.find(key);
    if(it == SpriteVector.end())
        return nullptr;
    else
        return it->second;
}

CSpriteSheet* CAssetManager::getSpriteSheet(std::string key) {
    auto it = SpriteSheetVector.find(key);
    if(it == SpriteSheetVector.end())
        return nullptr;
    else
        return it->second;
}

void CAssetManager::onCleanup() {
    {
        auto i = SpriteVector.begin();
        while(i != SpriteVector.end()) {
            delete i->second;
            SpriteVector.erase(i++->first);
        }
        SpriteVector.clear();
    }
    
    {
        auto i = SpriteSheetVector.begin();
        while(i != SpriteSheetVector.end()) {
            i->second->onCleanup();
            delete i->second;
            SpriteSheetVector.erase(i++->first);
        }
        SpriteSheetVector.clear();
    }
    
}