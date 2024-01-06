#ifndef FDF_H
# define FDF_H

# define ABS(x) (x < 0) ? -x : x
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_KEY 126
# define DOWN_KEY 125
# define PLUS_KEY 24
# define MINUS_KEY 27
# define ESC_KEY 53
# define LEFT_BRACKET_KEY 33
# define RIGHT_BRACKET_KEY 30
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define Q_KEY 12
# define E_KEY 14
# define I_KEY 34
# define C_KEY 8
# define O_KEY 31
# define Z_KEY 6
# define X_KEY 7
# define R_KEY 15
# define G_KEY 5
# define B_KEY 11
# define T_KEY 17
# define SPACE_KEY 49
# define ONE_KEY 18
# define TWO_KEY 19
# define THREE_KEY 20
# define FOUR_KEY 21
# define FIVE_KEY 23
# define SIX_KEY 22
# define SEVEN_KEY 26
# define EIGHT_KEY 28
# define NINE_KEY 25
# define ZERO_KEY 29
# define BACKSLASH_KEY 42
# define ENTER_KEY 36

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
    double  angle;
    double  angle_x;
    double  angle_y;
    double  angle_z;
    int     projection;
    int     palette_idx;
    int     palette_type;
    int     palette_sign;
    int     palette_ori[10];
    int     palette_update[10];
    int     print_flat;
    int     print_alt;
    t_point a;
    t_point b;
    t_img   img;
}   t_fdf;

#endif