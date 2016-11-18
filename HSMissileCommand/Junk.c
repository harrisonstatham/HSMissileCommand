/**
 * HS Intro Video Play
 * 
 * Play the intro video of missle command.
 * 
 *

void HSIntroVideo(uLCD_4DGL lcd) {
    
    // Missle command in big red, blocky, text. 
    // Then colored circles take chunks of the letters away slowly.
    // Then it fades out to the main menu.
    
}

void HSLCDPrintText(uLCD_4DGL lcd, char *s, int row, int col) {
    
    lcd.text_string(s, (row >> 8) & 0xFF, (col >> 8) & 0xFF, lcd.current_font, lcd.current_color);
}

void HSMenuDisplay(uLCD_4DGL lcd, DigitalIn leftbtn, DigitalIn rightbtn, DigitalIn firebtn, Serial serialport) {

    // The real main menu has the game playing automatically.
    // Im not doing that so, we can just have a "boring" menu
    // system where you can go up and down and select various items.
    HSMenu = create_dlinkedlist();
    
    HSUITextMenuItem playItem = {
        .text               = "Play",
        .textColor          = WHITE,
        .altTextColor       = BLACK,
        .backgroundColor    = BLACK,
        .altBackgroundColor = WHITE,
        .selected           = true,
        .position           {.x = 0, .y = 0}
    };
    
    HSUITextMenuItem settingsItem = {
        .text               = "Settings",
        .textColor          = WHITE,
        .altTextColor       = BLACK,
        .backgroundColor    = BLACK,
        .altBackgroundColor = WHITE,
        .selected           = false,
        .position           {.x = 0, .y = 0}
    };
    
    HSUITextMenuItem scoresItem = {
        .text               = "High Scores",
        .textColor          = WHITE,
        .altTextColor       = BLACK,
        .backgroundColor    = BLACK,
        .altBackgroundColor = WHITE,
        .selected           = false,
        .position           {.x = 0, .y = 0}
    };
    
    HSUITextMenuItem creditsItem = {
        .text               = "Credits",
        .textColor          = WHITE,
        .altTextColor       = BLACK,
        .backgroundColor    = BLACK,
        .altBackgroundColor = WHITE,
        .selected           = false,
        .position           {.x = 0, .y = 0}
    };
    
    
    // Insert all of the items into the list. Then we can walk the list and
    // draw each item.
    insertTail(HSMenu, (void *) &settingsItem);
    insertTail(HSMenu, (void *) &scoresItem);
    insertTail(HSMenu, (void *) &creditsItem);
    
    // we insert the play at the head so it sets this as the current element!
    insertHead(HSMenu, (void *) &playItem);
    
    while(1) {
        
        // Draw the "Missle Command" text in the top center portion
        // of the screen.
        
        
        // Draw the menu.    
        // x1, y1, x2, y2, color
        
        lcd.color(WHITE);
        lcd.text_string("Play", '\x0A', '\x0A', lcd.current_font, lcd.current_color);
        
        wait(0.5);
        
    }
    
    // Clear the screen and continue.
    
}*/