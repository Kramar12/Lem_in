#include "lem_in.h"

// ищет комнату по имени в главной структуре и возвращает комнату если нашёл, в другом случае ноль
t_room		*get_room_by_name(t_lemin *lemin, char *name)
{
	t_room	*temp;
	
	if (!lemin || !name || !lemin->rooms)
		return (NULL);
	while (lemin->rooms->prev)
		lemin->rooms = lemin->rooms->prev;
	temp = lemin->rooms;
	while (lemin->rooms)
	{
		if (!ft_strcmp(lemin->rooms->name, name))
			return (lemin->rooms);
		lemin->rooms = lemin->rooms->next;
	}
	lemin->rooms = temp;
	return (NULL);
}

t_room		*get_room_by_num(t_lemin *lemin, int num)
{
	t_room	*temp;
	
	if (!lemin || !lemin->rooms || num < 0)
		return (NULL);
	while (lemin->rooms->prev)
		lemin->rooms = lemin->rooms->prev;
	temp = lemin->rooms;
	while (lemin->rooms)
	{
		if (lemin->rooms->num == num)
			return (lemin->rooms);
		lemin->rooms = lemin->rooms->next;
	}
	lemin->rooms = temp;
	return (NULL);
}

// ищет комнату по имени в путе главной структуре и возвращает комнату если нашёл, в другом случае ноль
// функция создана для проверки на повторения в пути
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

// копирует комнату которую мы даем как аргумент, при этом выделяя для неё память
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
	ret->isvisited = room->isvisited;
	ret->num = room->num;
	return(ret);
}

//
t_room 		*get_con_start(t_lemin *lemin, int num, int *j)
{
	while(*j < lemin->num_rooms)
	{
		if (lemin->mat[num][*j])
		{
			return (cp_room(get_room_by_num(lemin, *j)));
		}
		(*j)++;
	}
	return (NULL);
}

// кидает комнату в продолжение пути
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

// isvisited
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
	while ((lemin->way->rooms->num != lemin->end->num) && kata)
		kata = concat_way(lemin, get_con_start(lemin, lemin->way->rooms->num, &i));
	concat_way(lemin, cp_room(lemin->end));
}