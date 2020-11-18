#include "RT.h"

double         rt_intersction(t_triangles *triangle, t_ray ray)
{
    t_vector e1 = vec_sub(triangle->ver[1],triangle->ver[0]);
    t_vector e2 = vec_sub(triangle->ver[2],triangle->ver[0]);
    t_vector p = vec_cross(ray.dir,e2);
    double a = vec_dot(e1,p);

    if (a  > -0.001 && a < 0.001)
        return (MAX);
    double f = 1/a;
    t_vector s = vec_sub(ray.origin, triangle->ver[0]);
    double u = f * vec_dot(s,p);
    if (u < 0.0 || u > 1.0)
        return (MAX);
    t_vector q = vec_cross(s,e1);
    float    v = f * vec_dot(ray.dir,p);
    if (v < 0.0 || u + v > 1.0)
        return (MAX);
    double t = f * vec_dot(e2,q); 
    return (t);
}

int fequal(float a, float b)
{
 return fabs(a-b) < 0.0001;
}

t_triangles     *find_closest(t_triangles *head, t_ray ray)
{
    t_triangles*    triangle = (t_triangles*)malloc(sizeof(t_triangles));
    triangle->t = MAX;
    double          t = MAX;
    double          tmp;
    int i = 0;

    while (head != NULL)
    {
        tmp = rt_intersction(head, ray);
        head->t = tmp;
        if (head->t < t)
        {
            triangle = head;
            t = head->t;
        }
        head = head->next;
    }
    if (triangle->t == MAX)
        return (NULL);
    return (triangle);
}

void		draw(t_mlx *mlx, t_camera c, t_triangles *triangles)
{
	int i,j;
	t_ray		ray;
    t_triangles *one;

	i = -1;   
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
            ray = generate_ray(&c,i,j);
            one = find_closest(triangles,ray);
            if (one == NULL)
            {
                ft_mlx_pixel_put(mlx, i, j, 0x000000);
                continue;
            }
			ft_mlx_pixel_put(mlx, i, j, 0xff);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
