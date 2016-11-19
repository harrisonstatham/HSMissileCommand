// ============================================
// The header file define the missile module
// Fall 2016 Gatech ECE2035
//=============================================

/** @file missile_public.h */

#ifndef MISSILE_PUBLIC_H
#define MISSILE_PUBLIC_H


#include <stdint.h>
#include "doubly_linked_list.h"





/**
 * @enum    MISSILE_STATUS
 * @brief   An enum that describes the state of a missile.
 */

typedef enum {
    
    MISSILE_EXPLODED    = 0,
    MISSILE_ACTIVE      = 1
    
} MISSILE_STATUS;




/**
 * @struct  MISSILE
 * @brief   The structure to store the information of a missile
 */
typedef struct {
    
    int x;                   ///< The x-coordinate of missile current position
    int y;                   ///< The y-coordinate of missile current position
    
    double source_x;           ///< The x-coordinate of the missile's origin
    double target_x;           ///< The x-coordinate of the missile's target
    
    int tick;                  ///< The missile's internal tick
    
    MISSILE_STATUS status;   ///< The missile status, see MISSILE_STATUS
    
} MISSILE;



/**
 * missile_init
 *
 * @description         Call missile_init() only once at the begining of your code
 */

void missile_init(void);



/**
 * missile_generator
 *
 * @description         This function draw the missiles onto the screen
 *                      Call missile_generator() repeatedly in your game-loop. ex: main()
 */

void missile_generator(void);



/**
 * get_missile_list
 *
 * @description         This function will return a linked-list of all active MISSILE structures.
 *                      This can be used to modify the active missiles. Marking missiles with status
 *                      MISSILE_EXPLODED will cue their erasure from the screen and removal from the
 *                      list at the next missile_generator() call.
 *
 * @return              A linked list (DLinkedList *) with all the missiles.
 */

DLinkedList* get_missile_list();


/**
 * set_missile_speed
 *
 * @description     Set the speed of missiles, Speed has range of 1-8 with 1 being fastest and 8 being slowest
 * @param   speed   The speed of the missiles.
 */

void set_missile_speed(int speed);


/**
 * set_missile_interval
 *
 * @description         Set the interval that the missiles fire, interval has range of 1-100 with 1 being fired in
 *                      very quick succession and 100 being fired very slowly after one another.
 * @param   interval    An integer describing how frequently the missiles should be generated.
 */

void set_missile_interval(int interval);



/**
 * getMissilesThisLevel
 *
 * @brief   Return the number of missiles that have been drawn this level.
 * @return  The number of missiles.
 */

uint32_t getMissilesThisLevel();




#endif //MISSILE_PUBLIC_H
