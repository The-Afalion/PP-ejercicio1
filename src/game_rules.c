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
#define VAULT_LINK_ID 17
#define VAULT_ID 62
BOOL game_rules_sheriff_is_dead(Game *game, Command *cmd);
BOOL game_rules_iam_drunk(Game *game, Command *cmd);
BOOL game_rules_weapon_damage_decrease(Game *game, Command *cmd);
BOOL game_rules_game_completed(Game *game, Command *cmd);
BOOL game_rules_killedNPC(Game *game, Command *cmd);
BOOL game_rules_heavy_inventory(Game *game, Command *cmd);
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
        link_set_open(game_get_link(game, VAULT_LINK_ID), TRUE);
    }

    /**Game rule : 2 */
    if (game_rules_iam_drunk(game, cmd) == TRUE)
    {
        for (i = 0; i < rand() % game_get_number_of_space(game); i++)
        {
            space_set_discovered(game_get_space_from_index(game, i), FALSE);
        }
    }
    /** Game rule : 3 */
    game_rules_weapon_damage_decrease(game, cmd);

    /**Game rule : 4 */
    if (game_rules_game_completed(game, cmd) == TRUE)
    {
        game_set_finished(game, TRUE);
    }

    /**Game rule : 5 */
    if (game_rules_killedNPC(game, cmd) == TRUE)
    {
        for (i = 0; i < game_get_number_of_characters(game); i++)
        {
            if (character_get_friendly(game_get_character_from_index(game, i)) == FALSE && character_get_health(game_get_character_from_index(game, i)) > 0)
            {
                character_set_health(game_get_character_from_index(game, i), (int)(character_get_health(game_get_character_from_index(game, i)) + character_get_health(game_get_character_from_index(game, i)) * 0.1));
            }
        }
    }
    /**Game rule : 6 */
    if (game_rules_heavy_inventory(game, cmd) == TRUE)
    {
        if (player_get_money(game_get_player(game)) >= 2)
        {
            player_set_money(game_get_player(game), player_get_money(game_get_player(game)) - 2);
        }
    }

    return OK;
}

BOOL game_rules_sheriff_is_dead(Game *game, Command *cmd)
{
    int sheriffhp = 10;
    Character *character = NULL;
    if (!game)
    {
        return FALSE;
    }

    if (!(character = game_get_character_from_id(game, (long)SHERIFF_ID)))
    {
        return FALSE;
    }

    sheriffhp = character_get_health(character);

    if (sheriffhp <= 0)
    {
        return 1;
    }
    return FALSE;
}

BOOL game_rules_iam_drunk(Game *game, Command *cmd)
{

    Player *player = NULL;
    char **args = NULL;
    CommandCode cmdc;
    if (!game || !cmd)
    {
        return ERROR;
    }
    if (!(player = game_get_player(game)))
    {
        return FALSE;
    }
    if (!(args = command_get_arg(cmd)))
    {
        return FALSE;
    }
    if ((cmdc = command_get_code(cmd)) != USE)
    {
        return FALSE;
    }
    if (game_get_object_id_from_name(game, args[0]) == WHISKY_ID)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL game_rules_weapon_damage_decrease(Game *game, Command *cmd)
{
    Player *player = NULL;
    Object *object = NULL;
    char **args = NULL;
    CommandCode cmdc;
     if (!game || !cmd)
    {
        return ERROR;
    }  
    if (!game || !cmd)
    {
        return ERROR;
    }
    if (!(player = game_get_player(game)))
    {
        return FALSE;
    }
    if (!(args = command_get_arg(cmd)))
    {
        return FALSE;
    }
    if ((cmdc = command_get_code(cmd)) != ATTACK)
    {
        return FALSE;
    }
    if (!(object = game_get_object(game, game_get_object_id_from_name(game, args[2]))))
    {
        return FALSE;
    }
    if ((object_set_damage(object, object_get_damage(object) - 1) == OK))
    {
        return TRUE;
    }

    return FALSE;
}

BOOL game_rules_game_completed(Game *game, Command *cmd)
{
    Player *player = NULL;
    if (!game || !cmd)
    {
        return ERROR;
    }
    if (!(player = game_get_player(game)))
    {
        return FALSE;
    }
    if (player_get_location(player) == VAULT_ID)
    {
        return TRUE;
    }
    return FALSE;
}

BOOL game_rules_killedNPC(Game *game, Command *cmd)
{
    Player *player = NULL;
    Character *character = NULL;
    char **args = NULL;
    CommandCode cmdc;
     if (!game || !cmd)
    {
        return ERROR;
    }
    if (!(player = game_get_player(game)))
    {
        return FALSE;
    }
    if (!(args = command_get_arg(cmd)))
    {
        return FALSE;
    }
    if ((cmdc = command_get_code(cmd)) != ATTACK)
    {
        return FALSE;
    }
    if (!(character = game_get_character_from_name(game, args[0])))
    {
        return FALSE;
    }
    if (character_get_health(character) <= 0)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL game_rules_heavy_inventory(Game *game, Command *cmd)
{
    Player *player = NULL;
    Inventory *backpack = NULL;

    if (!game || !cmd)
    {
        return ERROR;
    }
    if (!(player = game_get_player(game)))
    {
        return FALSE;
    }
    if (!(backpack = player_get_backpack(player)))
    {
        return FALSE;
    }
    if (inventory_is_full(backpack) == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}
