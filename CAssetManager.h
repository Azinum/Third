//
//  CAssetManager.h
//  Third
//
//  Created by Didrik Munther on 17/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __Third__CAssetManager__
#define __Third__CAssetManager__

#include <stdio.h>
#include "CSpriteSheet.h"
#include <SFML/Graphics.hpp>
#include "CSprite.h"
#include <map>
#include <string>

class CAssetManager {
    
public:
    CAssetManager();
    
    CSprite* addSprite(std::string name, std::string spriteSheetKey, sf::IntRect source);
    CSpriteSheet* addSpriteSheet(std::string name, std::string fileName);
    sf::Font* addFont(std::string name, std::string fileName);
    sf::Shader* addShader(std::string name, std::string fileName, sf::Shader::Type type);
    
    CSprite* getSprite(std::string key);
    CSpriteSheet* getSpriteSheet(std::string key);
    sf::Font* getFont(std::string key);
    sf::Shader* getShader(std::string key);
    
    void onCleanup();
    
private:
    std::map<std::string, CSprite*> _SpriteVector;
    std::map<std::string, CSpriteSheet*> _SpriteSheetVector;
    std::map<std::string, sf::Font> _FontVector;
    std::map<std::string, sf::Shader*> _ShaderVector;
    
};

#endif /* defined(__Third__CAssetManager__) */
