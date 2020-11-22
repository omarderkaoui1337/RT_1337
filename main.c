#include "RT.h"

double MAX = 1000000.0;

void print_the_data(t_triangles *tst)
{
	while (tst)
		{
			printf("normal = [%f] [%f] [%f]\n",tst->normal.x,tst->normal.y,tst->normal.z);
			printf("-------->ver[0] = [%f] [%f] [%f]\n",tst->ver[0].x,tst->ver[0].y,tst->ver[0].z);
			printf("-------->ver[1] = [%f] [%f] [%f]\n",tst->ver[1].x,tst->ver[1].y,tst->ver[2].z);
			printf("-------->ver[2] = [%f] [%f] [%f]\n",tst->ver[2].x,tst->ver[2].y,tst->ver[2].z);
			tst = tst->next;
		}
}
void print_the_box(t_box box)
{
	printf("box\n");
	printf("box.x_max %f \n ",box.x_max); 
	printf("box.x_min %f \n ",box.x_min); 
	printf("box.y_max %f \n ",box.y_max); 
	printf("box.y_min %f \n ",box.y_min); 
	printf("box.z_max %f \n ",box.z_max);
	printf("box.z_min %f \n ",box.z_min);
}

void print_the_cube(t_cube cube)
{
	printf("cube a %f %f %f\n", cube.a.x, cube.a.y, cube.a.z);
	printf("cube b %f %f %f\n", cube.b.x, cube.b.y, cube.b.z);
	printf("cube c %f %f %f\n", cube.c.x, cube.c.y, cube.c.z);
	printf("cube d %f %f %f\n", cube.d.x, cube.d.y, cube.d.z);
	printf("cube e %f %f %f\n", cube.e.x, cube.e.y, cube.e.z);
	printf("cube f %f %f %f\n", cube.f.x, cube.f.y, cube.f.z);
	printf("cube g %f %f %f\n", cube.g.x, cube.g.y, cube.g.z);
	printf("cube h %f %f %f\n", cube.h.x, cube.h.y, cube.h.z);
}

void print_the_camera(t_camera camera)
{
	printf("eye %f %f %f\n", camera.eye.x, camera.eye.y, camera.eye.z);
	printf("look_at %f %f %f\n", camera.look_at.x, camera.look_at.y, camera.look_at.z);
	printf("up %f %f %f\n", camera.up.x, camera.up.y, camera.up.z);
	printf("u %f %f %f\n", camera.u.x, camera.u.y, camera.u.z);
	printf("v %f %f %f\n",camera.v.x, camera.v.y, camera.v.z);
	printf("view_dir %f %f %f\n",camera.view_dir.x, camera.view_dir.y, camera.view_dir.z);
	printf("h_width %f \n", camera.h_width);
	printf("h_height %f \n", camera.h_height);
}

t_triangles* removeLastNode(t_triangles *head) 
{ 
    if (head == NULL) 
        return NULL; 
     if (head->next == NULL)
	 { 
        free(head); 
        return NULL; 
    } 
    t_triangles *second_last = head; 
    while (second_last->next->next != NULL) 
        second_last = second_last->next; 
    free(second_last->next); 
    second_last->next = NULL; 
    return head; 
} 

int main(int ac, char **arv)
{
	t_everything ever;
	ever.mlx = (t_mlx*)malloc(sizeof(t_mlx));
	int fd;
    if (ac == 2)
	{
		ft_mlx_setup(ever.mlx);
		t_box	box;

		pthread_t	thread_ID[5];
		void *exit_value0;
		void *exit_value1;
		void *exit_value2;
		void *exit_value3;
		void *exit_value4;
	

		fd = open(arv[1], O_RDONLY);
		ever.triangles = stock_triangles(fd);
		ever.triangles = removeLastNode(ever.triangles);
		box = find_box(ever.triangles);
		ever.cam = creat_camera(box);

		rt1(&ever);
		rt2(&ever);
		rt3(&ever);
		rt4(&ever);

		/*pthread_create(&thread_ID[0], NULL, rt1, &ever);
		pthread_create(&thread_ID[1], NULL, rt2, &ever);
		pthread_create(&thread_ID[2], NULL, rt3, &ever);
		pthread_create(&thread_ID[3], NULL, rt4, &ever);
		
		pthread_join(thread_ID[0], &exit_value0);
		pthread_join(thread_ID[1], &exit_value1);
		pthread_join(thread_ID[2], &exit_value2);
		pthread_join(thread_ID[3], &exit_value3);*/
	}
	else
	{
		write(1, "\033[0;31mEnter a valid filename\n", 30);
		return (1);
	}
    mlx_hook(ever.mlx->win_ptr, 2, 0, key_press, ever.mlx);
	mlx_hook(ever.mlx->win_ptr, 17, 0, close_win, ever.mlx);
    mlx_loop(ever.mlx->mlx_ptr);
    return(0);
}