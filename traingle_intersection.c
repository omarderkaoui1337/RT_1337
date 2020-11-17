#include "RT.h"

double         rt_intersction(t_triangles *triangle, t_ray ray)
{
    if (triangle ==NULL)
        exit(0);
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

t_triangles     *find_closest(t_triangles *h_triangle, t_ray ray)
{
    t_triangles* triangle;
    double t = MAX;
    h_triangle->t = MAX;
    while (h_triangle)
    {
        h_triangle->t = rt_intersction(h_triangle, ray);
        //printf("h_triangle->t %f\n",h_triangle->t);
        if (h_triangle->t < t)
        {
            triangle = h_triangle;
            t = h_triangle->t;
        } 
        h_triangle = h_triangle->next;
    }
    //printf("triangle -> t %f\n",triangle->t);
    if (triangle->t == MAX)
    {
        exit(0);
        return (NULL);
    }
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
            //printf("ray origine %f %f %f\n",ray.origin.x, ray.origin.y, ray.origin.z);
           // printf("ray dir %f %f %f\n",ray.dir.x, ray.dir.y, ray.dir.z);
            one = find_closest(triangles,ray);
            //printf("one->t = %f\n",one->t);
           /// if (one->t == MAX)
            //{
            //    HER
                //ft_mlx_pixel_put(mlx, i, j, 0x000000);
                //continue;
            //}
			//ft_mlx_pixel_put(mlx, i, j, 0xff);
		}
	}
	//mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}