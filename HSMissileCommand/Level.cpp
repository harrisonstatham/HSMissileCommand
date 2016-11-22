//
//  Level.cpp
//  HSMissileCommand
//
//  Created by Harrison on 11/21/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#include "Level.hpp"


/**
 * NextLevel
 *
 * @param currentLevel  A pointer (Level *) to the current level.
 */

void NextLevel(Level *currentLevel) {
    
    // Get the next level.
    
    if(currentLevel == NULL) {
        
        *currentLevel = levels[0];
        
    } else if(currentLevel->index == 10) {
        
        // do nothing since this is the last level.
        
    } else {
        
        *currentLevel = levels[currentLevel->index];
    }
    
    // Clear all of the current missiles on the screen.
    // IE destroy the missile list.
    DLinkedList *missiles = get_missile_list();
    
    LLNode *head = missiles->head;
    MISSILE *m   = NULL;
    
    while(head) {
        
        m = (MISSILE *) head->data;
        m->status = MISSILE_EXPLODED;
        head = head->next;
    }
    
    
    // Clear all of the user missiles on the screen.
    // IE destroy the user missile list.
    PLAYER player = player_get_info();
    DLinkedList *pmissiles = player.playerMissiles;
    head = pmissiles->head;
    
    PLAYER_MISSILE *mp = NULL;
    
    while(head) {
        
        mp = (PLAYER_MISSILE *) head->data;
        mp->status = PMISSILE_EXPLODED;
        head = head->next;
    }
    
    
    // Add code here to change the missile speed and rate of
    // generation - not too hard to do!
    // There are functions that will set this for you!
    
    
    
    
    // Reset the missile generator.
    setContinueToDrawMissiles(true);
}



/**
 * CanGoToNextLevel
 *
 * @return              A boolean determining if the next level can be loaded.
 */

bool CanGoToNextLevel() {
    
    /**
    DLinkedList *missiles = get_missile_list();
    
    LLNode *head = missiles->head;
    MISSILE *m   = NULL;
    
    while(head) {
        
        m = (MISSILE *) head->data;
        
        if(m->status == MISSILE_ACTIVE) {
            
            return false;
        }
        
        head = head->next;
    }
     
    */
    
    return true;
}

