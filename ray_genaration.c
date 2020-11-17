#include "RT.h"

t_ray			generate_ray(t_camera *camera, int i, int j)
{
	t_ray ray;
	float deltax;
	float deltay;
	float x;
	float y;

	ray.origin = camera->eye;
	deltax = camera->h_width / WIDTH;
	deltay = camera->h_height / HEIGHT;
	if (i >= 0 && i <= WIDTH / 2)
		x = -(camera->h_width / 2) + i * deltax;
	if (i > WIDTH / 2)
		x = (i - WIDTH / 2) * deltax;
	if (j >= 0 && j <= HEIGHT / 2)
		y = (camera->h_height / 2) - j * deltay;
	if (j > HEIGHT / 2)
		y = -(j - HEIGHT / 2) * deltay;
	ray.dir = vec_norm(vec_sum(vec_sum(vec_sum(vec_sum(
		vec_kscale(x, camera->u), vec_kscale(y, camera->v)),
		camera->view_dir), camera->look_at), vec_kscale(-1, ray.origin)));
	return (ray);
}
