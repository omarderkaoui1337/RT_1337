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
    float    v = f * vec_dot(ray.dir,q);
    if (v < 0.0 || u + v > 1.0)
        return (MAX);
    double t = f * vec_dot(e2,q); 
    return (t);
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

void *rt1(void *arg)
{
    t_everything *ever = (t_everything *)arg;
	int i,j;
	t_ray		ray;
    t_triangles *one;

	i = -1;   
	while (++i < WIDTH/2)
	{
		j = -1;
		while (++j < (HEIGHT)/2)
		{
            ray = generate_ray(&ever->cam,i,j);
            one = find_closest(ever->triangles0,ray);
            if (one == NULL)
            {
                ft_mlx_pixel_put(ever->mlx, i, j, 0x000000);
                continue;
            }
			ft_mlx_pixel_put(ever->mlx, i, j, 0xff);
		}
	}
	mlx_put_image_to_window(ever->mlx->mlx_ptr,ever->mlx->win_ptr, ever->mlx->img_ptr, 0, 0);
    return (NULL);
}

void *rt2(void *arg)
{
    t_everything *ever = (t_everything *)arg;
	int i,j;
	t_ray		ray;
    t_triangles *one;

	i = (WIDTH/2)-1;   
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < (HEIGHT/2))
		{
            ray = generate_ray(&ever->cam,i,j);
            one = find_closest(ever->triangles1,ray);
            if (one == NULL)
            {
                ft_mlx_pixel_put(ever->mlx, i, j, 0x000000);
                continue;
            }
			ft_mlx_pixel_put(ever->mlx, i, j, 0xff);
		}
	}
	mlx_put_image_to_window(ever->mlx->mlx_ptr,ever->mlx->win_ptr, ever->mlx->img_ptr, 0, 0);
    return (NULL);
}

void *rt3(void *arg)
{
    t_everything *ever = (t_everything *)arg;
	int i,j;
	t_ray		ray;
    t_triangles *one;

	i = -1;   
	while (++i < WIDTH/2)
	{
		j = (HEIGHT/2) -1;
		while (++j < HEIGHT)
		{
            ray = generate_ray(&ever->cam,i,j);
            one = find_closest(ever->triangles2,ray);
            if (one == NULL)
            {
                ft_mlx_pixel_put(ever->mlx, i, j, 0x000000);
                continue;
            }
			ft_mlx_pixel_put(ever->mlx, i, j, 0xff);
		}
	}
	mlx_put_image_to_window(ever->mlx->mlx_ptr,ever->mlx->win_ptr, ever->mlx->img_ptr, 0, 0);
    return (NULL);
}

void *rt4(void *arg)
{
    t_everything *ever = (t_everything *)arg;
	int i,j;
	t_ray		ray;
    t_triangles *one;

	i = WIDTH/2 -1;   
	while (++i < WIDTH)
	{
		j = (HEIGHT/2) -1;
		while (++j < HEIGHT)
		{
            ray = generate_ray(&ever->cam,i,j);
            one = find_closest(ever->triangles3,ray);
            if (one == NULL)
            {
                ft_mlx_pixel_put(ever->mlx, i, j, 0x000000);
                continue;
            }
			ft_mlx_pixel_put(ever->mlx, i, j, 0xff);
		}
	}
	mlx_put_image_to_window(ever->mlx->mlx_ptr,ever->mlx->win_ptr, ever->mlx->img_ptr, 0, 0);
    return (NULL);
}