//
//  CLiving.cpp
//  Fifth
//
//  Created by Didrik Munther on 01/06/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CLiving.h"
#include "NSurface.h"

CLiving::CLiving(sf::IntRect rect, sf::Color color) : CMovable(rect, color) {
    _initValues();
}

CLiving::CLiving(sf::IntRect rect, std::string spriteKey) : CMovable(rect, spriteKey) {
    _initValues();
}

void CLiving::_initValues() {
    _values[ValueTypes::HEALTH]      = _maxValues[ValueTypes::HEALTH] = 100;
    _values[ValueTypes::KEVLAR]      = _maxValues[ValueTypes::KEVLAR] = 100;
    _values[ValueTypes::ENERGY]      = _maxValues[ValueTypes::ENERGY] = 100;
    _values[ValueTypes::STAMINA]     = _maxValues[ValueTypes::STAMINA] = 100;
    _stats [StatTypes::ARMOUR]       = 1;
    _stats [StatTypes::ATTACK_POWER] = 10;
    _stats [StatTypes::ATTACK_SPEED] = 10;

    // temp
    _values[ValueTypes::HEALTH] = 75;
    _values[ValueTypes::KEVLAR] = 50;
}

void CLiving::cLivingRender(CWindow *window, CCamera *camera) {
    
    int floatOverHead = 10;
    int bgWidth = 100;
    int bgHeight = 15;
    int healthWidth = ((float)_values[ValueTypes::HEALTH] / _maxValues[ValueTypes::HEALTH]) * bgWidth;
    int kevlarWidth = ((float)_values[ValueTypes::KEVLAR] / _maxValues[ValueTypes::KEVLAR]) * bgWidth;
    
    if(camera->collision(body.getX() + body.getW() / 2 - bgWidth / 2,
                         body.getY() - bgHeight - floatOverHead,
                         bgWidth,
                         bgHeight)) {
        
        NSurface::renderRect(body.getX() + body.getW() / 2 - bgWidth / 2 - camera->offsetX(),  // Background
                             body.getY() - bgHeight - floatOverHead - camera->offsetY(),
                             bgWidth,
                             bgHeight,
                             *window->getRenderTexture(), 255, 0, 0);
        NSurface::renderRect(body.getX() + body.getW() / 2 - bgWidth / 2 - camera->offsetX(),  // Health
                             body.getY() - bgHeight - floatOverHead - camera->offsetY(),
                             healthWidth,
                             bgHeight,
                             *window->getRenderTexture(), 0, 255, 0);
        NSurface::renderRect(body.getX() + body.getW() / 2 - bgWidth / 2 - camera->offsetX(),  // Kevlar
                             body.getY() - bgHeight - floatOverHead - camera->offsetY() + bgHeight / 2,
                             kevlarWidth,
                             bgHeight / 2,
                             *window->getRenderTexture(), 0, 0, 255);
    }
    
}

void CLiving::cLivingLoop() {
    
}

void CLiving::dealDamage(int amount) {
    int* health = &_values[ValueTypes::HEALTH];
    int* kevlar = &_values[ValueTypes::KEVLAR];
    if(_values[KEVLAR] > 0) {
        *kevlar -= amount;
        if(*kevlar <= 0)
            *kevlar = 0;
    } else {
        *health -= amount;
        if(*health <= 0) {
            *health = 0;
            toRemove = true;
        }
    }
}

void CLiving::heal(int amount) {
    int* health = &_values[ValueTypes::HEALTH];
    *health += amount;
    if(*health >= _maxValues[ValueTypes::HEALTH])
        *health = _maxValues[ValueTypes::HEALTH];
}

