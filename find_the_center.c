#include "RT.h"

t_point center_of_triangle(t_triangles *traingle)
{
    t_point c;

    c.x = (traingle->ver[0].x + traingle->ver[1].x + traingle->ver[2].x)/3;
    c.y = (traingle->ver[0].y + traingle->ver[1].y + traingle->ver[2].y)/3;
    c.z = (traingle->ver[0].z + traingle->ver[1].z + traingle->ver[2].z)/3;
    return (c);
}

t_point find_the_center(t_triangles *tr)
{
    t_point center_mesh = (t_point){0,0,0};;
    t_point center_triangle;
    int x = 0;

    while (tr)
    {
        center_triangle = center_of_triangle(tr);
        center_mesh = vec_sub(center_mesh,center_triangle);
        x++;
        tr = tr->next;
    }
    center_mesh.x = center_mesh.x/x;
    center_mesh.y = center_mesh.y/x;
    center_mesh.z = center_mesh.z/x;
    return (center_mesh);
}