//
//  HSMissileCommand.hpp
//  HSMissileCommand
//
//  Created by Harrison on 11/21/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#ifndef HSMissileCommand_hpp
#define HSMissileCommand_hpp

#include <math.h>

#include "mbed/mbed.h"

#include "globals.h"
#include "missile_public.h"
#include "doubly_linked_list.h"
#include "city_landscape_public.h"
#include "player_public.h"


#include "Level.hpp"
#include "Explosions.hpp"
#include "PrintToLCD.hpp"
#include "IntroScreen.hpp"
#include "MainMenu.hpp"
#include "GameOverScreen.hpp"



extern uint32_t playerScore;
extern int32_t playerLives;


typedef struct _HSMissileCommand {

    PLAYER *player;
    
    DLinkedList *missiles_bad;
    DLinkedList *missiles_good;
    
    
    uint32_t playerScore;
    uint32_t playerLives;
    uint32_t levelIndex;
    
    

} HSMissileCommand;




/***********************************************************************
 * Helper Function Prototypes
 *
 */




/**
 * numCities
 *
 * @description         The number of cities on screen must be in the range:
 *                      1 - MAX_NUM_CITY. Otherwise code further along will
 *                      error out which we do not want.
 *
 * @param setNumCities  The number of cities we want to show on screen.
 * @return              The number of actual cities to show on screen.
 */
uint32_t numCities(uint32_t setNumCities, bool readWrite);


/**
 * HS Serial Print Line
 *
 * @brief       Print out a line to the serial port.
 * @param str   A string (const char *) to the string to print.
 */
void HSSerialPrintLine(const char *str);


/**
 * didMissileHit
 *
 * @brief           Determine if a missile has struck a city within some margin.
 * @param city      A pointer (CITY *) to the city.
 * @param missile   A pointer (MISSILE *) to the missile.
 * @return          True if its a hit. False otherwise.
 */

bool didMissileHit(CITY *city, MISSILE* missile);


/**
 * didMissileHitPlayer
 *
 * @brief   Check to see if a missile has hit the player.
 * @return  True if the missile has hit the player. False otherwise.
 */

bool didMissileHitPlayer(MISSILE *missile, PLAYER *player);


/**
 * didMissileHitPlayer
 *
 * @brief   Check to see if a missile has hit the player.
 * @return  True if the missile has hit the player. False otherwise.
 */
bool didMissileHitMissile(MISSILE *badmissile, PLAYER_MISSILE *goodmissile, float radius);




/**
 * UpdateCityStatus
 *
 * @brief   Check to see if missiles have hit the city. If so update the cities.
 */
void UpdateCityStatus(Level *l);


/**
 * UpdateMissileStatus
 *
 * @brief   Walk both missile linked lists and check for collisions.
 */
void UpdateMissileStatus(Level *l);

/**
 * ResetInterceptedMissilesThisLevel
 *
 */

void ResetInterceptedMissileCount();

/**
 * GetInterceptedMissilesThisLevel
 */

uint32_t GetInterceptedMissileCount();

/**
 * Check Player Status
 *
 * @brief   Walk the missile linked list and find out if a missile has hit
 *          the players ship!
 */
void UpdatePlayerStatus(Level *l);







/**
 * CheckGameOver
 *
 * @brief       Check to see if the game is over.
 * @return      Return true if all cities are destroyed, or if the player has
 *              been destroyed.
 */

bool CheckGameOver();






#endif /* HSMissileCommand_hpp */
