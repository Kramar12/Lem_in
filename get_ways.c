#include "lem_in.h"


t_room		*get_room_by_name(t_lemin *lemin, char *name)
{
	if (!lemin || !name)
		return (NULL);
	while (lemin->rooms->prev)
		lemin->rooms = lemin->rooms->prev;
	while (lemin->rooms)
	{
		if (!ft_strcmp(lemin->rooms->name, name))
			return (lemin->rooms);
		lemin->rooms = lemin->rooms->next;
	}
	return (NULL);
}

t_room		*get_room_by_name_in_way(t_lemin *lemin, char *name)
{
	t_room		*temp;
	
	if (!lemin)
		return (NULL);
	temp = lemin->way->rooms;
	while (lemin->way->rooms->prev)
		lemin->way->rooms = lemin->way->rooms->prev;
	while (lemin->way->rooms)
	{
		if (!ft_strcmp(lemin->way->rooms->name, name))
			return (lemin->way->rooms);
		lemin->way->rooms = lemin->way->rooms->next;
	}
	lemin->way->rooms = temp;
	return (NULL);
}

char 		*get_second(char *line, char *s1)
{
	int 	i;
	
	char 	*temp; // delete
	i = 0;
	if (!line || !s1)
		return (NULL);
	while (line[i] == *s1)
	{
		i++;
		s1++;
	}
	//uncomment belove and delete under comments till return, and delete *temp
//	if (!*s1 && line[i] == '-') // get 2nd
//		return (ft_strsub(line, (unsigned)ft_strpos(line, '-'), (ft_strlen(line) - ft_strpos(line, '-'))));
//	else
//		return (ft_strsub(line, 0, (ft_strlen(line) - (ft_strlen(line) - ft_strpos(line, '-')))));
	
	if (!*s1 && line[i] == '-') // get 2nd
		temp = (ft_strsub(line, ((unsigned)ft_strpos(line, '-') + 1), (ft_strlen(line) - ft_strpos(line, '-'))));
	else
		temp = (ft_strsub(line, 0, (ft_strlen(line) - (ft_strlen(line) - ft_strpos(line, '-')))));
	
	return (temp);
}

t_room 		*cp_room(t_room *room)
{
	t_room	*ret;
	
	if (!room)
		return (NULL);
	ret = (t_room *)malloc(sizeof(t_room));
	ret->name = ft_strdup(room->name);
	ret->isfull = 0;
	ret->next = NULL;
	ret->prev = NULL;
	ret->link_with = NULL;
	ret->x = room->x;
	ret->y = room->y;
	return(ret);
}

t_room 		*get_con_start(t_lemin *lemin, char *name, int *j)
{
	if (!lemin->links)
		exit ((int)write(1, "ERROR\n", 6) * 0 + 1);
	while (lemin->links[*j])
	{
		if (ft_strstr(lemin->links[*j], name) && !get_room_by_name_in_way(lemin, get_second(lemin->links[*j], name)))
		{
//			(*j)++;
			return (cp_room(get_room_by_name(lemin, get_second(lemin->links[(*j)++], name))));
		}
		(*j)++;
	}
	return (NULL);
}

int 		concat_way(t_lemin *lemin, t_room *add)
{
	t_room		*temp;
	
	temp = NULL;
	if (!add || get_room_by_name_in_way(lemin, add->name))
		return (0);
	if (!lemin->way->rooms)
	{
		lemin->way->rooms = add;
		return (1);
	}
	while (lemin->way->rooms)
	{
		temp = lemin->way->rooms;
		lemin->way->rooms = lemin->way->rooms->next;
	}
	lemin->way->rooms = add;
	lemin->way->rooms->prev = temp;
	lemin->way->rooms->prev->next = lemin->way->rooms;
	return (1);
}

void 		get_ways(t_lemin *lemin)
{
	int 	i;
	int 	kata;
	t_way	*temp;
	
	kata = 1;
	i = 0;
	if (!lemin->way)
	{
		lemin->way = (t_way *)malloc(sizeof(t_way));
		lemin->way->steps = 0;
		lemin->way->next = NULL;
		lemin->way->prev = NULL;
	}
	else
	{
		temp = lemin->way;
		lemin->way = lemin->way->next;
		lemin->way = (t_way *)malloc(sizeof(t_way));
		lemin->way->prev = temp;
		lemin->way->prev->next = lemin->way;
	}
	lemin->way->rooms = cp_room(lemin->start);
	while (ft_strcmp(lemin->way->rooms->name, lemin->end->name) && kata)
		kata = concat_way(lemin, get_con_start(lemin, lemin->way->rooms->name, &i));
	concat_way(lemin, cp_room(lemin->end));
}