/***********************************************************************
 *  Missile Command
 *
 *  @brief      An implementation of the Missile Command arcade game on the MBED.
 *
 *  @author     Harrison Statham
 *  @date       Fall 2016
 */


#include "mbed/mbed.h"   
#include "stdint.h"

#include "wave_player.h"
#include "MMA8452.h"

#include "globals.h"
#include "city_landscape_public.h"
#include "missile_public.h"
#include "player_public.h"

#include "HSMissileCommand.hpp"



/***********************************************************************
 * Helper Function Prototypes
 *
 */


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
DigitalIn       aux_pb(p24);

uLCD_4DGL       uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;

// Speaker
AnalogOut       DACout(p18);
PwmOut          speaker(p25);
wave_player     waver(&DACout);

// SD Card
SDFileSystem    sd(p5, p6, p7, p8, "sd"); // mosi, miso, sck, cs


uint32_t        playerScore = 0;
int32_t        playerLives = 1;

Level           currentLevel = levels[0];


uint32_t        difficulty = 0;



/***********************************************************************
 * Main
 *
 *
 * To do:
 *
 * 1. The initial missile intercept radius should be 10 pixels.
 * 2. The city explosion should be different than the missile.
 * 3. Level should be in top left corner.
 * 4. Score should be in top right corner.
 * 5. Lives can be in lower left corner. 
 *
 * Finished:
 *
 * 1. Implement intro screen
 * 2. Implement menu system
 *
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
    aux_pb.mode(PullUp);
    
    
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
    
    
    showIntroScreen(3);
    
    difficulty = ShowMainMenu(left_pb, right_pb, aux_pb, fire_pb);
    
    player_init();
    city_landscape_init(numCities(3, false));
    missile_init();
    draw_cities();
    
    
    int rightbtnPressed = 0;
    int leftbtnPressed  = 0;
    int firebtnPressed  = 0;
    
    uint32_t numMissilesThisLevel = 0;
    
    // Main game loop
    while(1)
    {
        
        missile_generator();
        
        player_draw(HSPLAYER_COLOR);
        draw_landscape();
        
        // Print score after the missile generator so we can overwrite
        // any of the pixels that might have been set by the missile
        // generator.
        PrintScoreToScreen(playerScore);
        
        PrintLivesToScreen(playerLives);
        
        PrintLevelToScreen(&currentLevel);
        
        
        numMissilesThisLevel = getMissilesThisLevel();
        
        
        #ifdef HSDEBUG
        
        
        
        #endif
        
        // 1. Update missiles
        // 2. Read input
        
        rightbtnPressed = !right_pb.read();
        leftbtnPressed  = !left_pb.read();
        firebtnPressed  = !fire_pb.read();
        
        
        // 3. Update player position
        
        if(rightbtnPressed && leftbtnPressed) {
            // do level advance here.
            
            #ifdef HSDEBUG
                        
                pc.printf("Going to next level.\n\r");
            
            #endif
            
            NextLevel(&currentLevel);
            
            #ifdef HSDEBUG
                        
                pc.printf("On next level.\n\r");
                        
            #endif
            
            // Wait for a little to slow down the code.
            // As it is a human cant press both buttons, and remove their fingers without
            // it advancing multiple levels.
            wait(0.5);
            
            if(CheckGameOver()) {
                
                break;
            }
            
            // Go to next iteration of loop, to start next level.
            continue;
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
        
        
        // 7. Check for next level.
        if(numMissilesThisLevel >= currentLevel.numMissilesMax) {
            
            #ifdef HSDEBUG
                pc.printf("Satisfied condition for next level.\n\r");
            #endif
            
            // Stop drawing new missiles to the screen.
            setContinueToDrawMissiles(false);
            
            
            if(CanGoToNextLevel()) {
                
                #ifdef HSDEBUG
                    pc.printf("Going to next level.\n\r");
                #endif
                
                numMissilesThisLevel = 0;
                
                NextLevel(&currentLevel);
            }
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







