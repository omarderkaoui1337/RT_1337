//salm
#include "RT.h"

int	key_press(int keycode, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
        exit(0); 
	}
	return (0);
}

int	close_win(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	return (0);
}
