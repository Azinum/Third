//
//  CText.cpp
//  Third
//
//  Created by Didrik Munther on 22/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CText.h"
#include "NSurface.h"

CText::CText(std::string text, TTF_Font* font, SDL_Color color, CAssetManager* assetManager) :
    text(text), font(font), color(color), assetManager(assetManager) {
}

void CText::onRender(int x, int y, SDL_Renderer *renderer, CCamera* camera) {
    NSurface::renderText(x - camera->offsetX(), y - camera->offsetY(), this, renderer);
}

TTF_Font* CText::getFont() {
    return font;
}

std::string* CText::getText() {
    return &text;
}

SDL_Color* CText::getColor() {
    return &color;
}