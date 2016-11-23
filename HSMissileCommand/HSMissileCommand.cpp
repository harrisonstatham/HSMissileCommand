//
//  HSMissileCommand.cpp
//  HSMissileCommand
//
//  Created by Harrison on 11/21/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#include "HSMissileCommand.hpp"



/**
 * numCities
 *
 * @description         The number of cities on screen must be in the range:
 *                      1 - MAX_NUM_CITY. Otherwise code further along will
 *                      error out which we do not want.
 *
 * @param setNumCities  The number of cities we want to show on screen.
 * @param shouldRead    Set to true to read the current number of cities.
 * @return              The number of actual cities to show on screen.
 */

uint32_t numCities(uint32_t setNumCities, bool shouldRead) {
    
    // static memory hangs around from function call to function call...
    static uint32_t actualNumCities;
    
    // If shouldRead = true, then we should just return the current value.
    if(shouldRead) return actualNumCities;
    
    // If we chose the same number, just return.
    if(setNumCities == actualNumCities) return setNumCities;
    
    // Gate the mutation of the number of cities.
    if(setNumCities >= MAX_NUM_CITY || setNumCities < 1) {
        
        actualNumCities = (setNumCities >= MAX_NUM_CITY) ? MAX_NUM_CITY : 1;
        
#ifdef HSDEBUG
        pc.printf("numCities(): Tried to create: %d cities. Min = 1, Max = %d\n\r", setNumCities, MAX_NUM_CITY);
#endif
        
        
    } else {
        
        actualNumCities = setNumCities;
    }
    
    return actualNumCities;
}






/**
 * HS Serial Print Line
 *
 * @brief       Print out a line to the serial port.
 * @param str   A string (const char *) to the string to print.
 */
void HSSerialPrintLine(const char *str) {
    
    pc.printf(str);
    pc.printf("\n\r");
}


/**
 * didMissileHit
 *
 * @brief           Determine if a missile has struck a city within some margin.
 * @param city      A pointer (CITY *) to the city.
 * @param missile   A pointer (MISSILE *) to the missile.
 * @return          True if its a hit. False otherwise.
 */

bool didMissileHit(CITY *city, MISSILE* missile) {
    
    if(city->status == DESTORIED) return false;
    
    uint32_t x_left     = city->x - CITY_HIT_MARGIN;
    uint32_t x_right    = city->x + city->width + CITY_HIT_MARGIN;
    
    uint32_t y_bottom   = city->y;
    uint32_t y_top      = city->y + city->height + CITY_HIT_MARGIN;
    
    // cache these for later usage.
    uint32_t m_x        = missile->x;
    uint32_t m_y        = missile->y;
    
    return ((m_x >= x_left    && m_x <= x_right) && (m_y >= y_bottom  && m_y <= y_top));
}



/**
 * didMissileHitPlayer
 *
 * @brief   Check to see if a missile has hit the player.
 * @return  True if the missile has hit the player. False otherwise.
 */

bool didMissileHitPlayer(MISSILE *missile, PLAYER *player) {
    
    if(missile->status == MISSILE_EXPLODED || player->status == DESTROYED) {
        return false;
    }
    
    
    uint32_t m_x = missile->x;
    uint32_t m_y = missile->y;
    
    uint32_t p_x = player->x;
    uint32_t p_y = player->y;
    uint32_t p_w = player->width;
    uint32_t p_h = player->height;
    
    bool xInRange = ((m_x >= p_x) && (m_x <= (p_x + p_w)));
    
    bool yInRange = ((m_y >= p_y) && (m_y <= (p_y + p_h)));
    
    
    return ((xInRange) && (yInRange));
}


/**
 * didMissileHitPlayer
 *
 * @brief   Check to see if a missile has hit the player.
 * @return  True if the missile has hit the player. False otherwise.
 */
