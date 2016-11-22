//
//  PrintToLCD.hpp
//  HSMissileCommand
//
//  Created by Harrison on 11/21/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#ifndef PrintToLCD_hpp
#define PrintToLCD_hpp

#include <string.h>

#include "globals.h"

#include "Level.hpp"
#include "player_public.h"



/**
 * PrintScoreToScreen
 *
 * @brief   Print the current number of intercepted missiles to the screen.
 */
void PrintScoreToScreen(uint32_t score);


/**
 * PrintLivesToScreen
 *
 * @brief   Print the current number of player lives to the screen.
 */
void PrintLivesToScreen(uint32_t numLives);



/**
 * PrintLevelToScreen
 *
 * @brief   Print the current level to the screen.
 */

void PrintLevelToScreen(Level *currentLevel);


#endif /* PrintToLCD_hpp */
