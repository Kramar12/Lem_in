#include "lem_in.h"

void 	printss(int **max, int y, int x, int yc, int xc)
{
	int 	i = 0, j = 0;
	if (!max)
		return;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (i == yc && j == xc)
				printf("%s%3d%s",RED,  max[i][j],RESET);
			else
				printf("%3d", max[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int         are_nums(char *s)
{
    if (!s)
        return (-1);
    else
    {
        while (*s)
        {
            if (!(*s >= '0' && *s <= '9'))
                return (0);
            s++;
        }
    }
    return (1);
}

void        fill_mroom(t_lemin *lemin, int code)
{
    char    *line;
    char    **split;
    
    gnl(0, &line);
    split = ft_strsplit(line, ' ', 1);
    if (!split || !(split[0]) || !(split[1]) || !(split[2]))
        return ;
    if (code && !lemin->start)
    {
        lemin->start = (t_room *)malloc(sizeof(t_room));
        lemin->start->name = split[0];
        lemin->start->x = ft_atoi(split[1]);
        lemin->start->y = ft_atoi(split[2]);
        lemin->start->isfull = -1;
        lemin->start->prev = NULL;
        lemin->start->next = NULL;
		lemin->start->link_with = NULL;
		lemin->start->num = lemin->num_rooms++;
    }
    else if (!lemin->end)
    {
        lemin->end = (t_room *)malloc(sizeof(t_room));
        lemin->end->name = split[0];
        lemin->end->x = ft_atoi(split[1]);
        lemin->end->y = ft_atoi(split[2]);
		lemin->end->isfull = -1;
		lemin->end->prev = NULL;
		lemin->end->next = NULL;
		lemin->end->link_with = NULL;
		lemin->end->num = lemin->num_rooms++;
    }
}

int         get_room_num(t_lemin *lemin, char *name)
{
    t_room *temp;
    
    if (!ft_strcmp(name, "2"))
        lemin->end->prev = NULL;
    if (!(temp = get_room_by_name(lemin, name)))
    {
        if (!ft_strcmp(lemin->start->name, name))
            temp = lemin->start;
        else if (!ft_strcmp(lemin->end->name, name))
            temp = lemin->end;
        else
            return (-1);
    }
    return (temp->num);
}

// добавить проверки
void        get_nums_links(t_lemin *lemin, char *line, int *x, int *y)
{
    char *first;
    char *secnd;
    int len;
    
    len = ft_strpos(line, '-');
    secnd = ft_memalloc((size_t)len);
    secnd = ft_strncpy(secnd, line, len);
    first = ft_strdup(ft_strchr(line, '-') + 1);
    *x = get_room_num(lemin, first);
    *y = get_room_num(lemin, secnd);
}

// добавить проверки
void        fill_links(t_lemin *lemin, char *line)
{
    int     i;
    int     x_temp;
    int     y_temp;
    int 	j;
    
    i = 0;
    if (!lemin->mat)
    {
        lemin->mat = (int **) malloc(sizeof(int *) * (lemin->num_rooms + 2));
        while (i < (lemin->num_rooms + 2))
        {
        	j = (lemin->num_rooms) + 2;
            lemin->mat[i] = (int *) malloc(sizeof(int) * (lemin->num_rooms + 2));
            while(j--)
				lemin->mat[i][j] = 0;
            i++;
        }
        printss(lemin->mat, (lemin->num_rooms + 2), (lemin->num_rooms + 2), 0, 0);
    }
    
    get_nums_links(lemin, line, &x_temp, &y_temp);
    if (y_temp == -1 || x_temp == -1)
		return;
    lemin->mat[y_temp][x_temp] = 1;
    lemin->mat[x_temp][y_temp] = 1;
}

void        fill_rooms(t_lemin *lemin, char *line)
{
    char    **split;
    t_room  *temp;
    
    split = ft_strsplit(line, ' ', 1);
    if (!split || !(split[0]) || !(split[1]) || !(split[2]))
        return ;
    if (!lemin->rooms)
    {
        lemin->rooms = (t_room *)malloc(sizeof(t_room));
        lemin->rooms->name = NULL;
        lemin->rooms->prev = NULL;
        lemin->rooms->next = NULL;
    }
    else
    {
        temp = lemin->rooms;
        lemin->rooms = lemin->rooms->next;
        lemin->rooms = (t_room *)malloc(sizeof(t_room));
        lemin->rooms->name = NULL;
        lemin->rooms->prev = temp;
        lemin->rooms->prev->next = lemin->rooms;
    }
    if (!lemin->rooms->name)
    {
        lemin->rooms->name = split[0];
        lemin->rooms->isfull = 0;
        lemin->rooms->link_with = NULL;
        lemin->rooms->x = ft_atoi(split[1]);
        lemin->rooms->y = ft_atoi(split[2]);
        lemin->rooms->next = NULL;
        lemin->rooms->num = lemin->num_rooms++;
    }
}



void 		get_all_ways(t_lemin *lemin)
{
	int 	*arr;
	int 	i;
	int 	ret;
	int 	c;
	
	c = 0;
	ret = 0;
	i = 0;
	arr = (int *)malloc(sizeof(int) * (lemin->num_rooms + 1));
	ft_bzero(arr, ((size_t)lemin->num_rooms + 1));

	while (i < lemin->num_rooms + 1)
	{
		c = 0;
		while (c < lemin->num_rooms)
		{
			arr[i] += lemin->mat[i][c];
			c++;
		}
		i++;
	}
	arr[i] = -1;
//	i = 0;
//	printf("\n");
//	while (arr[i] != -1)
//	{
//		printf("arr[%d] = %d\n", i , arr[i]);
//		i++;
//	}
	i = 0;
	int 	temp;
	
	temp = 0;
	while (arr[i] != -1)
	{
		while (arr[i]--)
		{
			get_ways(lemin);
			print_way(lemin);
		}
		i++;
	}
}

// добавить матрицу смежностей
void        parse_rooms(t_lemin *lemin)
{
    char    *line;
    int     c;
    
    c = 0;
    lemin->ants = 0;
    while (gnl(0, &line))
    {
        if (!ft_strncmp("5", line, 1))
            line = line;
        if (!line || !(*line) || (*line == '\n' && *(line + 1) == '\0'))
            break ;
        else if (*line == '#' && *(line + 1) != '#')
            continue ;
        else if (!lemin->ants && are_nums(line))
            lemin->ants = ft_atoi(line);
        else if (!ft_strcmp((line), "##start") || !ft_strcmp((line), "##end"))
            fill_mroom(lemin, !ft_strcmp((line), "##start") ? 1 : 0);
        else if (*line != '#' && !ft_strchr(line, ' '))
            fill_links(lemin, line);
        else
            fill_rooms(lemin, line);
        ft_strdel(&line);
    }
//    make_mat(lemin);
	printss(lemin->mat, (lemin->num_rooms + 2), (lemin->num_rooms + 2), 0, 0);
    get_all_ways(lemin);
}

int main(void)
{
    char    *line;

    t_lemin     lemin;
//	dup2(open(av[1], O_RDONLY), 0);
    lemin = (t_lemin){0, 0, NULL, NULL, NULL, NULL, NULL};
    parse_rooms(&lemin);
//    gnl(0, &line);


    return 0;
}