bool didMissileHitMissile(MISSILE *badmissile, PLAYER_MISSILE *goodmissile, float radius) {
    
    // If the two missiles are already exploded then just return false.
    if(badmissile->status == MISSILE_EXPLODED || goodmissile->status == PMISSILE_EXPLODED) {
        return false;
    }
    
    uint32_t gm_x = goodmissile->x;
    uint32_t gm_y = goodmissile->y;
    
    uint32_t bm_x = badmissile->x;
    uint32_t bm_y = badmissile->y;
    
    // Do a simple distance calculation.
    // Calculate the distance from the two missiles.
    float distance = sqrt( pow((gm_x - bm_x), 2) + pow((gm_y - bm_y), 2) );
    
    if(distance <= radius) {
        return true;
    }
    
    return false;
}


/**
 * UpdateCityStatus
 *
 * @brief   Check to see if missiles have hit the city. If so update the cities.
 */

void UpdateCityStatus(Level *l) {
    
    DLinkedList *missilesIn = get_missile_list();
    LLNode *head            = missilesIn->head;
    
    uint32_t    num_cities = numCities(0, true);
    uint32_t    counter;
    MISSILE *   min;
    CITY        city_temp;
    
    // Walk the linked list and compare to each city.
    while(head) {
        
        // Grab the missile from the data.
        min = (MISSILE *) head->data;
        
        if(min->status == MISSILE_EXPLODED) {
            
            head = head->next;
            continue;
        }
        
        // Loop through all of the cities.
        for(counter = 0; counter < num_cities; counter++) {
            
            city_temp = city_get_info(counter);
            
            if(didMissileHit(&city_temp, min)) {
                
                // Ha! The city has been destoried!!! Wait... Destoried?...
                city_destory(counter);
                
                // Show animation for missile destruction.
                AnimateExplosionAtLocation(min->x, min->y, false);
                
                // Show an animation for the cities destruction.
                AnimateExplosionAtLocation(city_temp.x, city_temp.y, true);
                
                // Update missile to remove it from the screen.
                min->status = MISSILE_EXPLODED;
                
                
                otherSound.write(1);
                
            } else {
                
                // The missile didnt hit a city but did it hit the landscape?
                // If so it still needs to explode and be removed from the
                // screen.
                
                if(min->y >= city_temp.y) {
                    
                    AnimateExplosionAtLocation(min->x, min->y, false);
                    min->status = MISSILE_EXPLODED;
                }
                
            }
        }
        
        head = head->next;
    }
    
    
}


uint32_t numMissilesInterceptedThisLevel = 0;

/**
 * ResetInterceptedMissilesThisLevel
 *
 */

void ResetInterceptedMissileCount() {
    
    numMissilesInterceptedThisLevel = 0;
}

/**
 * GetInterceptedMissilesThisLevel
 */

uint32_t GetInterceptedMissileCount() {
    
    return numMissilesInterceptedThisLevel;
}



/**
 * UpdateMissileStatus
 *
 * @brief   Walk both missile linked lists and check for collisions.
 */

