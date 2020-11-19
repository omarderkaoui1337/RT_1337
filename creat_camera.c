#include "RT.h"

t_cube creat_cube(t_box box,double k)
{
    t_cube cube;
    t_point c;

    c = (t_point) {4*box.x_min + 4*box.x_max, 4*box.y_min + 4*box.y_max, 4*box.z_min + 4*box.z_max};
    cube.a = (t_point) {box.x_min, box.y_min, box.z_min};
    cube.a = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.a,c))));
    cube.b = (t_point) {box.x_min, box.y_max, box.z_min};
    cube.b = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.b,c))));
    cube.c = (t_point) {box.x_max, box.y_max, box.z_min};
    cube.c = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.c,c))));
    cube.d = (t_point) {box.x_max, box.y_min, box.z_min};
    cube.d = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.d,c))));
    cube.e = (t_point) {box.x_min, box.y_min, box.z_max};
    cube.e = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.e,c))));
    cube.f = (t_point) {box.x_min, box.y_max, box.z_max};
    cube.f = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.f,c))));
    cube.g = (t_point) {box.x_max, box.y_min, box.z_max};
    cube.g = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.g,c))));
    cube.h = (t_point) {box.x_max, box.y_max, box.z_max};
    cube.h = vec_sum(c, vec_kscale(k, vec_norm(vec_sub(cube.h,c))));
    return (cube);
}

t_point creat_look_at(t_cube cube)
{
    t_point at;
    
    at = vec_sum(cube.a,vec_kscale(0.5,vec_sum(vec_norm(vec_sub(cube.d, cube.a)),vec_norm(vec_sub(cube.b, cube.a)))));
    
    return (at);
}

t_point creat_look_from(t_cube cube, t_point at)
{
    t_point eye;
    t_vector dir;
    dir = vec_norm(vec_cross(vec_sub(cube.d, cube.a),vec_sub(at, cube.a)));
    eye = vec_sum(at, vec_kscale(1, dir));
    return(eye);
}

t_camera creat_camera(t_box box)
{
    t_camera camera;
    t_cube cube;
    //float dist = 1;
    
    cube = creat_cube(box,30);
    camera.up = (t_vector){0.0, 1.0, 0.0};
    camera.look_at = creat_look_at(cube);
    camera.eye = creat_look_from(cube, camera.look_at);
    camera.view_dir = vec_norm(vec_sub(camera.look_at, camera.eye));
	camera.u = vec_norm(vec_cross(camera.view_dir, camera.up));
	camera.u = vec_kscale(-1, camera.u);
	camera.v = vec_norm(vec_cross(camera.u, camera.view_dir));
	camera.v = vec_kscale(-1, camera.v);
	/*camera.h_height = tan(camera.fov / 2.0) * 2.0 * dist;
	camera.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	camera.h_width = camera.aspect_ratio * camera.h_height;*/
    camera.h_height = get_dist(cube.d,cube.a);
    camera.h_width = get_dist(cube.b,cube.a);
    camera.fov = DEG_TO_RAD(60);
    return (camera);
}