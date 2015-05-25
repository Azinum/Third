//
//  CPlayer.cpp
//  Third
//
//  Created by Didrik Munther on 14/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CPlayer.h"
#include "Define.h"
#include <iostream>

CPlayer::CPlayer(sf::IntRect rect, sf::Color color) :
    CEntity(rect, color) {
        initValues();
}

CPlayer::CPlayer(sf::IntRect rect, std::string spriteKey) :
    CEntity(rect, spriteKey) {
        CPlayer(rect, sf::Color{255, 255, 255, 255});
        initValues();
}

void CPlayer::initValues() {
    maxSpeed = 10.0f;
    accelerationX = 1.5f;
    accelerationY = 100.0f;
    stoppingAccelerationX = accelerationX * 2;
    sneakSpeed = (float)maxSpeed / 2.0f;
    isSneaking = false;
    hasWalkedX = false;
    hasWalkedY = false;
}

void CPlayer::goRight() {
    body.velX += accelerationX;
    if(isSneaking) {
        if(body.velX > sneakSpeed)
            body.velX = sneakSpeed;
    } else {
        if(body.velX > maxSpeed)
            body.velX = maxSpeed;
    }
    
    hasWalkedX = true;
}

void CPlayer::goLeft() {
    body.velX -= accelerationX;
    if(isSneaking) {
        if(body.velX < -sneakSpeed)
            body.velX = -sneakSpeed;
    } else {
        if(body.velX < -maxSpeed)
            body.velX = -maxSpeed;
    }
    hasWalkedX = true;
}

void CPlayer::goUp() {
    if(hasProperty(EntityProperty::FLYING)) {
        body.velY -= accelerationY;
        if(isSneaking) {
            if(body.velY < -sneakSpeed)
                body.velY = -sneakSpeed;
        } else {
            if(body.velY < -maxSpeed)
                body.velY = -maxSpeed;
        }
    } else {
        jump();
    }
    
    hasWalkedY = true;
}

void CPlayer::goDown() {
    if(hasProperty(EntityProperty::FLYING)) {
        body.velY += accelerationY;
        
        if(isSneaking) {
            if(body.velY > sneakSpeed)
                body.velY = sneakSpeed;
        } else {
            if(body.velY > maxSpeed)
                body.velY = maxSpeed;
        }
    }
    
    hasWalkedY = true;
}

void CPlayer::jump() {
    if (!collisionBottom)
        return;
    
    body.velY -= accelerationY;
    if(body.velY < -maxSpeed)
        body.velY = -maxSpeed;
    
}

void CPlayer::_doLogic() {
    if(!hasWalkedX) {
        if(body.velX < 0) {
            body.velX += stoppingAccelerationX;
            if(body.velX >= 0)
                body.velX = 0.0f;
        } else {
            body.velX -= stoppingAccelerationX;
            if(body.velX <= 0)
                body.velX = 0.0f;
        }
    }
    
    if(!hasWalkedY) {
        if(hasProperty(EntityProperty::FLYING)) {
            if(body.velY < 0) {
                body.velY += accelerationY;
                if(body.velY >= 0)
                    body.velY = 0.0f;
            } else {
                body.velY -= accelerationY;
                if(body.velY <= 0)
                    body.velY = 0.0f;
            }
        }
    }
    
    hasWalkedX = false;
    hasWalkedY = false;
}