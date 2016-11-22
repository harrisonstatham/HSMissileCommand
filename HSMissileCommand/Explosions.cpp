//
//  Explosions.cpp
//  HSMissileCommand
//
//  Created by Harrison on 11/22/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#include "Explosions.hpp"



/**
 * BasicAnimateExplosionAtLocation
 *
 * @brief           Animate an explosion of a missile at a given location.
 * @param x         The x location of the explosion.
 * @param y         The y location of the explosion.
 * @param radius    The radius of the explosion.
 * @param color     The color of the explosion.
 */

void BasicAnimateExplosionAtLocation(uint32_t x, uint32_t y, uint32_t radius, uint32_t color, float delay) {
    
    // Draw some circle of different colors around the missile coordinates.
    uLCD.filled_circle(x, y , radius, color);
    wait(delay);
    uLCD.filled_circle(x, y , radius-2, LGREY);
    wait(delay);
    uLCD.filled_circle(x, y , radius-2, BLACK);
    wait(delay);
    uLCD.filled_circle(x, y , radius, BLACK);
}





/**
 * AnimateExplosionAtLocation
 *
 * @brief           Animate an explosion of a missile at a given location.
 * @param x         The x location of the explosion.
 * @param y         The y location of the explosion.
 * @param isCity    Is the explosion a city? If so, do some other fancy stuff.
 */

void AnimateExplosionAtLocation(uint32_t x, uint32_t y, bool isCity) {
    
    // We have two different animations for missiles and cities.
    // Missiles are fairly simple. Cities will be a bit more dramatic...
    
    if(isCity) {
        
        // City destruction animation.
        // Do something a bit more dramatic!
        
        
        
    } else {
        
        BasicAnimateExplosionAtLocation(x, y, 5, RED, 0.01);
    }
}
