#ifndef FDF_H
# define FDF_H

# define MAX(x, y) (x >= y) ? x : y
# define MIN(x, y) (x <= y) ? x : y
# define ABS(x) (x < 0) ? -x : x

# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_KEY 126
# define DOWN_KEY 125
# define PLUS_KEY 24
# define MINUS_KEY 27
# define ESC_KEY 53

typedef struct s_img
{
    void    *mlx_img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
}   t_point;

typedef struct s_bres
{
    int x;
    int y;
    int dx;
    int dy;
    int D;
    int yi;
    int xi;
}   t_bres;

typedef struct s_fdf
{
    void    *win;
    void    *mlx;
    t_point **matrix;
    int     height;
    int     width;
    int     move_x;
    int     move_y;
    int     scale;
    t_point a;
    t_point b;
    t_img   img;
}   t_fdf;

#endif