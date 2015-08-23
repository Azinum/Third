//
//  CCamera.cpp
//  Third
//
//  Created by Didrik Munther on 02/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CCamera.h"
#include <iostream>
#include "Define.h"
#include <math.h>
#include "CEntity.h"

CCamera::CCamera() :
_offset{0, 0, 0, 0}, cameraSway(10), _noTarget(true) {
}

void CCamera::onInit(CWindow* window) {
    _offset = {0, 0, window->getWidth(), window->getHeight()};
    _cameraShake = 0.0;
}

void CCamera::onLoop() {
    if (!_target)
        _noTarget = true;
    if(_noTarget)
        return;
    
    _cameraShakeStep += 1;
    
    float cameraShakeX = floor(sin(_cameraShakeStep * _cameraShakeStep / 2) * _cameraShake);
    float cameraShakeY = floor(cos(_cameraShakeStep * _cameraShakeStep / 2) * _cameraShake);
    
    _offset.x += (((_target->body.getX() + _target->body.getW() / 2) - _offset.w / 2) - _offset.x + cameraShakeX) / cameraSway;
    _offset.y += (((_target->body.getY() + _target->body.getH() / 2) - _offset.h / 2) - _offset.y + cameraShakeY) / cameraSway;
    
    if(_cameraShake > 0)
        _cameraShake -= ceil(1.0 * (_cameraShake / 70));
        //_cameraShake -= 1.0; // Looks better for some reason...
}

int CCamera::offsetX() {
    return (int)floor(_offset.x);
}

int CCamera::offsetY() {
    return (int)floor(_offset.y);
}

void CCamera::addCameraShake(float cameraShake) {
    _cameraShake += cameraShake;
}

void CCamera::setTarget(CEntity* target) {
    if(target) {
        this->_target = target;
        _noTarget = false;
    } else
        _noTarget = true;
}

bool CCamera::collision(CEntity* entity) {
    if(offsetX() > entity->body.getX() + entity->body.getW())
        return false;
    if(offsetX() + _offset.w < entity->body.getX())
        return false;
    if(offsetY() > entity->body.getY() + entity->body.getH())
        return false;
    if(offsetY() + _offset.h < entity->body.getY())
        return false;
    else
        return true;
}

bool CCamera::collision(int x, int y, int w, int h) {
    if(offsetX() > x + w)
        return false;
    if(offsetX() + _offset.w < x)
        return false;
    if(offsetY() > y + h)
        return false;
    if(offsetY() + _offset.h < y)
        return false;
    else
        return true;
}