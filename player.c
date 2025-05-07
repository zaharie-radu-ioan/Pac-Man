#include "map.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


int process_input()
{
    char input = get_input();

    int new_x = player_x;
    int new_y = player_y;

    if (input == 'q')
        return 0;
    else if (input == 'w')
        new_y--;
    else if (input == 's')
        new_y++;
    else if (input == 'a')
        new_x--;
    else if (input == 'd')
        new_x++;

    char tile = get_tile(new_x, new_y);

    if (tile == '#')
    {
        return 1;
    }

    if (tile == 'E')
    {
        printf("\n Ai fost prins de un inamic! GAME OVER!\n");
        exit(0);
    }

    set_tile(player_x, player_y, '.');
    player_x = new_x;
    player_y = new_y;
    set_tile(player_x, player_y, 'P');

    return 1;
}