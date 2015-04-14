//
//  CParticle.h
//  Third
//
//  Created by Didrik Munther on 19/03/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __Third__CParticle__
#define __Third__CParticle__

#include <stdio.h>
#include "CEntity.h"

class CParticle : public CEntity {
    
public:
    CParticle(SDL_Rect rect, SDL_Color color);
    CParticle(SDL_Rect rect, SDL_Color color, int livingTime);
private:
    SDL_Color color;
    int creationTime;
    int livingTime;
    
    virtual void doLogic();
};


#endif /* defined(__Third__CParticle__) */
