// ============================================
// The file implement the missile module
// Fall 2016 Gatech ECE2035
//=============================================

#include "missile_private.h"
#include "doubly_linked_list.h"


int missile_tick=0;

//Create a DLL for missiles
DLinkedList* missileDLL = NULL;

void missile_init(void)
{
    missileDLL = create_dlinkedlist();
}

// See the comments in missile_public.h
void missile_generator(void){
    missile_tick++;
    // only fire the missile at certain ticks
    if((missile_tick % MISSILE_INTERVAL)==0 || missile_tick==0){
        //printf("missile_create()");
        missile_create();
    }        
    // update the missiles and draw them
    missile_update_position();
}

/** This function finds an empty slot of missile record, and active it.
*/
void missile_create(void){
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

/** This function update the position of all missiles and draw them
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

// set missile speed (default speed is 4)
void set_missile_speed(int speed){
    ASSERT_P(speed>=1 && speed<=8,ERROR_MISSILE_SPEED);
    if(speed>=1 && speed<=8){  
        MISSILE_SPEED = speed;
    }
}

// set missile interval (default interval is 10)
void set_missile_interval(int interval){
    ASSERT_P(interval>=1 && interval<=100,ERROR_MISSILE_INTERVAL);
    if(interval>=1 && interval<=100){
        MISSILE_INTERVAL = interval;
    }
}

// See comments in missile_public.h
DLinkedList* get_missile_list() {
    return missileDLL;
}

/** This function draw a missile.
    @param missile The missile to be drawn
    @param color The color of the missile
*/
void missile_draw(MISSILE* missile, int color){
    int init_x,init_y,current_x,current_y;

    init_x = missile->source_x;
    init_y = 0;
    current_x = missile->x;
    current_y = missile->y;
    uLCD.line(init_x, init_y, current_x, current_y, color);
}
