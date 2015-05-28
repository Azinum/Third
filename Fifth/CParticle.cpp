//
//  CParticle.cpp
//  Third
//
//  Created by Didrik Munther on 19/03/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CParticle.h"
#include "Define.h"

CParticle::CParticle(sf::IntRect rect, sf::Color color) :
    CEntity(rect, color), _color(color), _creationTime(_clock.getElapsedTime().asMilliseconds()), _livingTime(5) {
}

CParticle::CParticle(sf::IntRect rect, sf::Color color, int livingTime) :
    CEntity(rect, color), _color(color), _creationTime(_clock.getElapsedTime().asMilliseconds()), _livingTime(livingTime) {
}

void CParticle::_doLogic() {
    
    if(_clock.getElapsedTime().asMilliseconds() - _creationTime > _livingTime * 1000)
        toRemove = true;
    
    body.velX += rand() % 3 - 1;
    //body.velY += rand() % 3 - 1;
    
    if(body.rect.top > DESPAWN_HEIGHT)
        toRemove = true;
}
