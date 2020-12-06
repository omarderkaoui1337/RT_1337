#include "../RT.h"


int check_cam_ptr()
{
    return (1);
}

int check(int fd)
{
    char *line;
    int l = 1;

    while (get_next_line(fd, &line))
    {
        
        l++;
        free(line);
    }
    return (1);
}