void UpdateMissileStatus(Level *l) {
    
    PLAYER person               = player_get_info();
    DLinkedList *missilesIn     = get_missile_list();
    DLinkedList *missilesOut    = person.playerMissiles;
    
    // Walk both of the lists and see if any of the missiles have hit each other.
    // Note: we probably want to define some ranges in which we call it a "hit"...
    
    LLNode *headgood    = missilesOut->head;
    LLNode *headbad     = missilesIn->head;
    
    PLAYER_MISSILE *mp  = NULL;
    MISSILE *mb         = NULL;
    
    /*
    uint32_t bad_x;
    uint32_t bad_y;
    
    uint32_t good_x;
    uint32_t good_y;
    */
    
    
    // Walk the first list and compare.
    while(headgood) {
        
        // Get the current missile.
        mp = (PLAYER_MISSILE *) headgood->data;
        
        /*
        good_x = mp->x;
        good_y = mp->y;
        */
         
        // Walk the second list and compare.
        while(headbad) {
            
            // Do some comparison of the current pointers.
            mb = (MISSILE *) headbad->data;
            
            
            if(didMissileHitMissile(mb, mp, l->interceptRadius)) {
                
                playerScore++;
                
                mp->status = PMISSILE_EXPLODED;
                mb->status = MISSILE_EXPLODED;
                
                missileSound.write(1);
                
                // We have a hit!
                AnimateExplosionAtLocation(mb->x, mb->y, false);
                
                // break out of the current loop since we dont
                // want to check the current missile against any others since
                // it has been destroyed (or destoried...)
                break;

            }
            
            /*
            // Grab the coorindates of the incoming/outgoing missiles.
            bad_x = mb->x;
            bad_y = mb->y;
            
            bool xHit = ((bad_x <= good_x + l->interceptRadius) &&
                         (bad_x >= good_x - l->interceptRadius));
            
            bool yHit = ((bad_y <= good_y ) && (bad_y >= good_y ));
            
            
            if(xHit && yHit) {
                
                playerScore++;
                
                mp->status = PMISSILE_EXPLODED;
                mb->status = MISSILE_EXPLODED;
                
                // We have a hit!
                AnimateExplosionAtLocation(bad_x, bad_y, false);
                
                // break out of the current loop since we dont
                // want to check the current missile against any others since
                // it has been destroyed (or destoried...)
                break;
            }
             
             */
            
            headbad = headbad->next;
        }
        
        // Reset the headbad pointer.
        headbad  = missilesIn->head;
        
        // Move the head good pointer to the next element.
        headgood = headgood->next;
    }
    
}

/**
 * Check Player Status
 *
 * @brief   Walk the missile linked list and find out if a missile has hit
 *          the players ship!
 */
void UpdatePlayerStatus(Level *l) {
    
    PLAYER person               = player_get_info();
    DLinkedList *missilesIn     = get_missile_list();
    LLNode *min                 = missilesIn->head;
    
    MISSILE *mis = NULL;
    
    while(min) {
        
        mis = (MISSILE *) min->data;
        
        // Check to see if the missile has hit the player ship.
        if(didMissileHitPlayer(mis, &person)) {
            
            // A missile hit the player ship.
            mis->status = MISSILE_EXPLODED;
            
            // Show animation of missile exploding.
            
            AnimateExplosionAtLocation(mis->x, mis->y, false);
            
            // Show animation of ship exploding.
            
            otherSound.write(1);
            
            
            // Check to see if we have more lives available.
            if(playerLives < 0) {
                
                // Its game over for the player.
                player_destroy();
                
                #ifdef HSDEBUG
                    pc.printf("Destroyed\n\r");
                #endif
                
                // Break out of the loop because we are done!
                break;
                
            } else {
                
                #ifdef HSDEBUG
                    pc.printf("New Ship!\n\r");
                #endif
                
                playerLives--;
                
                // respawn the ship.
                // it will naturally respawn the ship on the next loop.
                // Leave this alone.
            }
        }
        
        // Go to next element.
        min = min->next;
    }
    
}








/**
 * CheckGameOver
 *
 * @brief       Check to see if the game is over.
 * @return      Return true if all cities are destroyed, or if the player has
 *              been destroyed.
 */

bool CheckGameOver() {
    
    PLAYER   player             = player_get_info();
    uint32_t currentNumCities   = numCities(0, true);
    uint32_t counter            = 0;
    
    CITY city;
    
    // If the player has been destroyed then we need to show end of game.
    // We can modify this line in the future to check for the number of lives
    // left, and once we are out of lives then we fail.
    if(player.status != ALIVE) return true;
    
    if(playerLives < 0) return true;
    
    for(counter = 0; counter < currentNumCities; counter++) {
        
        city = city_get_info(counter);
        
        // If we find one city that isnt destroyed then obviously the game
        // should continue!
        if(city.status == EXIST) return false;
    }
    
    return true;
}
