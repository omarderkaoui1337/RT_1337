#include "RT.h"
double MAX = 1000000.0;

void print_the_data(t_triangles *tst)
{
	while (tst)
		{
			printf("normal = [%f] [%f] [%f]\n",tst->normal.x,tst->normal.y,tst->normal.z);
			printf("-------->ver[0] = [%f] [%f] [%f]\n",tst->ver[0].x,tst->ver[0].y,tst->ver[0].z);
			printf("-------->ver[1] = [%f] [%f] [%f]\n",tst->ver[1].x,tst->ver[1].y,tst->ver[1].z);
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

t_triangles* copylist(t_triangles* head)
{
    t_triangles* current = head;
    t_triangles *copie ,*head_copie;

	if (head == NULL)
		return NULL;

// Part 2 - the head element
	copie = (t_triangles *)malloc(sizeof(t_triangles));
	copie->ver = (t_point *)malloc(sizeof(t_point)*3);
	copie->normal = head->normal;
	copie->ver[0] = head->ver[0];
	copie->ver[1] = head->ver[1];
	copie->ver[2] = head->ver[2];
// Part 3 - the rest of the list
	head_copie = copie;
	head = head->next;
	while(head != NULL)
	{
    	copie->next =(t_triangles *)malloc(sizeof(t_triangles));
		copie->next->ver = (t_point *)malloc(sizeof(t_point) * 3);
    	copie = copie->next;
    	copie->ver[0] = head->ver[0];
		copie->ver[1] = head->ver[1];
		copie->ver[2] = head->ver[2];
    	head = head->next;
	}
	copie->next = NULL; 
	return(head_copie);
}

int main(int ac, char **arv)
{
	t_everything ever;
	ever.mlx = (t_mlx*)malloc(sizeof(t_mlx));
    if (ac == 2)
	{
		ft_mlx_setup(ever.mlx);
		t_box		box;
		int 		fd;
		

		pthread_t thread1, thread2, thread3, thread4;
		fd = open(arv[1], O_RDONLY);
		ever.triangles0 = stock_triangles(fd);
		ever.triangles0 = removeLastNode(ever.triangles0);

		box = find_box(ever.triangles0);
		ever.cam = creat_camera(box);

		ever.triangles1 = copylist(ever.triangles0);
		ever.triangles2 = copylist(ever.triangles0);
		ever.triangles3 = copylist(ever.triangles0);


		pthread_create(&thread1, NULL, rt1, &ever);
		pthread_create(&thread2, NULL, rt2, &ever);
		pthread_create(&thread3, NULL, rt3, &ever);
		pthread_create(&thread4, NULL, rt4, &ever);
		
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);
		pthread_join(thread4, NULL);
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