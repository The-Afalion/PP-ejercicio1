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
#define PLACA_ID 48
#define WHISKY_ID 50
BOOL game_rules_sheriff_is_dead(Game *game, Command *cmd);
BOOL game_rules_iam_drunk(Game * game, Command * cmd);
Status game_rules_update(Game *game, Command *cmd)
{
    int i;

    if (!game || !cmd)
    {
        return ERROR;
    }

/**Game rule : 1 */
    if (game_rules_sheriff_is_dead(game, cmd) == TRUE)
    {
        link_set_open(game_get_link_from_index());
    }

/**Game rule : 2 */
    if (game_rules_iam_drunk(game, cmd) == TRUE)
    {
        for ( i = 0; i < rand() % game_get_number_of_space(game) ; i++)
        {
            space_set_discovered(game_get_space_from_index(game, i) ,FALSE);
        }
        
    }
/** Game rule : 3 */

    
    return OK;
}

BOOL game_rules_sheriff_is_dead(Game *game, Command *cmd)
{
    int sheriffhp = 10;
    Character *character = NULL;
    if (!game)
    {
        return ERROR;
    }

    if (!(character = game_get_character_from_id(game, (long)SHERIFF_ID)))
    {
        return NO_ID;
    }

    sheriffhp = character_get_health(character);

    if (sheriffhp <= 0)
    {
        return 1;
    }
    return NO_ID;

}

BOOL game_rules_iam_drunk(Game * game, Command * cmd){

    Player *player = NULL;
    Object *object = NULL;
    char ** args = NULL;
    CommandCode cmd;
    if(!game || !cmd){
        return ERROR;
    }
    if (!(player = game_get_player(game)))
    {
        return FALSE;
    }
    if (!(args = command_get_args(cmd)))
    {
        return FALSE;
    }
    if ((cmd = cmd_get_code(cmd)) != USE)
    {
        return FALSE;
    }
    if (game_get_object_id_from_name(game , args[0]) == WHISKY_ID)
    {
        return TRUE;
    }
    
    return FALSE;
}

BOOL game_rules_weapon_damage_decrease(Game * game, Command * cmd){
    Player *player = NULL;
    Object *object = NULL;
    char ** args = NULL;
    CommandCode cmd;
    if(!game || !cmd){
        return ERROR;
    }
    if (!(player = game_get_player(game)))
    {
        return FALSE;
    }
    if (!(args = command_get_args(cmd)))
    {
        return FALSE;
    }
    if ((cmd = cmd_get_code(cmd)) != ATTACK)
    {
        return FALSE;
    }
    if (game_get_object_id_from_name(game , args[0]) == PLACA_ID)
    {
        return TRUE;
    }
    
    return FALSE;

}