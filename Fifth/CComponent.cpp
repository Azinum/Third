//
//  CComponent.cpp
//  Fifth
//
//  Created by Didrik Munther on 21/09/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CComponent.h"
#include "CEntity.h"
#include "NMouse.h"


CComponent::CComponent(CEntity* parent, CInstance* instance, CLuaScript* script)
    : parent(parent)
    , object(parent, this, script)
    , tempWindow(nullptr)
    , tempCamera(nullptr)
    , tempRenderflags(nullptr)
    , tempInstance(nullptr)
{
    onInit(instance);
}

CComponent::~CComponent() {
    
}

void CComponent::onInit(CInstance* instance) {
    if(!object.hasReference("onInit"))
        return;
    
    tempInstance = instance;
    
    callSimpleFunction("onInit");
    
    tempInstance = nullptr;
}

void CComponent::onEvent(CInstance* instance, int key, bool keyDown) {
    if(!object.hasReference("onEvent"))
        return;
    
    tempInstance = instance;
    
    object.beginCall("onEvent");
    object.pushObject(key);
    object.pushObject((bool)keyDown);
    object.endCall(2, 0);
    
    tempInstance = nullptr;
}

void CComponent::onKeyStates(CInstance* instance, const Uint8* keystates) {
    if(!object.hasReference("onKeyStates"))
        return;
    
    KeyState state{keystates};
    
    tempInstance = instance;
    
    object.beginCall("onKeyStates");
    object.pushObject(state);
    object.endCall(1, 0);
    
    tempInstance = nullptr;
}

void CComponent::onLoop(CInstance* instance) {
    if(!object.hasReference("onLoop"))
        return;
    
    tempInstance = instance;
    tempCamera = instance->camera;
    tempWindow = &instance->window;
    
    
    callSimpleFunction("onLoop");
    
    tempInstance = nullptr;
    tempCamera = nullptr;
    tempWindow = nullptr;
}

void CComponent::onRender(CWindow* window, CCamera* camera, RenderFlags renderFlags) {
    if(!object.hasReference("onRender"))
        return;
    
    tempWindow = window;
    tempCamera = camera;
    tempRenderflags = &renderFlags;
    
    callSimpleFunction("onRender");
    
    tempWindow = nullptr;
    tempCamera = nullptr;
    tempRenderflags = nullptr;
}

void CComponent::onRenderAdditional(CWindow* window, CCamera* camera, RenderFlags renderFlags) {
    if(!object.hasReference("onRenderAdditional"))
        return;
    
    tempWindow = window;
    tempCamera = camera;
    tempRenderflags = &renderFlags;
    
    callSimpleFunction("onRenderAdditional");
    
    tempWindow = nullptr;
    tempCamera = nullptr;
    tempRenderflags = nullptr;
    
}

bool CComponent::onCollision(CEntity* target, CollisionSides* collisionSides) {
    if(!object.hasReference("onCollision"))
        return true;
    
    object.beginCall("onCollision");
    object.pushObject(target);
    object.pushObject(collisionSides);
    object.endCall(2, 1);
    
    if(!lua_isboolean(object.getScript()->getState(), -1))
        return true;
    else
        return lua_toboolean(object.getScript()->getState(), -1);
    
}

void CComponent::onSerialize(rapidjson::Value* value, rapidjson::Document::AllocatorType* alloc) {
    if(!object.hasReference("onSerialize"))
        return;
}

void CComponent::onDeserialize(rapidjson::Value* value) {
    onDeserialize(value->GetString());
}

void CComponent::onDeserialize(std::string value) {
    if(!object.hasReference("onDeserialize"))
        return;
    
    object.beginCall("onDeserialize");
    object.pushObject(value);
    object.endCall(1, 0);
}

void CComponent::callSimpleFunction(std::string function) {
    if(!object.hasReference(function.c_str()))
        return;
    
    object.beginCall(function.c_str());
    object.endCall(0, 0);
}

void CComponent::pushThis() {
    object.pushThisObject();
}

void CComponent::renderRect(int x, int y, int w, int h, int r, int g, int b, int a) {
    if(tempCamera == nullptr || tempWindow == nullptr)
        return;
    
    NSurface::renderRect(x, y, w, h, tempWindow, r, g, b, a);
}

void CComponent::renderLine(int x, int y, int x2, int y2, int r, int g, int b, int a) {
    if(tempCamera == nullptr || tempWindow == nullptr)
        return;
    
    NSurface::renderLine(Line(x, y, x2, y2, Color(r, g, b, a)), tempWindow->getRenderer(), tempCamera);
}

void CComponent::renderText(int x, int y, int size, std::string text, std::string fontKey, int r, int g, int b) {
    if(tempCamera == nullptr || tempWindow == nullptr)
        return;
    
    CText textObj(text, size, fontKey, Color(r, b, g));
    NSurface::renderText(x, y, &textObj, tempWindow);
}

int CComponent::getRelativeMouse(lua_State* L) {
    int x, y;
    if(tempInstance != nullptr) {
        x = NMouse::relativeMouseX(tempInstance->camera);
        y = NMouse::relativeMouseY(tempInstance->camera);
    } else if(tempCamera != nullptr) {
        x = NMouse::relativeMouseX(tempCamera);
        y = NMouse::relativeMouseY(tempCamera);
    } else {
        return 0;
    }
    
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    
    return 2;
}

int CComponent::getMouse(lua_State* L) {
    int x = NMouse::absoluteMouseX();
    int y = NMouse::absoluteMouseY();
    
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);
    
    return 2;
}