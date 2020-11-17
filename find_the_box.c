#include "RT.h"

double *min_max(t_triangles *triangle)
{
    double *tab = (double *)malloc(sizeof(double) * 6);

    tab[0] = fmax(fmax(triangle->vertix[0].x, triangle->vertix[1].x), triangle->vertix[2].x);
    tab[1] = fmin(fmin(triangle->vertix[0].x, triangle->vertix[1].x), triangle->vertix[2].x);
    tab[2] = fmax(fmax(triangle->vertix[0].y, triangle->vertix[1].y), triangle->vertix[2].y);
    tab[3] = fmin(fmin(triangle->vertix[0].y, triangle->vertix[1].y), triangle->vertix[2].y);
    tab[4] = fmax(fmax(triangle->vertix[0].z, triangle->vertix[1].z), triangle->vertix[2].z);
    tab[5] = fmin(fmin(triangle->vertix[0].z, triangle->vertix[1].z), triangle->vertix[2].z);
    return (tab);
}

t_box intialize_box()
{
    t_box box;
    box.x_max = DBL_MIN;
    box.x_min = DBL_MAX;
    box.y_max = DBL_MIN;
    box.y_min = DBL_MAX;
    box.z_max = DBL_MIN;
    box.z_min = DBL_MAX;
    return (box);
}

t_box find_box(t_triangles *list)
{
    t_box box;
    double *tab1;

    box = intialize_box();
    while (list)
    {
        tab1 = min_max(list);
        box.x_max = fmax(box.x_max, tab1[0]);
        box.x_min = fmin(box.x_min, tab1[1]);
        box.y_max = fmax(box.x_min, tab1[2]);
        box.y_min = fmin(box.y_min, tab1[3]);
        box.z_max = fmax(box.z_max, tab1[4]);
        box.z_min = fmin(box.z_min, tab1[5]);
        list = list->next;
    }
    return (box);
}