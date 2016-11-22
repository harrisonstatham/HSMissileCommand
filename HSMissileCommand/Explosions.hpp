//
//  Explosions.hpp
//  HSMissileCommand
//
//  Created by Harrison on 11/22/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#ifndef Explosions_hpp
#define Explosions_hpp

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"


/**
 * BasicAnimateExplosionAtLocation
 *
 * @brief           Animate an explosion of a missile at a given location.
 * @param x         The x location of the explosion.
 * @param y         The y location of the explosion.
 * @param radius    The radius of the explosion.
 * @param color     The color of the explosion.
 */

void BasicAnimateExplosionAtLocation(uint32_t x, uint32_t y, uint32_t radius, uint32_t color, float delay);



/**
 * AnimateExplosionAtLocation
 *
 * @brief           Animate an explosion of a missile at a given location.
 * @param x         The x location of the explosion.
 * @param y         The y location of the explosion.
 * @param isCity    Is the explosion a city? If so, do some other fancy stuff.
 */

void AnimateExplosionAtLocation(uint32_t x, uint32_t y, bool isCity);






#endif /* Explosions_hpp */
