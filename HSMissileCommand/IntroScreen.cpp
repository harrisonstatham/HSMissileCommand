//
//  IntroScreen.cpp
//  HSMissileCommand
//
//  Created by Harrison on 11/22/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#include "IntroScreen.hpp"




/**
 * Show Intro Screen
 *
 * @brief           Show the intro screen to the user.
 * @description     The intro screen is some text and then explosions
 *                  that eat away at the text. This is similar to the
 *                  real Missile Command intro screen.
 *
 * @author          Harrison Statham
 */

void showIntroScreen(uint32_t seconds) {
    
    // Clear the screen just in case there is something on it.
    uLCD.cls();
    
    
    // Write out Missile Command in big red letters.
    // Should be blocky pixelated letters for effect.
    
    uLCD.text_string("MISSILE COMMAND", '\x02', '\x07', FONT_7X8, RED);
    
    uLCD.text_string("  GT ECE 2035  ", '\x02', '\x09', FONT_7X8, RED);
    uLCD.text_string("Harrison Statham", '\x01', '\x0A', FONT_7X8, RED);
    
    wait(seconds);
    
    uint32_t x = 64;
    uint32_t y = 64;
    float delay = 0.02;
    
    // Show the destruction of the above text.
    
    // 1st round of explosions
    BasicAnimateExplosionAtLocation(x+5, y+5, 10, BLUE, delay);
    BasicAnimateExplosionAtLocation(x-8, y-9, 15, RED, delay);
    BasicAnimateExplosionAtLocation(x-5, y+10, 10, GREEN, delay);
    BasicAnimateExplosionAtLocation(x+15, y+35, 15, BLUE, delay);
    BasicAnimateExplosionAtLocation(x-23, y-40, 20, RED, delay);
    BasicAnimateExplosionAtLocation(x-15, y+20, 10, GREEN, delay);
    BasicAnimateExplosionAtLocation(x+5, y+5, 5, LGREY, delay);
    BasicAnimateExplosionAtLocation(x+30, y+30, 5, BLUE, delay);
    
    
    // 2nd round of explosions
    BasicAnimateExplosionAtLocation(x+50, y+5, 10, BLUE, delay);
    BasicAnimateExplosionAtLocation(x-50, y-9, 15, RED, delay);
    BasicAnimateExplosionAtLocation(x-30, y+10, 10, GREEN, delay);
    BasicAnimateExplosionAtLocation(x+45, y+35, 15, BLUE, delay);
    BasicAnimateExplosionAtLocation(x-63, y-40, 20, RED, delay);
    BasicAnimateExplosionAtLocation(x-35, y+20, 10, GREEN, delay);
    BasicAnimateExplosionAtLocation(x+55, y+5, 5, LGREY, delay);
    BasicAnimateExplosionAtLocation(x+40, y+30, 5, BLUE, delay);
    
    // wait a little so the user can see the now "chunky" text remains.
    wait(1);
    
    
    
    // Clear the screen of the intro screen.
    uLCD.cls();
}
