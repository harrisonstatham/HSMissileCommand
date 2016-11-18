/***********************************************************************
 *  Missile Command
 *
 *  An implementation of the Missile Command arcade game on the MBED.
 * 
 *  Harrison Statham
 */
 
#include "mbed/mbed.h"   
#include "stdint.h"

#include "wave_player.h"
#include "MMA8452.h"

#include "globals.h"
#include "city_landscape_public.h"
#include "missile_public.h"
#include "player_public.h"




/***********************************************************************
 * Defines & Macros
 *
 */

#define HSDEBUG 1

#define HSPLAYER_COLOR    255

#define MISSILE_TO_MISSILE_MARGIN 3

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))



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
 * UpdateCityStatus
 *
 * @brief   Check to see if missiles have hit the city. If so update the cities.
 */
void UpdateCityStatus(void);


/**
 * UpdateMissileStatus
 *
 * @brief   Walk both missile linked lists and check for collisions.
 */
void UpdateMissileStatus(void);


/**
 * Check Player Status
 *
 * @brief   Walk the missile linked list and find out if a missile has hit
 *          the players ship!
 */
void UpdatePlayerStatus(void);




/**
 * AnimateExplosionAtLocation
 *
 * @brief           Animate an explosion of a missile at a given location.
 * @param x         The x location of the explosion.
 * @param y         The y location of the explosion.
 * @param isCity    Is the explosion a city? If so, do some other fancy stuff.
 */

void AnimateExplosionAtLocation(uint32_t x, uint32_t y, bool isCity);


/**
 * CheckGameOver
 *
 * @brief       Check to see if the game is over.
 * @return      Return true if all cities are destroyed, or if the player has
 *              been destroyed.
 */

bool CheckGameOver();


/**
 * PrintScoreToScreen
 *
 * @brief   Print the current number of intercepted missiles to the screen.
 */ 
void PrintScoreToScreen();


/**
 * PrintLivesToScreen
 *
 * @brief   Print the current number of player lives to the screen.
 */ 
void PrintLivesToScreen();


/**
 * playSound
 *
 * @brief       Play a sound using the buzzer.
 * @param wav   A string (char *) to the file to play.
 */
void playSound(char* wav);







/***********************************************************************
 * Global Variables
 *
 */

Serial          pc(USBTX,USBRX);

MMA8452         accel(p28, p27, 100000);

DigitalIn       left_pb(p21);
DigitalIn       right_pb(p22); 
DigitalIn       fire_pb(p23);

uLCD_4DGL       uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;

// Speaker
AnalogOut       DACout(p18);
PwmOut          speaker(p25);
wave_player     waver(&DACout);

// SD Card
SDFileSystem    sd(p5, p6, p7, p8, "sd"); // mosi, miso, sck, cs


uint32_t        playerScore = 0;
uint32_t        playerLives = 1;

/***********************************************************************
 * Main
 *
 */

int main()
{
    // Replace <outfile> with your student ID
    /*test_dlinkedlist(
        "/sd/tests/dll_test.txt",
        "/sd/<outfile>.txt"
    );*/

    // Test the speaker
    //playSound("/sd/wavfiles/BUZZER.wav");
    
    //Initialize hardware buttons
    left_pb.mode(PullUp); 
    right_pb.mode(PullUp);
    fire_pb.mode(PullUp);
    
    
    /*******************************************
     * Initialize
     *
     * Initialize any portions of the code here.
     * 
     * 1. Player
     * 2. City Landscape
     * 3. Missiles
     * 4. ...
     */
     
    player_init();
    city_landscape_init(numCities(3, false));
    missile_init();
    draw_cities();
    
    
    int rightbtnPressed = 0;
    int leftbtnPressed  = 0;
    int firebtnPressed  = 0;
    
    
    // Main game loop
    while(1)
    {
        
        missile_generator();
        
        player_draw(HSPLAYER_COLOR);
        draw_landscape();
        
        // Print score after the missile generator so we can overwrite
        // any of the pixels that might have been set by the missile
        // generator.
        PrintScoreToScreen();
        
        PrintLivesToScreen();
        
        #ifdef HSDEBUG
        
            pc.printf("Testing the local ARM compiler.\n\r");
        
        #endif
        
        // 1. Update missiles
        // 2. Read input
        
        rightbtnPressed = !right_pb.read();
        leftbtnPressed  = !left_pb.read();
        firebtnPressed  = !fire_pb.read();
        
        
        // 3. Update player position
        
        if(rightbtnPressed && leftbtnPressed) {
            // do level advance here.    
        }
        
        if(rightbtnPressed) {
            
            player_moveRight();
            
            #ifdef HSDEBUG
                pc.printf("Moving right.\n\r");
            #endif
        }
        
        if(leftbtnPressed) {
        
            player_moveLeft();  
            
            #ifdef HSDEBUG
                pc.printf("Moving left.\n\r");
            #endif
        }
        
        if(firebtnPressed) {
            
            player_fire();  
            
            #ifdef HSDEBUG
                pc.printf("Firing.\n\r");
            #endif
        }
        
        player_missile_draw();
        
        
        // 4. Check for collisions
        
        #ifdef HSDEBUG
            pc.printf("Checking for collisions.\n\r");
        #endif
        
        UpdatePlayerStatus();
        
        UpdateCityStatus();
        
        UpdateMissileStatus();
        
        
        // 5. Redraw city landscape
        draw_cities();
        
        
        // 6. Check for endgame
        
        if(CheckGameOver()) {
            
            break;
        }
        
    }
    
    // Show the game over menu here.
    // more advanced in the future.
    uLCD.printf("Game Over\n\r");
    
    // ===User implementations end===
    
    
    // Clean up.
    
}



