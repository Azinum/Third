//
//  CParticle.cpp
//  Third
//
//  Created by Didrik Munther on 19/03/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#include "CParticle.h"
#include "Define.h"

CParticle::CParticle(Box rect, sf::Color color, int livingTime /* = 5 */) :
CEntity(rect, color), _creationTime(_clock.getElapsedTime().asMilliseconds()), _livingTime(livingTime) {
    addProperty(EntityProperty::FLIP_FREEZED);
}

CParticle::CParticle(Box rect, std::string spriteKey, int livingTime /* = 5 */) :
CEntity(rect, spriteKey), _creationTime(_clock.getElapsedTime().asMilliseconds()), _livingTime(livingTime) {
    addProperty(EntityProperty::FLIP_FREEZED);
}

void CParticle::_doLogic() {
    CEntity::_doLogic();
    
    if(collisionBottom)
        body.velX /= 1.2;
    
    if(_clock.getElapsedTime().asMilliseconds() - _creationTime > _livingTime * 1000)
        toRemove = true;
    
    if(body.getY() > DESPAWN_HEIGHT)
        toRemove = true;
}

void CParticle::_collisionLogic() {
    
}