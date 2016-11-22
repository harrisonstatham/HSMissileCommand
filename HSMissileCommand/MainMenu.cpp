//
//  MainMenu.cpp
//  HSMissileCommand
//
//  Created by Harrison on 11/22/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#include "MainMenu.hpp"


enum MainMenuStateMachineStates {
    
    PLAY_MENU = 0,
    DIFFICULTY_MENU,
    HIGH_SCORES_MENU,
    CREDITS_MENU
};

typedef enum MainMenuStateMachineStates HSMainMenuState;




/**
 * Show Main Menu
 *
 * @brief           Show the main menu to the user.
 * @return          An unsigned int (uint32_t) giving the difficulty.
 *                  (0 = easy, 1 = medium, 2 = hard)
 *
 * @author          Harrison Statham
 */
uint32_t ShowMainMenu(DigitalIn leftbtn, DigitalIn rightbtn, DigitalIn auxbtn, DigitalIn firebtn) {
    
    
    // Draw all the main text here that DOESNT change across states.
    
    // Show MISSILE COMMAND at the top of the screen.
    uLCD.text_string("MISSILE COMMAND", '\x02', '\x01', FONT_7X8, RED);
    
    // Show directions for navigating the menu here.
    uLCD.text_string("Right = Up",      '\x02', '\x03', FONT_7X8, RED);
    uLCD.text_string("Left  = Down",    '\x02', '\x04', FONT_7X8, RED);
    uLCD.text_string("Fire  = Enter",   '\x02', '\x05', FONT_7X8, RED);
    
    // Show the main menu text
    // Save room for a little triangle to the left of the text designating the current menu item
    // that is selected!
    
    uLCD.text_string("   Play",         '\x00', '\x07', FONT_7X8, RED);
    uLCD.text_string("   Difficulty:",  '\x00', '\x08', FONT_7X8, RED);
    uLCD.text_string("      Easy",      '\x00', '\x09', FONT_7X8, RED);
    uLCD.text_string("      Medium",    '\x00', '\x0A', FONT_7X8, RED);
    uLCD.text_string("      Hard",      '\x00', '\x0B', FONT_7X8, RED);
    uLCD.text_string("   High Scores",  '\x00', '\x0C', FONT_7X8, RED);
    uLCD.text_string("   Credits",      '\x00', '\x0D', FONT_7X8, RED);
    
    
    uint32_t rightbtnPressed    = 0;
    uint32_t leftbtnPressed     = 0;
    uint32_t firebtnPressed     = 0;
    uint32_t auxbtnPressed      = 0;
    
    
    // Initialize the state of our state machine.
    HSMainMenuState state       = PLAY_MENU;
    
    uint32_t difficulty         = 0;
    
    
    while(true) {
        
        rightbtnPressed = !rightbtn.read();
        leftbtnPressed  = !leftbtn.read();
        firebtnPressed  = !firebtn.read();
        auxbtnPressed   = !auxbtn.read();
        
        if(state == PLAY_MENU) {
            
            if(leftbtnPressed) state = DIFFICULTY_MENU;
            if(firebtnPressed) break;
        
        } else if(state == DIFFICULTY_MENU) {
            
            if(rightbtnPressed) state = PLAY_MENU;
            if(leftbtnPressed)  state = HIGH_SCORES_MENU;
            
            if(auxbtnPressed) {
                
                // do toggle of difficulty here.
            }
            
        } else if(state == HIGH_SCORES_MENU) {
            
            if(rightbtnPressed)     state = DIFFICULTY_MENU;
            if(leftbtnPressed)      state = CREDITS_MENU;
            
            if(firebtnPressed) {
                
                // show high scores menu.
            }
        
        } else if(state == CREDITS_MENU) {
            
            if(rightbtnPressed)     state = HIGH_SCORES_MENU;
            
            if(firebtnPressed) {
                
                // show credits menu.
            }
        }
        
        
        
    }
    
    return difficulty;
}


