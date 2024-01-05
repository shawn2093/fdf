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
# define LEFT_BRACKET_KEY 30
# define RIGHT_BRACKET_KEY 33
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define Q_KEY 12
# define E_KEY 14

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
    int     scale_z;
    double  angle_x;
    double  angle_y;
    double  angle_z;
    t_point a;
    t_point b;
    t_img   img;
}   t_fdf;

#endif