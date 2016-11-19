// ============================================
// The file implement the missile module
// Fall 2016 Gatech ECE2035
//=============================================

#include "missile_private.h"
#include "doubly_linked_list.h"


int missile_tick = 0;

uint32_t numMissilesThisLevel = 0;

bool shouldContinueToDrawMissiles = true;

//Create a DLL for missiles
DLinkedList* missileDLL = NULL;


/**
 * missile_init
 *
 * @description         Call missile_init() only once at the begining of your code
 */
void missile_init(void)
{
    missileDLL = create_dlinkedlist();
}



/**
 * missile_generator
 *
 * @description         This function draw the missiles onto the screen
 *                      Call missile_generator() repeatedly in your game-loop. ex: main()
 */
void missile_generator(void){
    
    missile_tick++;
    
    // only fire the missile at certain ticks
    if((missile_tick % MISSILE_INTERVAL)==0 || missile_tick==0){
        //printf("missile_create()");
        
        if(shouldContinueToDrawMissiles) {
            
            missile_create();
            numMissilesThisLevel++;
        }
    }
    
    // update the missiles and draw them
    missile_update_position();
}



/**
 * missile_create
 *
 * @brief   This function finds an empty slot of missile record, and active it.
 */

void missile_create(void) {
    
    MISSILE* missle = (MISSILE*)malloc(sizeof(MISSILE));
    
    missle->y = 0;
    
    //each missile has its own tick
    missle->tick = 0;
    
    //set a random source for the missile
    missle->source_x = rand() % SIZE_X;
    
    //set a random target for the missile
    missle->target_x = rand() % SIZE_X;
    
    //the missile starts at its source
    missle->x = missle->source_x;
    
    missle->status = MISSILE_ACTIVE;
    
    insertHead(missileDLL, missle);
}




/**
 * missile_update_position
 *
 * @brief   This function update the position of all missiles and draw them
 */

void missile_update_position(void){    
    //controls how fast the missile will move
    int rate = MISSILE_SPEED * 25;
    //delta_x and delta_y account for the slope of the missile
    double delta_x, delta_y;
     
    MISSILE* newMissile = (MISSILE*)getHead(missileDLL);
    //iterate over all missiles
    while(newMissile)
    {            
        if(newMissile->status == MISSILE_EXPLODED)
        {
            // clear the missile on the screen
            missile_draw(newMissile, BACKGROUND_COLOR);
                        
            // Remove it from the list
            newMissile = (MISSILE*)deleteForward(missileDLL, 1);
        }
        else 
        {
            //cover the last missile location
            missile_draw(newMissile, BACKGROUND_COLOR);

            // update missile position
            delta_y = 200/rate;
            delta_x = (newMissile->target_x - newMissile->source_x)/rate;
            newMissile->y = (int)(delta_y*(newMissile->tick%rate));
            newMissile->x = (int)(newMissile->source_x + delta_x*(newMissile->tick%rate));
            // draw missile
            missile_draw(newMissile, MISSILE_COLOR);
            //update missile's internal tick
            newMissile->tick++;            
            
            // Advance the loop
            newMissile = (MISSILE*)getNext(missileDLL);
        }       
    }
}


/**
 * set_missile_speed
 *
 * @brief   Set missile speed (default speed is 4)
 */
void set_missile_speed(int speed){
    ASSERT_P(speed>=1 && speed<=8,ERROR_MISSILE_SPEED);
    if(speed>=1 && speed<=8){  
        MISSILE_SPEED = speed;
    }
}



/**
 * set_missile_interval
 *
 * @description         Set the interval that the missiles fire, interval has range of 1-100 with 1 being fired in
 *                      very quick succession and 100 being fired very slowly after one another.
 * @param   interval    An integer describing how frequently the missiles should be generated.
 */

void set_missile_interval(int interval){
    ASSERT_P(interval>=1 && interval<=100,ERROR_MISSILE_INTERVAL);
    if(interval>=1 && interval<=100){
        MISSILE_INTERVAL = interval;
    }
}


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

DLinkedList* get_missile_list() {
    return missileDLL;
}



/**
 * set_missile_interval
 *
 * @brief               This function draw a missile.
 * @param   missile     A pointer (MISSILE *) to the missile to draw.
 * @param   color       An integer representing the color of the missile.
 */

void missile_draw(MISSILE* missile, int color){
    int init_x,init_y,current_x,current_y;

    init_x = missile->source_x;
    init_y = 0;
    current_x = missile->x;
    current_y = missile->y;
    uLCD.line(init_x, init_y, current_x, current_y, color);
}



/**
 * getMissilesThisLevel
 *
 * @brief   Return the number of missiles that have been drawn this level.
 * @return  The number of missiles.
 */

uint32_t getMissilesThisLevel() {
    
    return numMissilesThisLevel;
}


/**
 * setContinueToDrawMissiles
 *
 * @brief                       Set a boolean determining whether missiles should be drawn.
 * @param   shouldDrawMissiles  A boolean determining whether missiles should be drawn.
 */

void setContinueToDrawMissiles(bool shouldDrawMissiles) {
    
    shouldContinueToDrawMissiles = shouldDrawMissiles;
}


