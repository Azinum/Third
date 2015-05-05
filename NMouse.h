//
//  NMouse.h
//  Third
//
//  Created by Didrik Munther on 16/04/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __Third__NMouse__
#define __Third__NMouse__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "CCamera.h"

namespace NMouse {
    
    int absoluteMouseX(sf::RenderWindow* window);
    int absoluteMouseY(sf::RenderWindow* window);
    
    int relativeMouseX(sf::RenderWindow* window, CCamera* camera);
    int relativeMouseY(sf::RenderWindow* window, CCamera* camera);
    
};

#endif /* defined(__Third__NMouse__) */
