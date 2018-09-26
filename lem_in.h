#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include <stdio.h>
#include "libft/libft.h"

typedef struct      s_ant
{
    int             num;
    char            *pos;
    struct s_ant    *next;
    struct s_ant    *prev;
}                   t_ant;


typedef struct  s_room
{
    char        *name;
    int         x;
    int         y;
    int         isfull;
    char        **link_with;

    struct s_room *next;
    struct s_room *prev;
}               t_room;

typedef struct  s_lemin
{
    int         ants;
    int 		num_rooms;
    t_room      *start;
    t_room      *end;
    t_room      *rooms;
}               t_lemin;


#endif //LEM_IN_LEM_IN_H