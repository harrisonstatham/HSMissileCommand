// ============================================
// The file is for module "city landscape"
// This module is provdied in C style for new programmers in C
// 2014 Gatech ECE2035
//=============================================

#include "city_landscape_private.h"

CITY city_record[MAX_NUM_CITY];
int building_height[NUM_BUILDING];

// See the comments in city_landscape_public.h
void city_landscape_init(int num_city) {
    int i;
    int city_distance = (SIZE_X-CITY_TO_SCREEN_MARGIN*2)/num_city;
    
    // All interface for user should have error checking
    ASSERT_P(num_city<=MAX_NUM_CITY,ERROR_CITY_NUMBER);
    
    //initialize the record of cities
    for(i=0;i<MAX_NUM_CITY;i++){
        if(i<num_city){
            // See the definition of CITY structure in city_landscape.h
            city_record[i].y = REVERSE_Y(LANDSCAPE_HEIGHT)-1;
            city_record[i].x = i*city_distance + CITY_TO_SCREEN_MARGIN;
            city_record[i].width = CITY_WIDTH;            // the width is fix number
            city_record[i].height = MAX_BUILDING_HEIGHT;  // the height is fix number
            city_record[i].status = EXIST;
        }
        else{
            city_record[i].status = DESTORIED;
        }
    }
    
    //initialize the height of the buildings
    srand(1);
    for(i=0;i<NUM_BUILDING;i++){
        building_height[i] = (rand() % MAX_BUILDING_HEIGHT*2/3)+MAX_BUILDING_HEIGHT/3;
    }
    
    //draw city landscape on the screen
    draw_cities();
    draw_landscape();

}

CITY city_get_info(int index){
    // All interface for user should have error checking
    ASSERT_P(index<MAX_NUM_CITY,ERROR_CITY_INDEX_GET_INFO);
    
    return city_record[index];
}

void city_destory(int index){
    int j;
    int city_x, city_y, building_x, building_y;
    int height;
    
    // error checking. the index must smaller than its max.
    ASSERT_P(index<MAX_NUM_CITY,ERROR_CITY_INDEX_DESTROY);
    
    // remove the record
    city_record[index].status = DESTORIED;
    
    // use the background color to cover the city
    city_x = city_record[index].x;
    city_y = city_record[index].y;
    for(j=0;j<NUM_BUILDING;j++){
        building_x = city_x+j*BUILDING_WIDTH;
        building_y = city_y;
        height = building_y-building_height[j]+1;
        uLCD.filled_rectangle(building_x, building_y, building_x+BUILDING_WIDTH-1, height, BACKGROUND_COLOR);
    }
}

void draw_cities(void){
    int i,j;
    int city_x, city_y, building_x, building_y;
    int height;
    
    for(i=0;i<MAX_NUM_CITY;i++){
        
        // draw each city
        if(city_record[i].status==EXIST){
            city_x = city_record[i].x;
            city_y = city_record[i].y;
            
            // draw each building
            for(j=0;j<NUM_BUILDING;j++){
                building_x = city_x+j*BUILDING_WIDTH;
                building_y = city_y;
                height = building_y-building_height[j]+1;
                uLCD.filled_rectangle(building_x, building_y, building_x+BUILDING_WIDTH-1, height, BUILDING_COLOR);
            }
        }
    }
}

void draw_landscape(void){
    uLCD.filled_rectangle(0, SIZE_Y-1, SIZE_X-1, REVERSE_Y(LANDSCAPE_HEIGHT), LANDSCAPE_COLOR);
}