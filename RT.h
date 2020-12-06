#ifndef RT_H
# define RT_H

# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h> 
# include <stdbool.h>
# include <float.h>
#include <pthread.h>

# define HEIGHT			700
# define WIDTH			700

extern double MAX;

# define BLACK			0x212121

#define HER printf("i am her\n");
#define HELLO printf("hello\n");

# define DEG_TO_RAD(X) (X * (M_PI / 180.0));


typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
	int				bpp;
	int				s_l;
	int				en;
	int				x;
	int				y;
}					t_mlx;

typedef struct s_point
{
    double x;
    double y;
    double z;
}               t_point;

typedef struct s_point t_vector	;

typedef struct s_triangles
{
	double	t;
	t_point *ver;
	t_point normal;
	struct s_triangles* next;
}               t_triangles;

typedef struct s_box
{
	double x_max;
	double x_min;
	double y_max;
	double y_min;
	double z_max;
	double z_min;
}				t_box;

typedef struct		s_camera
{
	t_point			eye;
	t_point			look_at;
	t_vector		up;
	t_vector		u;
	t_vector		v;
	t_vector		view_dir;
	t_vector		bottom_left;
	t_vector		x_incv;
	t_vector		y_incv;
	float			aspect_ratio;
	float			fov;
	float			h_width;
	float			h_height;
	float			dist;
}					t_camera;

typedef struct		s_ray
{
	t_point			origin;
	t_vector		dir;
}					t_ray;

typedef struct		s_cube
{
	t_point a;
	t_point b;
	t_point c;
	t_point d;
	t_point e;
	t_point f;
	t_point g;
	t_point h;
	t_point	face_centre1; 
	t_point	face_centre2; 
	t_point	face_centre3; 
	t_point	face_centre4; 
}					t_cube;

typedef	struct		s_rot
{
	int				on;
	int				alpha_x;
	int				alpha_y;
	int				alpha_z;
}					t_rot;

typedef	struct		s_trans
{
	int				on;
	t_vector		vec;
}					t_trans;

typedef struct		s_light_coeffs
{
	float			ks;
	float			kd;
	float			n;
}					t_light_coeffs;

typedef struct		s_object
{
	char			*name;
	int				color;
	t_vector		center;
	t_vector		vec_dir;
	float			radius;
	float			alpha;
	t_light_coeffs	coeffs;
	double			t;
	double			tsh;
	t_rot			rot;
	t_trans			trans;
	float			k;
}					t_object;

typedef struct 		s_everything
{
	t_mlx *mlx;
	t_camera cam;
	t_triangles *triangles0;
	t_triangles *triangles1;
	t_triangles *triangles2;
	t_triangles *triangles3;
}					t_everything;

int					key_press(int keycode, void *param);
int					close_win(void *param);
void	            ft_mlx_setup(t_mlx *mlx);
float				ft_atof(char *str);
t_triangles			*stock_triangles(int fd);
t_box 				find_box(t_triangles *list);

double				vec_dot(t_vector v1, t_vector v2);
t_vector			vec_sub(t_vector v1, t_vector v2);
t_vector			vec_sum(t_vector v1, t_vector v2);
t_vector			vec_kscale(float k, t_vector v);
t_vector			vec_cross(t_vector v1, t_vector v2);
t_vector			vec_norm(t_vector v);
float				get_dist(t_vector point1, t_vector point2);

void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	ft_draw(t_mlx *mlx);
void	set_mlx_hooks(t_mlx *mlx);
void	ft_mlx_setup(t_mlx *mlx);

t_ray			generate_ray(t_camera *camera, int i, int j);
t_camera creat_camera(t_box box);
t_box find_box(t_triangles *list);
t_cube creat_cube(t_box box,double k);
void *rt1(void *arg);
void *rt2(void *arg);
void *rt3(void *arg);
void *rt4(void *arg);

double         rt_intersction(t_triangles *triangle, t_ray ray);
t_ray			generate_ray(t_camera *camera, int i, int j);
t_triangles     *find_closest(t_triangles *h_triangle, t_ray ray);

#endif