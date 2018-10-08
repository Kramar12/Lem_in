#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H



#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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
	int 		num;
	int 		isvisited;
	int         isfull;
	char        **link_with;
	
	struct s_room *next;
	struct s_room *prev;
}               t_room;

typedef struct		s_way
{
	t_room			*rooms;
	int 			steps;
	struct s_way	*next;
	struct s_way	*prev;
}					t_way;



typedef struct  s_lemin
{
    int         ants;
    int 		num_rooms;
    int 		**mat;
    t_room      *start;
    t_room      *end;
    t_room      *rooms;
    t_way		*way;
}               t_lemin;

void 		get_ways(t_lemin *lemin);
char 		*get_second(char *line, char *s1);
t_room		*get_room_by_name(t_lemin *lemin, char *name);
void        get_nums_links(t_lemin *lemin, char *line, int *x, int *y);
int         get_room_num(t_lemin *lemin, char *name);

/*
 * trash
 */

void	print_way(t_lemin *lemin);

#endif //LEM_IN_LEM_IN_H
