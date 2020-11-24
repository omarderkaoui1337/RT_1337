#include "RT.h"

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

    box = intialize_box();
    while (list)
    {
        box.x_max = fmax(box.x_max, fmax(fmax(list->ver[0].x, list->ver[1].x), list->ver[2].x));
        box.x_min = fmin(box.x_min, fmin(fmin(list->ver[0].x, list->ver[1].x), list->ver[2].x));
        box.y_max = fmax(box.y_max, fmax(fmax(list->ver[0].y, list->ver[1].y), list->ver[2].y));
        box.y_min = fmin(box.y_min, fmin(fmin(list->ver[0].y, list->ver[1].y), list->ver[2].y));
        box.z_max = fmax(box.z_max, fmax(fmax(list->ver[0].z, list->ver[1].z), list->ver[2].z));
        box.z_min = fmin(box.z_min, fmin(fmin(list->ver[0].z, list->ver[1].z), list->ver[2].z));
        list = list->next;
    }
    return (box);
}