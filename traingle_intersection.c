#include "RT.h"

double         rt_intersction(t_triangles *triangle, t_ray ray)
{
    t_vector e1 = vec_sub(triangle->vertix[0],triangle->vertix[1]);
    t_vector e2 = vec_sub(triangle->vertix[0],triangle->vertix[1]);
    t_vector p = vec_cross(ray.dir,e2);
    double a = vec_dot(e1,p);

    if (a  > -0.001 && a < 0.001)
        return (DBL_MAX);
    double f = 1/a;
    t_vector s = vec_sub(ray.origin, triangle->vertix[0]);
    double u = f * vec_dot(s,p);
    if (u < 0.0 || u > 1.0)
        return (DBL_MAX);
    t_vector q = vec_cross(s,e1);
    float    v = f * vec_dot(ray.dir,p);
    if (v < 0.0 || u + v > 1.0)
        return (DBL_MAX);
    double t = f * vec_dot(e2,q); 
    return (t);
}

t_triangles     *find_closest(t_triangles *h_triangle, t_ray ray)
{
    t_triangles* triangle= (t_triangles*)malloc(sizeof(t_triangles));

    triangle->t = DBL_MAX;
    while (h_triangle)
    {
        h_triangle->t = rt_intersction(h_triangle, ray);
        if (h_triangle->t < triangle->t)
            triangle = h_triangle;
        h_triangle = h_triangle->next;
    }
    if (triangle->t == DBL_MAX)
        return (NULL);
    return (triangle);
}



void		draw(t_mlx *mlx, t_camera c, t_triangles *triangles)
{
	int i,j;
	t_ray		ray;
	int			k;
    t_triangles *one;

	k = 0;
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
                ft_mlx_pixel_put(mlx, i, j, 0);
                continue;
            }
			ft_mlx_pixel_put(mlx, i, j, 0xff0000);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}