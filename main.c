#include "RT.h"

void print_the_data(t_triangles *tst)
{
	while (tst)
		{
			printf("normal = [%f] [%f] [%f]\n",tst->normal.x,tst->normal.y,tst->normal.z);
			printf("-------->vertix[0] = [%f] [%f] [%f]\n",tst->vertix[0].x,tst->vertix[0].y,tst->vertix[0].z);
			printf("-------->vertix[1] = [%f] [%f] [%f]\n",tst->vertix[1].x,tst->vertix[1].y,tst->vertix[2].z);
			printf("-------->vertix[2] = [%f] [%f] [%f]\n",tst->vertix[2].x,tst->vertix[2].y,tst->vertix[2].z);
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

t_triangles* removeLastNode(t_triangles *head) 
{ 
    if (head == NULL) 
        return NULL; 
    if (head->next == NULL) { 
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
    t_mlx mlx;
	int fd;
    if (ac == 2)
	{
		t_triangles *tst;
		t_box	box;
		t_camera cam;

		fd = open(arv[1], O_RDONLY);
		tst = stock_triangles(fd);
		tst = removeLastNode(tst);
		print_the_data(tst);
		/*box = find_box(tst);
		print_the_box(box);*/
		/*cam = creat_camera(box);
		draw(&mlx, cam, tst);
		ft_mlx_setup(&mlx);*/
	}
	else
	{
		write(1, "\033[0;31mEnter a valid filename\n", 30);
		return (1);
	}
    mlx_hook(mlx.win_ptr, 2, 0, key_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, close_win, &mlx);
    mlx_loop(mlx.mlx_ptr);
    return(0);
}