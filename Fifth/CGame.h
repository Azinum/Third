//
//  CGame.h
//  Third
//
//  Created by Didrik Munther on 12/03/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __Third__CGame__
#define __Third__CGame__

#include <stdio.h>
#include <sstream>
#include <string>
#include "CInstance.h"
#include "CChatBubble.h"
#include "CNetwork.h"
#include <SDL2/SDL.h>

class CGame {
    
    friend class CNetwork;
    
public:
    
    CGame();
    ~CGame();
    
    int onExecute();
    
private:
    
    // Main functions
    int _onInit();
    void _initRelativePaths();
    void _onEvent();
    void _handleKeyStates();
    void _onLoop();
    void _onRender();
    int _onCleanup();
    
    // Main variables
    bool _isRunning;
    CInstance instance;
    SDL_Event _event;
    
    // Timer variables
    float _lastTime;
    float _timer;
    const float _ns;
    float _delta;
    int _frames;
    int _updates;
    
    // Misc variables
    std::stringstream _title;
    std::string _intro;
    bool isFocused;
    
};

#endif /* defined(__Third__CGame__) */