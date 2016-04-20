//
//  Define.cpp
//  Third
//
//  Created by Didrik Munther on 13/03/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//d

#include <stdio.h>
#include <SDL2/SDL.h>


#ifndef __Third__Define__
#define __Third__Define__

const int PACKET_SIZE           = 512;
const char PACKET_START[]       = "{!{STARTPACKET}!}";
const char PACKET_ENDING[]      = "{!{ENDPACKET}!}\0";

const char SERVER_NOT_FULL[]    = "{!{SERVERNOTFULL}!}";
const char SERVER_FULL[]        = "{!{SERVERFULL}!}";

const int SCREEN_WIDTH          = 1280;
const int SCREEN_HEIGHT         = 720;
const int SCREEN_BPP            = 32;

const int GAME_INTERVAL          = 60;

const char LOG_FILE[]           = "debug.log";

struct Box {
    int x, y;
    int w, h;
    
    Box(int x, int y, int w, int h)
    : x(x), y(y), w(w), h(h) {  }
    
    bool operator==(const Box& a) {
        return  x == a.x &&
                y == a.y &&
                w == a.w &&
                h == a.h;
    }
    
    operator SDL_Rect() const { return SDL_Rect{x, y, w, h}; }
};

struct Area {
    int w, h;
};

enum RenderFlags {
    CLEAR = 0,
    COLLISION_BORDERS   = 1 << 0,
    COLLISION_AREA      = 1 << 1,
    COLLISION_GRID      = 1 << 2,
    COLLISION_FULL_AREA = 1 << 3,
    ENTITY_GRID         = 1 << 4,
    ENEMY_TRIANGLE      = 1 << 5,
    TRACE_BULLETS       = 1 << 6,
    RENDER_COMBAT_TEXT  = 1 << 7
};

#endif


