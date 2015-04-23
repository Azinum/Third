//
//  CChatBubble.cpp
//  Third
//
//  Created by Didrik Munther on 22/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CChatBubble.h"
#include <sstream>
#include "NSurface.h"
#include <SDL2/SDL.h>
#include "Define.h"
#include <iostream>

CChatBubble::CChatBubble(std::string text, CEntity* target, std::string fontKey, CAssetManager* assetManager, int type) :
    target(target), type(type), CGuiText(0, 0, text, fontKey, assetManager), creationTime(SDL_GetTicks()),
    r(0), g(0), b(0), rB(220), gB(220), bB(220) {
    
    switch(type) {
        case ChatBubbleType::SAY:
            r = g = b = 0;        // Black
            break;
        case ChatBubbleType::YELL:
            r = 255;                // Red
            break;
        case ChatBubbleType::WHISPER:
            g = b = 255;            // Cyan
            break;
    }
    
    std::vector<std::string> splittedText;              // All this basically splits the text up so that it becomes several lines instead of a long one
    
    std::stringstream ss(text);
    std::string item;
    const char* delim = " ";
    while (std::getline(ss, item, *delim)) {
        splittedText.push_back(item);
    }
    
    int currentSize = 0;
    std::string currentString = "";
    for(int i = 0; i < splittedText.size(); i++) {
        if(currentSize > 10) {
            TextVector.push_back(CText(currentString, fontKey, assetManager, SDL_Color{(Uint8)r,(Uint8)g,(Uint8)b,255}));
            currentString = "";
            currentSize = 0;
        }
        currentSize += (int)splittedText[i].length();
        currentString += splittedText[i] + " ";
    }
    if(currentSize > 0)                 // For when the loop quits but there is still text that should be added
        TextVector.push_back(CText(currentString, fontKey, assetManager, SDL_Color{(Uint8)r,(Uint8)g,(Uint8)b,255}));
        
    int letterPerSecond = 10;
    livingTime = (int)text.length() / letterPerSecond;
    
}

void CChatBubble::onLoop() {
    if(SDL_GetTicks() > creationTime + livingTime * 1000)
        toRemove = true;
}

void CChatBubble::onRender(SDL_Renderer *renderer, CCamera* camera) {
    
    if(TextVector.size() <= 0)
        return;
    if(TextVector[0].getFont() == nullptr)
        return;
    
    int width, height;
    
    int widestLine = 0;
    int totalHeight = 0;
    auto i = TextVector.begin();
    while(i != TextVector.end()) {
        TTF_SizeText(i->getFont(), i->getText()->c_str(), &width, &height);
        if(width > widestLine)
            widestLine = width;
        totalHeight += height;
        i++;
    }
    
    int margin = 4;
    int floatOverHead = 20;
    
    NSurface::renderRect(target->body.getX() + target->body.getWidth() / 2 - widestLine / 2 - camera->offsetX(),
                         target->body.getY() - camera->offsetY() - totalHeight - floatOverHead,
                         widestLine,
                         totalHeight,
                         renderer, rB, gB, bB);
    
    int currentLine = (int)TextVector.size() - 1;
    i = TextVector.begin();
    while(i != TextVector.end()) {
        TTF_SizeText(i->getFont(), i->getText()->c_str(), &width, &height);                     // x = tX + tW / 2 - w / 2
        int posX = target->body.getX() + target->body.getWidth() / 2 - width / 2 + (int)(margin / 2);
        int posY = target->body.getY() - totalHeight + height * currentLine - floatOverHead;
        if(!camera->collision(posX, posY, width, height + margin * 3)) {
            currentLine--;
            i++;
            continue;
        }
        i++->onRender(posX - camera->offsetX(),
                      posY - camera->offsetY(),
                      renderer);
        currentLine--;
    }
    
}







