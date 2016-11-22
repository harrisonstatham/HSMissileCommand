//
//  HSMissileCommand.hpp
//  HSMissileCommand
//
//  Created by Harrison on 11/21/16.
//  Copyright © 2016 HarrisonStatham. All rights reserved.
//

#ifndef HSMissileCommand_hpp
#define HSMissileCommand_hpp

#include "mbed/mbed.h"
#include "missile_public.h"
#include "doubly_linked_list.h"
#include "city_landscape_public.h"
#include "player_public.h"


typedef struct _HSMissileCommand {

    PLAYER *player;
    
    DLinkedList *missiles_bad;
    DLinkedList *missiles_good;
    
    
    uint32_t playerScore;
    uint32_t playerLives;
    uint32_t levelIndex;
    
    

} HSMissileCommand;







#endif /* HSMissileCommand_hpp */
