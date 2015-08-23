//
//  CSpriteSheet.cpp
//  Third
//
//  Created by Didrik Munther on 24/03/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CSpriteSheet.h"
#include <SDL2_image/SDL_image.h>

CSpriteSheet::CSpriteSheet() {
}

int CSpriteSheet::openFile(SDL_Renderer* renderer, std::string fileName) {
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    _texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

SDL_Texture* CSpriteSheet::getTexture() {
    return _texture;
}

void CSpriteSheet::onCleanup() {
}