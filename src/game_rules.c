/**
 * @brief Implementa modulo de las reglas propias del juego
 *
 * @file 
 * @author Unai.G
 * @version 1.0
 * @date 04/05/26
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_rules.h"
#include <stdio.h>
#include <stdlib.h>
#define SHERIFF_ID 70

Id game_rules_sheriff_is_dead(Game * game){
    int sheriffhp = 10;
    Character * character = NULL;
    if (!(character = game_get_character_from_id(game,SHERIFF_ID)))
    {
        return NO_ID;
    }
    sheriffhp = character_get_health(character);

    if(sheriffhp <= 0)
    {
        return 1;
    }
}

Status game_rules_update(Game *game, Command *cmd){

    if (game_rules_sheriff_is_dead(game) == 1)
    {
        game_set_finished(game,-1);
    }
    
}

