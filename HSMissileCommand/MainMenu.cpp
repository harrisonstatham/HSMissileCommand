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




void ShowHighScoreMenu() {
    
    // Start text at row \x05
    uLCD.text_string("High Scores:",        '\x02', '\x05', FONT_7X8, RED);
    uLCD.text_string("Harrison:   Inf",     '\x02', '\x06', FONT_7X8, RED);
    
}

void ShowCreditsMenu() {
    
    // Start text at row \x05
    uLCD.text_string("Credits:",            '\x02', '\x05', FONT_7X8, RED);
    uLCD.text_string("Dr. Schimmel",        '\x02', '\x06', FONT_7X8, RED);
    uLCD.text_string("Dr. Wills",           '\x02', '\x07', FONT_7X8, RED);
    uLCD.text_string("GT 2035 TAs",         '\x02', '\x08', FONT_7X8, RED);
    uLCD.text_string("Harrison Statham",    '\x02', '\x09', FONT_7X8, RED);
}



void ShowAltMenu(DigitalIn auxbtn, uint32_t whatMenu) {
    
    uLCD.cls();
    
    // Show MISSILE COMMAND at the top of the screen.
    uLCD.text_string("MISSILE COMMAND", '\x02', '\x01', FONT_7X8, RED);
    
    // Show directions for navigating the menu here.
    uLCD.text_string("Aux  = Back",   '\x02', '\x03', FONT_7X8, RED);
    
    
    while(true) {
        
        if(whatMenu == 0) {
            
            ShowHighScoreMenu();
        
        } else if(whatMenu == 1) {
            
            ShowCreditsMenu();
            
        } else {
            
            break;
        }
        
        
        if(!auxbtn.read()) {
            
            break;
        }
    }
    
    // Clear the screen before returning.
    uLCD.cls();
    
}





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
    
    
    uint32_t rightbtnPressed    = 0;
    uint32_t leftbtnPressed     = 0;
    uint32_t firebtnPressed     = 0;
    uint32_t auxbtnPressed      = 0;
    
    
    // Initialize the state of our state machine.
    HSMainMenuState state       = PLAY_MENU;
    
    uint32_t difficulty         = 0;
    
    char *playText;
    char *difficultyText;
    char *difficultyEasyText;
    char *difficultyMediumText;
    char *difficultyHardText;
    
    char *highScoreText;
    char *creditText;
    
    
    while(true) {
        
        rightbtnPressed = !rightbtn.read();
        leftbtnPressed  = !leftbtn.read();
        firebtnPressed  = !firebtn.read();
        auxbtnPressed   = !auxbtn.read();
        
        // Initialize all of the text to the default case.
        // Then we change it below.
        playText                = (char *) "   Play";
        difficultyText          = (char *) "   Difficulty:";
        difficultyEasyText      = (char *) "      Easy";
        difficultyMediumText    = (char *) "      Medium";
        difficultyHardText      = (char *) "      Hard";
        highScoreText           = (char *) "   High Scores";
        creditText              = (char *) "   Credits";
    
        if(state == PLAY_MENU) {
            
            if(leftbtnPressed) state = DIFFICULTY_MENU;
            if(firebtnPressed) break;
            
            playText = (char *) "-> Play";
        
        } else if(state == DIFFICULTY_MENU) {
            
            if(rightbtnPressed) state = PLAY_MENU;
            if(leftbtnPressed)  state = HIGH_SCORES_MENU;
            
            difficultyText = (char *) "-> Difficulty:";
            
            
            
            if(difficulty == 0) {
                
                difficultyEasyText      = (char *) "   >  Easy";
            
            } else if(difficulty == 1) {
                
                difficultyMediumText    = (char *) "   >  Medium";
            
            } else if(difficulty == 2) {
                
                difficultyHardText      = (char *) "   >  Hard";
            }
            
            if(auxbtnPressed) {
                
                // do toggle of difficulty here.
                // Yes, we could use something with mod. Might end up doing that.
                if(difficulty == 0 || difficulty == 1 || difficulty == 2) difficulty++;
                
                if(difficulty == 3) difficulty = 0;
            }
            
            
        } else if(state == HIGH_SCORES_MENU) {
            
            if(rightbtnPressed)     state = DIFFICULTY_MENU;
            if(leftbtnPressed)      state = CREDITS_MENU;
            
            highScoreText   = (char *) "-> High Scores";
            
            
            if(firebtnPressed) {
                
                // show high scores menu.
                
                ShowAltMenu(auxbtn, 0);
                
                // Immediately continue to redraw menu.
                continue;
            }
        
        } else if(state == CREDITS_MENU) {
            
            if(rightbtnPressed)     state = HIGH_SCORES_MENU;
            
            creditText  = (char *) "-> Credits";
            
            
            if(firebtnPressed) {
                
                // show credits menu.
                
                ShowAltMenu(auxbtn, 1);
                
                // Immediately continue to redraw menu.
                continue;
            }
        }
        
        
        // Show directions for navigating the menu here.
        uLCD.text_string("Right = Up",      '\x02', '\x03', FONT_7X8, RED);
        uLCD.text_string("Left  = Down",    '\x02', '\x04', FONT_7X8, RED);
        uLCD.text_string("Fire  = Enter",   '\x02', '\x05', FONT_7X8, RED);
        
        
        
        // Show the main menu text
        // Save room for a little triangle to the left of the text designating the current menu item
        // that is selected!
        
        uLCD.text_string(playText,                  '\x00', '\x07', FONT_7X8, RED);
        uLCD.text_string(difficultyText,            '\x00', '\x08', FONT_7X8, RED);
        uLCD.text_string(difficultyEasyText,        '\x00', '\x09', FONT_7X8, RED);
        uLCD.text_string(difficultyMediumText,      '\x00', '\x0A', FONT_7X8, RED);
        uLCD.text_string(difficultyHardText,        '\x00', '\x0B', FONT_7X8, RED);
        uLCD.text_string(highScoreText,             '\x00', '\x0C', FONT_7X8, RED);
        uLCD.text_string(creditText,                '\x00', '\x0D', FONT_7X8, RED);
        
    }
    
    
    // Clear the screen of the main menu screen.
    uLCD.cls();
    
    
    return difficulty;
}