/***********************************************************************
 * Helper Functions
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
        
        pc.printf("numCities(): Tried to create: %d cities. Min = 1, Max = %d\n\r", setNumCities, MAX_NUM_CITY);
    
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
 * UpdateCityStatus
 *
 * @brief   Check to see if missiles have hit the city. If so update the cities.
 */

void UpdateCityStatus(void) {
    
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




/**
 * UpdateMissileStatus
 *
 * @brief   Walk both missile linked lists and check for collisions.
 */
 
void UpdateMissileStatus() {
    
    PLAYER person               = player_get_info();
    DLinkedList *missilesIn     = get_missile_list();
    DLinkedList *missilesOut    = person.playerMissiles;
    
    // Walk both of the lists and see if any of the missiles have hit each other.
    // Note: we probably want to define some ranges in which we call it a "hit"...
    
    LLNode *headgood    = missilesOut->head;
    LLNode *headbad     = missilesIn->head;
    
    PLAYER_MISSILE *mp  = NULL;
    MISSILE *mb         = NULL;
    
    uint32_t bad_x;
    uint32_t bad_y;
    
    uint32_t good_x;
    uint32_t good_y;
    
    // Walk the first list and compare.
    while(headgood) {
        
        // Get the current missile.
        mp = (PLAYER_MISSILE *) headgood->data;
        
        
        good_x = mp->x;
        good_y = mp->y;  
        
        // Walk the second list and compare.
        while(headbad) {
            
            // Do some comparison of the current pointers.
            mb = (MISSILE *) headbad->data;
            
            
            
            // Grab the coorindates of the incoming/outgoing missiles.
            bad_x = mb->x;
            bad_y = mb->y;
            
            bool xHit = ((bad_x <= good_x + MISSILE_TO_MISSILE_MARGIN) &&
                         (bad_x >= good_x - MISSILE_TO_MISSILE_MARGIN));
            
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
void UpdatePlayerStatus(void) {
    
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
            
            // Show animation of ship exploding.   
            
            
            // Check to see if we have more lives available.
            if(playerLives < 1) {
                
                // Its game over for the player.
                person.status = DESTROYED;
                
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
 * AnimateExplosionAtLocation
 *
 * @brief           Animate an explosion of a missile at a given location.
 * @param x         The x location of the explosion.
 * @param y         The y location of the explosion.
 * @param isCity    Is the explosion a city? If so, do some other fancy stuff.
 */

void AnimateExplosionAtLocation(uint32_t x, uint32_t y, bool isCity) {
    
    // We have two different animations for missiles and cities.
    // Missiles are fairly simple. Cities will be a bit more dramatic...
        
    if(isCity) {
        
        // City destruction animation.
        
        
        
        
    } else {
        
        // Draw some circle of different colors around the missile coordinates.
        uLCD.filled_circle(x, y , 5, RED);
        wait(0.05);
        uLCD.filled_circle(x, y , 3, LGREY);
        wait(0.05);
        uLCD.filled_circle(x, y , 3, BLACK);
        wait(0.05);
        uLCD.filled_circle(x, y , 5, BLACK);
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
    
    for(counter = 0; counter < currentNumCities; counter++) {
        
        city = city_get_info(counter);
        
        // If we find one city that isnt destroyed then obviously the game
        // should continue!
        if(city.status == EXIST) return false;
    }
    
    return true;
}


/**
 * PrintScoreToScreen
 *
 * @brief   Print the current number of intercepted missiles to the screen.
 */
 
void PrintScoreToScreen() {
    
    // Draw black rectangle in top left corner.
    //uLCD.filled_rectangle(0, 0, 40, 20, BLACK);
    
    char text[12];
    sprintf(text, "S: %d", playerScore);
    
    uLCD.text_string(text, '\x00', '\x00', FONT_7X8, GREEN);
}


/**
 * PrintLivesToScreen
 *
 * @brief   Print the current number of player lives to the screen.
 */ 
void PrintLivesToScreen() {
    
    char text[12];
    sprintf(text, "   %d", playerLives);
    
    // Attempt to draw a heart from basic shapes.
    
    uLCD.text_string(text, '\x00', '\x02', FONT_7X8, GREEN);
}











// ===User implementations end===







// Plays a wavfile
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        pc.printf("File opened successfully\n\r");

        //play wav file
        pc.printf("Sound playing...\n\r");
        waver.play(wave_file);
    
        //close wav file
        pc.printf("Sound stopped...\n\r");
        fclose(wave_file);
        return;
    }
    
    pc.printf("Could not open file for reading - %s\n\r", wav);
    return;
}







