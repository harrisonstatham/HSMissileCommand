//
//  Level.hpp
//  HSMissileCommand
//
//  Created by Harrison on 11/21/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

// Only for XCode support.
#include <stdint.h>
#include <stdio.h> // needed for NULL... 

#include "player_public.h"
#include "missile_public.h"
#include "doubly_linked_list.h"

/**
 * @struct  Level
 * @brief   A struct describing the current level.
 */

typedef struct Level {
    
    uint32_t    index;
    uint32_t    numMissilesMax;

    uint32_t    missileSpeed;
    uint32_t    missileRate;
    float       interceptRadius;

} Level;



// Define some constants in memory for each level.
// Limit to 10 levels say.

const Level levels[10] = {
    
    {
        .index              = 1,
        .numMissilesMax     = 10,
        .missileSpeed       = 7,
        .missileRate        = 10,
        .interceptRadius    = 10
    },
    {
        .index              = 2,
        .numMissilesMax     = 10,
        .missileSpeed       = 7,
        .missileRate        = 10,
        .interceptRadius    = 10
    },
    {
        .index              = 3,
        .numMissilesMax     = 10,
        .missileSpeed       = 6,
        .missileRate        = 9,
        .interceptRadius    = 9
    },
    {
        .index              = 4,
        .numMissilesMax     = 10,
        .missileSpeed       = 6,
        .missileRate        = 9,
        .interceptRadius    = 8
    },
    {
        .index              = 5,
        .numMissilesMax     = 10,
        .missileSpeed       = 5,
        .missileRate        = 8,
        .interceptRadius    = 7
    },
    {
        .index              = 6,
        .numMissilesMax     = 10,
        .missileSpeed       = 5,
        .missileRate        = 8,
        .interceptRadius    = 6
    },
    {
        .index              = 7,
        .numMissilesMax     = 10,
        .missileSpeed       = 4,
        .missileRate        = 7,
        .interceptRadius    = 5
    },
    {
        .index              = 8,
        .numMissilesMax     = 10,
        .missileSpeed       = 4,
        .missileRate        = 6,
        .interceptRadius    = 4
    },
    {
        .index              = 9,
        .numMissilesMax     = 10,
        .missileSpeed       = 3,
        .missileRate        = 5,
        .interceptRadius    = 4
    },
    {
        .index              = 10,
        .numMissilesMax     = 10,
        .missileSpeed       = 2,
        .missileRate        = 2,
        .interceptRadius    = 4
    }
};


/**
 * NextLevel
 *
 * @param currentLevel  A pointer (Level *) to the current level.
 */

void NextLevel(Level *currentLevel);


/**
 * CanGoToNextLevel
 *
 * @return              A boolean determining if the next level can be loaded.
 */

bool CanGoToNextLevel();


#endif /* Level_hpp */
