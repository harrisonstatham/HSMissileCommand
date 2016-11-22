#include "player_private.h"

PLAYER player; // structure of player

PLAYER player_get_info(void){ // getter for user to acquire info without accessing structure
    return player;
}

// initialize the player's position, missile status, draw player, 
void player_init(void) {    
    player.x = PLAYER_INIT_X; player.y = PLAYER_INIT_Y; player.status = ALIVE;    
    player.playerMissiles = create_dlinkedlist();    
    player.delta = PLAYER_DELTA;
    player.width = PLAYER_WIDTH; 
    player.height = PLAYER_HEIGHT;
    player_draw(PLAYER_COLOR);
}

// move player PLAYER_DELTA pixels to the left
void player_moveLeft(void) {
    
    if (player.x-player.delta >= 0) {
        player_draw(BACKGROUND_COLOR);
        player.x-=player.delta;        
        player_draw(PLAYER_COLOR);
    }
}

// move player PLAYER_DELTA pixels to the right
void player_moveRight(void) { 
    if (player.x+player.delta <= 117) {
        player_draw(BACKGROUND_COLOR);
        player.x+=player.delta;
        player_draw(PLAYER_COLOR); 
    }
}

// generate an active missile to shoot 
void player_fire() { 
    PLAYER_MISSILE* playerMissile = (PLAYER_MISSILE*)malloc(sizeof(PLAYER_MISSILE));    
    playerMissile->y = player.y-player.delta;
    playerMissile->x = player.x + (player.width/2);
    playerMissile->status = PMISSILE_ACTIVE;
    insertHead(player.playerMissiles, playerMissile);
}

// draw/updates the line of any active missiles, "erase" deactive missiles
void player_missile_draw(void)
{      
        PLAYER_MISSILE* playerMissile = (PLAYER_MISSILE*)getHead(player.playerMissiles);    
        
        while(playerMissile)
        {                        
                if(playerMissile->status == PMISSILE_EXPLODED)
                {
                    //pc->printf("pmd:exploded\n");
                    uLCD.line(playerMissile->x, player.y-player.delta, playerMissile->x, playerMissile->y, BACKGROUND_COLOR);
                    playerMissile = (PLAYER_MISSILE*)deleteForward(player.playerMissiles, 1);
                } 
                else
                {   // update missile position
                    playerMissile->y -= PLAYER_MISSILE_SPEED;
                
                    if (playerMissile->y < 0)
                    {
                        //pc->printf("pmd:collision\n");
                        uLCD.line(playerMissile->x, player.y-player.delta, playerMissile->x, 0, BACKGROUND_COLOR);
                        // Remove from list                
                        playerMissile = (PLAYER_MISSILE*)deleteForward(player.playerMissiles, 1);
                    }
                    else 
                    {
                        //pc->printf("pmd:normal\n");
                        // draw missile
                        uLCD.line(playerMissile->x, playerMissile->y+PLAYER_MISSILE_SPEED, playerMissile->x, playerMissile->y, PLAYER_MISSILE_COLOR);
                        playerMissile = (PLAYER_MISSILE*) getNext(player.playerMissiles);
                    }
                }                
        }
    }
//}

// ==== player_private.h implementation ====
void player_draw(int color) {
    
    
    uLCD.filled_rectangle(player.x, player.y, player.x+player.width, player.y+player.height, color);
    
    uLCD.filled_rectangle(player.x,   player.y+5, player.x,   player.y-4, color);
    uLCD.filled_rectangle(player.x+5, player.y+5, player.x+5, player.y-10, color);
    uLCD.filled_rectangle(player.x+10,player.y+5, player.x+10,player.y-4, color);

    uLCD.filled_rectangle(player.x+player.delta, player.y-player.delta, player.x+player.width-player.delta, player.y+player.height, color);
    
    
    
    /*
     #define PLAYER_DELTA 3 // used in design of player, pixels to move, euclidean distance
     #define PLAYER_WIDTH 10
     #define PLAYER_HEIGHT 3
     */
    

    
    
    
    /*
     
    // This is a galaga ship....
    uLCD.filled_rectangle(player.x,   player.y+3, player.x,   player.y-5, color);
    uLCD.filled_rectangle(player.x+1, player.y+2, player.x+1, player.y-1, color);
    uLCD.filled_rectangle(player.x+2, player.y+1, player.x+2, player.y-7, color);
    uLCD.filled_rectangle(player.x+3, player.y+2, player.x+3, player.y-5, color);
    uLCD.filled_rectangle(player.x+4, player.y+2, player.x+4, player.y-7, color);
    
    // The middle of ship.
    uLCD.filled_rectangle(player.x+5, player.y+3, player.x+5, player.y-11, color);
    
    // The right side of ship.
    uLCD.filled_rectangle(player.x+6, player.y+2, player.x+6, player.y-7, color);
    uLCD.filled_rectangle(player.x+7, player.y+2, player.x+7, player.y-5, color);
    uLCD.filled_rectangle(player.x+8, player.y+1, player.x+8, player.y-7, color);
    uLCD.filled_rectangle(player.x+9, player.y+2, player.x+9, player.y-1, color);
    uLCD.filled_rectangle(player.x+10,player.y+3, player.x+10,player.y-5, color);
    
     */
    
    
    
    
}





// destory and "erase" the player off the screen. change status to DESTROYED
void player_destroy() {
    player_draw(BACKGROUND_COLOR);
    player.status = DESTROYED;
}













