//
//  GameOverScreen.cpp
//  HSMissileCommand
//
//  Created by Harrison on 11/22/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#include "GameOverScreen.hpp"





/**
 * Show Game Over Screen
 *
 * @brief           Show the game over screen to the user.
 * @description     In Missile Command there is game over text in the middle
 *                  of the screen. A black square (rotated 45 degrees) grows
 *                  out from the middle of the screen slowly revealing the game over
 *                  text on top of a red background.
 *
 * @author          Harrison Statham
 */
void showGameOverScreen(uint32_t seconds) {
    
    // Alternatively we could create explosions all over the screen like we do in the opening scene.
    // Draw some explosions here!
    
    // Paint the background red.
    uLCD.background_color(RED);
    
    // Clear the screen. This will also repaint the background to red.
    uLCD.cls();
    
    uint32_t x_left = 64;
    uint32_t y_left = 64;
    
    uint32_t x_right = 64;
    uint32_t y_right = 64;
    
    uint32_t x_point        = 64;
    uint32_t y_point_up     = 64;
    uint32_t y_point_down   = 64;
    

    
    while(x_left > 0 && x_right < 164) {
        
        // Draw the expanding rotated square.
        
        uLCD.triangle(x_left, y_left, x_point, y_point_up, x_right, y_right, BLACK);
        uLCD.triangle(x_left, y_left, x_point, y_point_down, x_right, y_right, BLACK);
        
        if(x_left < 16 ) {
        
            // Draw game over text to screen.
            uLCD.text_string(" GAME OVER!", '\x04', '\x07', FONT_7X8, RED);
        
        }
        
        x_left--;
        x_right++;
        
        y_point_up--;
        y_point_down++;
    }
    

    
    
    wait(seconds);
    
    // Paint the background black again.
    uLCD.background_color(BLACK);
    
    // Clear the screen. This will also repaint the background to black.
    uLCD.cls();
    
}
