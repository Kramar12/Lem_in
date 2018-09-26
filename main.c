#include "lem_in.h"

int         is_nums(char *s)
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
    }
    else if (!lemin->end)
    {
        lemin->end = (t_room *)malloc(sizeof(t_room));
        lemin->end->name = split[0];
        lemin->end->x = ft_atoi(split[1]);
        lemin->end->y = ft_atoi(split[2]);
    }
}

void        fill_links(t_lemin *lemin, char *line)
{

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
    }
    if (!lemin->rooms->name)
    {
        lemin->rooms->name = split[0];
        lemin->rooms->isfull = 0;
        lemin->rooms->link_with = NULL;
        lemin->rooms->x = ft_atoi(split[1]);
        lemin->rooms->y = ft_atoi(split[2]);
        lemin->rooms->next = NULL;
        lemin->num_rooms++;
    }
}

void        parse_rooms(t_lemin *lemin)
{
    char    *line;
    int     knife_switch;
    
    lemin->ants = 0;
    while (gnl(0, &line))
    {
        if (!line || (*line == '\n' && *(line + 1) == '\0'))
            break ;
        if (*line == '#' && *(line + 1) != '#')
            continue ;
        if (!lemin->ants && is_nums(line))
            lemin->ants = ft_atoi(line);
        if (!ft_strcmp((line), "##start") || !ft_strcmp((line), "##end"))
            fill_mroom(lemin, !ft_strcmp((line), "##start") ? 1 : 0);
        if (*line != '#' && !ft_strchr(line, ' '))
            fill_links(lemin, line);
        else
            fill_rooms(lemin, line);
    }
}

int main(void)
{
    char    *line;

    t_lemin     lemin;

    lemin = (t_lemin){0, 0, NULL, NULL, NULL};
    parse_rooms(&lemin);
    gnl(0, &line);
    printf("%s", line);

    return 0;
}