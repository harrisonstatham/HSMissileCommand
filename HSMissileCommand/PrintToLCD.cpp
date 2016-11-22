//
//  PrintToLCD.cpp
//  HSMissileCommand
//
//  Created by Harrison on 11/21/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#include "PrintToLCD.hpp"


/**
 * PrintScoreToScreen
 *
 * @brief   Print the current number of intercepted missiles to the screen.
 * @note    The score should be in the top right corner of the screen.
 *
 * @author  Harrison Statham
 */

void PrintScoreToScreen(uint32_t score) {
    
    // Draw black rectangle in top left corner.
    //uLCD.filled_rectangle(0, 0, 40, 20, BLACK);
    
    char text[12];
    sprintf(text, "%d", score);
    
    uLCD.text_string(text, '\x0F', '\x00', FONT_7X8, GREEN);
}


/**
 * PrintLivesToScreen
 *
 * @brief   Print the current number of player lives to the screen.
 * @note    Print the lives to the bottom left corner of the screen.
 */
void PrintLivesToScreen(uint32_t lives) {
    
    char text[12];
    sprintf(text, "%d", lives);
    
    // Attempt to draw a heart from basic shapes.
    uLCD.text_string("<3", '\x00', '\x00', FONT_7X8, RED);
    uLCD.text_string(text, '\x03', '\x00', FONT_7X8, GREEN);
    
}


/**
 * PrintLevelToScreen
 *
 * @brief   Print the current level to the screen.
 * @note    The level should be in the top left corner of the screen.
 */

void PrintLevelToScreen(Level *level) {
    
    char text[12];
    sprintf(text, "L: %d", level->index);
    
    uLCD.text_string(text, '\x00', '\x02', FONT_7X8, GREEN);
}
