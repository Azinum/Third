//
//  CGuiText.h
//  Third
//
//  Created by Didrik Munther on 22/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __Third__CGuiText__
#define __Third__CGuiText__

#include <stdio.h>
#include "CCamera.h"
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

class CGuiText {
public:
    CGuiText(int x, int y, std::string text, std::string fontKey, CAssetManager* assetManager);
    
    virtual void onLoop();                                          // Pure virtual
    virtual void onRender(SDL_Renderer *renderer, CCamera* camera); //
    
    bool toRemove;
    
protected:
    std::string fontKey;
    CAssetManager* assetManager;
    std::string text;
    int x, y;
};

#endif /* defined(__Third__CGuiText__) */
