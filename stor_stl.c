#include "RT.h"

int cheak_the_patren(char *line)
{
    int i = -1;
    int j = 0;

    while (line[++i])
        if ((line[i] == ' ' && ft_isdigit(line[i + 1])) || (line[i] == ' ' && line[i + 1] == '-'))
            ++j;
    return (j == 3);
}

int *find_indxs(char *str)
{
    int *tab = (int *)malloc(sizeof(int) * 3);
    int i = -1;
    int j = -1;
    while (str[++i])
        if ((str[i] == ' ' && ft_isdigit(str[i + 1])) || (str[i] == ' ' && str[i + 1] == '-'))
            tab[++j] = i + 1;
    return (tab);
}

t_point line_to_points(char *line)
{
    t_point vertx;
    int *tab = find_indxs(line);
    vertx.x = atof(&line[tab[0]]);
    vertx.y = atof(&line[tab[1]]);
    vertx.z = atof(&line[tab[2]]);
    free(tab);
    return (vertx);
}

void free_list(t_triangles *head)
{
    t_triangles *temp;

    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int sheak(int l, char *line)
{
    if (ft_strstr(line, "endsolid") != NULL)
        return (2);
    if (l == 1)
        return (ft_strstr(line, "solid") != NULL);
    else if ((l - 2) % 7 == 0)
        return (ft_strstr(line, "facet normal") != NULL && cheak_the_patren(line));
    else if ((l - 3) % 7 == 0)
        return (ft_strstr(line, "outer loop") != NULL);
    else if ((l - 4) % 7 == 0 || (l - 5) % 7 == 0 || (l - 6) % 7 == 0)
        return (ft_strstr(line, "vertex") != NULL && cheak_the_patren(line));
    else if (l % 7 == 0)
        return (ft_strstr(line, "endloop") != NULL);
    else if ((l - 1) % 7 == 0)
        return (ft_strstr(line, "endfacet") != NULL);
    return (0);
}

t_triangles *stock_triangles(int fd)
{
    t_triangles *head = (t_triangles *)malloc(sizeof(t_triangles));
    t_triangles *temp = head;
    char *line;
    int l = 0;
    int k = 0;

    head->ver = (t_point *)malloc(sizeof(t_point) * 3);
    while (get_next_line(fd, &line))
    {
        l++;
        if (sheak(l, line) == 0) // to add if sheak = 2 free the list
            break;
        if ((l - 2) % 7 == 0 && ft_strstr(line, "facet normal") != NULL)
            head->normal = line_to_points(line);
        if ((l - 4) % 7 == 0 || (l - 5) % 7 == 0 || (l - 6) % 7 == 0)
            head->ver[k++] = line_to_points(line);
        if (l % 7 == 0 && ft_strstr(line, "endloop") != NULL)
        {
            k = 0;
            head->next = (t_triangles *)malloc(sizeof(t_triangles));
            head->next->ver = (t_point *)malloc(sizeof(t_point) * 3);
            head = head->next;
        }
        free(line);
    }
    head->next = NULL;
    return (temp);
}