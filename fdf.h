#ifndef FDF_H
# define FDF_H

# define MAX(x, y) (x >= y) ? x : y
# define MIN(x, y) (x <= y) ? x : y
# define ABS(x) (x < 0) ? -x : x

typedef struct s_point
{
    int x;
    int y;
    int z;
}   t_point;

typedef struct s_fdf
{
    t_point a;
    t_point b;
}   t_fdf;

#endif