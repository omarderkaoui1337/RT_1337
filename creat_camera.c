#include "RT.h"

t_cube creat_cube(t_box box,double k)
{
    t_cube cube;
    t_point c;

    cube.a = (t_point) {box.x_min, box.y_min, box.z_min};
    cube.b = (t_point) {box.x_min, box.y_max, box.z_min};
    cube.c = (t_point) {box.x_max, box.y_max, box.z_min};
    cube.d = (t_point) {box.x_max, box.y_min, box.z_min};
    cube.e = (t_point) {box.x_min, box.y_min, box.z_max};
    cube.f = (t_point) {box.x_min, box.y_max, box.z_max};
    cube.g = (t_point) {box.x_max, box.y_max, box.z_max};
    cube.h = (t_point) {box.x_max, box.y_min, box.z_max};
    c = vec_sum(cube.a ,vec_kscale(0.5,vec_sum(vec_sub(cube.e,cube.a),vec_sum(vec_sub(cube.b,cube.a), vec_sub(cube.d, cube.a)))));
    cube.a = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.a,c))));
    cube.b = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.b,c))));
    cube.c = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.c,c))));
    cube.d = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.d,c))));
    cube.e = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.e,c))));
    cube.f = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.f,c))));
    cube.g = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.g,c))));
    cube.h = vec_sum(c, vec_kscale(get_dist(cube.d,cube.a)*k, vec_norm(vec_sub(cube.h,c))));
    return (cube);
}

t_point creat_look_at(t_cube cube)
{
    t_point at;
    
    at = vec_sum(cube.a,vec_kscale(0.5 ,vec_sum(vec_sub(cube.b,cube.a),vec_sub(cube.d,cube.a))));
    return (at);
}

t_point creat_look_from(t_cube cube, t_point at)
{
    t_point eye;
    t_vector dir;

    double dist = get_dist(cube.e,cube.a);
    dir = vec_cross(vec_sub(cube.b, cube.a),vec_sub(cube.d, cube.a));
    eye = vec_sum(at, vec_kscale(1, dir));
    return(eye);
}

t_camera creat_camera(t_box box)
{
    t_camera camera;
    t_cube cube;
    
    
    cube = creat_cube(box,1);
    camera.up = (t_vector){0.0, 1.0, 0.0};
    camera.look_at = creat_look_at(cube);
    camera.eye = creat_look_from(cube, camera.look_at);
    camera.view_dir = vec_norm(vec_sub(camera.look_at, camera.eye));
	camera.u = vec_norm(vec_cross(camera.view_dir, camera.up));
	camera.u = vec_kscale(-1, camera.u);
	camera.v = vec_norm(vec_cross(camera.u, camera.view_dir));
	camera.v = vec_kscale(-1, camera.v);
    camera.aspect_ratio = (float)WIDTH / (float)HEIGHT;
    camera.h_height = get_dist(cube.d,cube.a);
    camera.h_width = camera.aspect_ratio * camera.h_height;
    return (camera);
}