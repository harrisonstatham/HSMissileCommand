//
//  IntroScreen.hpp
//  HSMissileCommand
//
//  Created by Harrison on 11/22/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#ifndef IntroScreen_hpp
#define IntroScreen_hpp

#include <stdio.h>
#include <stdint.h>

#include "globals.h"
#include "Explosions.hpp"


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
void showIntroScreen(uint32_t seconds);


#endif /* IntroScreen_hpp */
