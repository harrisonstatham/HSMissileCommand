//
//  MainMenu.hpp
//  HSMissileCommand
//
//  Created by Harrison on 11/22/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <stdio.h>
#include <stdlib.h>

#include "mbed/mbed.h"

#include "globals.h"


/**
 * Show Main Menu
 *
 * @brief           Show the main menu to the user.
 * @return          An unsigned int (uint32_t) giving the difficulty.
 *                  (0 = easy, 1 = medium, 2 = hard)
 *
 * @author          Harrison Statham
 */
uint32_t ShowMainMenu(DigitalIn leftbtn, DigitalIn rightbtn, DigitalIn auxbtn, DigitalIn firebtn);




#endif /* MainMenu_hpp */
