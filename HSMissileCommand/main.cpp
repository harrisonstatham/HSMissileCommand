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
int32_t         playerLives = 1;

Level           currentLevel = levels[0];


uint32_t        difficulty = 0;





/***********************************************************************
 * Main
 *
 *
 * To do:
 *
 * 1. The initial missile intercept radius should be 10 pixels.
 * 2. Create game over menu.
 * 3. Create some means to get back the top menu.
 *      - preferably not an infinite loop. So many infinite loops.
 * 4. When missiles move really fast they will jump over my ship, when they should destroy it.
 * 5.
 *
 * Finished:
 *
 * 1. Implement intro screen
 * 2. Implement menu system
 * 3. The city explosion should be different than the missile.
 * 4. Level should be in top left corner.
 * 5. Score should be in top right corner.
 * 6. Lives can be in lower left corner. 
 * 7. Change speed of missiles and generation rate.
 * 8.
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
    

    int rightbtnPressed = 0;
    int leftbtnPressed  = 0;
    int firebtnPressed  = 0;
    
    uint32_t numMissilesThisLevel = 0;
    
    
    while(1) {
        
        
        showIntroScreen(3);
        
        difficulty = ShowMainMenu(left_pb, right_pb, aux_pb, fire_pb);
        
        player_init();
        city_landscape_init(numCities(4, false));
        missile_init();
        draw_cities();
        
        
        // Main game loop
        while(1)
        {
            
            // Update the missile speed & interval.
            set_missile_speed(currentLevel.missileSpeed);
            set_missile_interval(currentLevel.missileRate);
            
            
            missile_generator();
            
            player_draw(HSPLAYER_COLOR);
            draw_landscape();
            
            // Print score after the missile generator so we can overwrite
            // any of the pixels that might have been set by the missile
            // generator.
            PrintScoreToScreen(playerScore);
            
            PrintLivesToScreen(playerLives);
            
            PrintLevelToScreen(&currentLevel);
            
            
            numMissilesThisLevel = GetInterceptedMissileCount();
            
            
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
            
            UpdatePlayerStatus(&currentLevel);
            
            UpdateCityStatus(&currentLevel);
            
            UpdateMissileStatus(&currentLevel);
            
            
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
                    
                    NextLevel(&currentLevel);
                    
                    ResetInterceptedMissileCount();
                }
            }
            
        }
        
        
        
        
        
        showGameOverScreen(5);
    }
    
    
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







