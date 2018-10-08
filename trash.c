#include "lem_in.h"

void	print_way(t_lemin *lemin)
{
	if (!lemin || !lemin->way || !lemin->way->rooms)
		return;
	
	while (lemin->way->rooms) {
		printf("%s <- ", lemin->way->rooms->name);
		lemin->way->rooms = lemin->way->rooms->prev;
		if (!lemin || !lemin->way || !lemin->way->rooms)
			break ;
	}
	printf("\n");
}