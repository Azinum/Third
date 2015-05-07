//
//  CInstance.h
//  Fifth
//
//  Created by Didrik Munther on 06/05/15.
//  Copyright (c) 2015 Didrik Munther. All rights reserved.
//

#ifndef __Fifth__CInstance__
#define __Fifth__CInstance__

#include <stdio.h>
#include "CEntityManager.h"
#include "CWindow.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CCamera.h"

class CInstance {
    
public:
    CInstance();
    
    CCamera camera;
    CPlayer* player;
    
    CEntityManager entityManager;
    CWindow window;
    
};

#endif /* defined(__Fifth__CInstance__) */
