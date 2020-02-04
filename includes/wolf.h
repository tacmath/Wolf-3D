/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 19:13:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 18:10:56 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include "mlx.h"
# include "lempxdef.h"
# include <math.h>
# include <stdlib.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

# define EPSILON 0.00000000000001

# define SCREEN_X 1920
# define SCREEN_Y 1080
# define PACK_NAME_W 512
# define PACK_NAME_H 100
# define SELECT_ZONE_W 800
# define SELECT_ZONE_H 600
# define RATIO 0.5625
# define NB_THREAD 4
# define TEXTURE_SIZE 512

# define EMPTY 0
# define STONE1 1
# define STONE2 2
# define STONE_FLAG 3
# define STONE_HITLER 4
# define BLUE_CELL1 5
# define STONE_EAGLE 6
# define BLUE_CELL2 7
# define BLUE_STONE1 8
# define BLUE_STONE2 9
# define WOOD_PAINT1 10
# define WOOD_PAINT2 11
# define WOOD 12
# define ELEVATOR_OU1 13
# define ACHTUNG 14
# define METAL1 15
# define DAY 16
# define NIGHT 17
# define RED_BRICK 18
# define RED_BRICK_NAZI 19
# define SKULL 20
# define RED_BRICK_NAZI2 21
# define ELEVATOR_IN1_1 33
# define NB_TEXT 13

# ifdef __APPLE__
#  define UP_KEY 13
#  define DOWN_KEY 1
#  define LEFT_KEY 0
#  define RIGHT_KEY 2
#  define TURNL_KEY 12
#  define TURNR_KEY 14
#  define SPACE_KEY 49
#  define SHIFT_KEY 257
#  define ESCAPE_KEY 53
#  define OS 0
# else
#  define UP_KEY 'z'
#  define DOWN_KEY 's'
#  define LEFT_KEY 'q'
#  define RIGHT_KEY 'd'
#  define TURNL_KEY 'a'
#  define TURNR_KEY 'e'
#  define SPACE_KEY 32
#  define SHIFT_KEY 65505
#  define ESCAPE_KEY 65307
# define OS 1
# endif

#  define RIGHT_CLICK 1

#  define FORWARD	0
#  define BACKWARD	1
#  define LOOK_R	2
#  define LOOK_L	3
#  define SPRINGT	4
#  define MOVE_L 5
#  define MOVE_R 6

#  define RUNING	0
#  define MENU		1
#  define CONTROLS	2
#  define PACK		3


#  define BUTTON_MENU	4
#  define BUTTON_CONTROLS 6

# define TEXT_PACK_DIR	"texture_packs/"

struct						s_point
{
	int						x;
	int						y;
};

typedef struct s_point		t_point;

struct						s_len
{
	int						w;
	int						h;
};

typedef struct s_len		t_len;

struct						s_info
{
	int		nb;
	char	*file;
	t_len	len;
};

typedef struct s_info		t_info;

struct						s_texture
{
	int		nb_textures;
	char	*textures;
	t_len	texture_size;
};

typedef struct s_texture		t_texture;

struct						s_sprite
{
	int		nb_sprites;
	char	*sprites;
	t_len	sprite_size;
};

typedef struct s_sprite		t_sprite;

struct						s_button_pack
{
	char	*buttons;
	t_len	button_size;
};

typedef struct s_button_pack		t_button_pack;

struct						s_background
{
	char	*file;
	int		color;
};

typedef struct s_background		t_background;


struct						s_menu_info
{
	char					*menu;
	t_background			background;
	t_len					menu_size;
};

typedef struct s_menu_info		t_menu_info;

struct						s_pack
{
	char			*name;
	char			*image;
	char			*skybox;
	int			roof;
	int			floor;
	t_texture		texture;
	t_sprite		sprite;
	t_button_pack		button;
	t_menu_info		menu;
};

typedef struct s_pack		t_pack;

struct						s_block
{
	char					type;
	char					interaction;
};

typedef struct s_block				t_block;

struct						s_image
{
	void *img;
	int	*data;
	int w;
	int h;
};

typedef struct s_image		t_image;

struct						s_rect
{
	int x;
	int y;
	int w;
	int h;
};

typedef struct s_rect		t_rect;

struct						s_map
{
	t_block					**map;	//Okay, here we have a 2D map with a char defining what there's in this case plus another for interactions (like a door closed or opened) //malloced // but we still need to define interactions mechanism
	t_point					map_size;
	char					*pack;
};

typedef struct s_map		t_map;

struct						s_test
{
	int	*text_c;
	int	height;
	int 	offset;
	double	delta;
};

typedef struct s_test		t_test;

struct						s_mlx_struct
{
	void					*mlx_ptr;
	void					*win_ptr;
	void					*img;
	int						*img_data;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
	int						nb_pxl;
};

typedef struct s_mlx_struct	t_mlx_struct;

struct						s_vector2
{
	double					x;
	double					y;
};

typedef struct s_vector2	t_vector2;

struct						s_button
{
	int x;
	int y;
	int w;
	int h;
	void (*function)();
};

typedef struct s_button	t_button;

struct						s_buttons
{
	t_button				menu[BUTTON_MENU];
	t_button				controls[BUTTON_CONTROLS];
	char					button_pressed;
};

typedef struct s_buttons	t_buttons;

struct						s_menu_pack
{
	t_len				name_size;
	int				chosen_pack;
	int 				**name;
	int				nb;
	int				nb_start;
	int 				nb_max;
	int				start;
	int				delta;
};

typedef struct s_menu_pack	t_menu_pack;

struct						s_menu
{
	t_menu_pack				pack;
	t_len					menu_size;
	unsigned int			*menu[4];
	int						background_color;
	unsigned int			*background;
	t_len					button_size;
	unsigned int			*button[5][2];
};

typedef struct s_menu	t_menu;

struct						s_wolf
{
	pthread_t				thr[NB_THREAD];
	t_map					*map;
	t_test					test[SCREEN_X];
	t_mlx_struct			*ml;
	char					*path;
	t_vector2				pos;//whereami?
	t_vector2				dir;//where do i look?
	double					dir_angle;
	char					change;//do we need to re-render the scene?
//	char					shift;//does the shift key pressed?
	t_pack					*packs;		//changer plus tard si besoin
	int						stamina;
	unsigned char			springt;
	int						offset;
	int					roof;
	int					floor;
	t_len					texture_size;
	char					nb_textures;
	unsigned int			****textures;
	t_len					sprites_size;
	char					nb_sprites;
	unsigned int			***sprites;
	t_len					skybox_size;
	unsigned int			*skybox;
	t_menu					menu;
	t_point					mouse_pos;
	char					key[7];
	int						key_used[7];
	char					get_key;
	t_buttons				button;
	char					mode;
	double					fov;
};

typedef struct s_wolf		t_wolf;

struct						s_intersection
{
	t_point					hit;
	t_vector2				exact_hit;
	int					text_col;
	char					block;
	char					side;
	double					dist;
};

typedef struct s_intersection	t_intersection;

struct						s_thread_data
{
	t_wolf					*wolf;
	int					strt;
	double					angle;
	t_vector2				dir;
	double					delta_angle;
};

typedef struct s_thread_data			t_thread_data;

void	init_button(t_wolf *wolf);
char	*get_str(char *str);
char	*jump_space(char *str);
void	print_control_button(t_wolf *wolf);
void	print_menu_button(t_wolf *wolf);
void	print_pack(t_wolf *wolf);
void	print_pack_return(t_wolf *wolf);

/*
 ** free.c
 */

void    free_data(t_wolf *wolf);
void    free_wolf(t_wolf *wolf);


/*
 ** get_pack_info.c
 */

int        get_all_packs(t_wolf *wolf);
int get_info(int fd, char **line, t_info *info);

/*
 ** utils.c
 */

char *jump_space(char *str);
int error_msg(char *error);
int        ft_map_realloc(t_map *map, char *str, t_vector2 *pos);
int    remove_comment(char *line);
t_block        *ft_get_nb(t_map *map, char *str, t_vector2 *pos);

/*
 ** utils2.c
 */

char *get_str(char *str);
int get_nbr(char *str);
int get_nbr_hex(char *str);


/*
 ** utils3.c
 */

int  free_pack(t_pack *pack);
int add_path_to_file(char *path, char **file);
int check_file(char *file, char *type);
char *ft_super_join(int nb_arg, ...);

/*
 ** utils4.c
 */

int packs_realloc(t_wolf *wolf, t_pack pack);
int pack_name_cmp(void *s1, void *s2);
void        ft_quicksort(void *tab, int len,
                         int type_size, int (*cmp)(void*, void*));
int get_packs_len(t_pack *packs);

/*
 ** input.c
 */

int        ft_get_map(t_wolf *wolf, char *file);

/*
 ** init.c
 */

void init_key(t_wolf *wolf);
int init_mlx(t_mlx_struct *ml);
int load_pack(t_wolf *wolf, t_pack pack);

/*
 ** controls.c
 */

void use_key(t_wolf *wolf);

/*
** point.c
*/

t_point						init_point(int x, int y);

/*
** vector.c
*/

t_vector2					init_vector2(double x, double y);
t_vector2					vector2_scalar(t_vector2 u, t_vector2 v);
t_vector2					vector2_sub(t_vector2 u, t_vector2 v);
t_vector2					vector2_add(t_vector2 u, t_vector2 v);
t_vector2					vector2_lambda_mult(double l, t_vector2 u);

/*
** vector2.c
*/

double						vector2_norm(t_vector2 u);
void						vector2_normalize(t_vector2 *u);
t_vector2					vector2_ortho_cw(t_vector2 u);
t_vector2					vector2_ortho_ccw(t_vector2 u);

/*
** rotate.c
*/

void						vector2_rotate(t_vector2 *u, double th);

/*
** fast_dda.c
*/

t_intersection					fast_dda(t_vector2 dir, t_vector2 pos, t_map *map);

/*
**  raycaster.c
*/
void						raycaster_col(t_wolf *wolf, int x, double angle, t_vector2 dir_ray);
int						col_thread(void *dt);
void						draw_all_screen(t_wolf *wolf);
void 						test_draw_no_par(t_wolf *wolf);


/*
 ** menu.c
 */

void print_menu(t_wolf *wolf);
void print_button(t_wolf *wolf, t_button button, unsigned int *image);
void fill_menu_background(t_wolf *wolf, int menu);

/*
 ** menu_control.c
 */

void print_control(t_wolf *wolf);

/*
 ** menu_pack.c
 */

void print_pack_return(t_wolf *wolf);
void        check_pack_button(t_wolf *wolf, int x, int y);
void print_pack(t_wolf *wolf);
void print_pack_button(t_wolf *wolf);

/*
** event.c
*/

int								ft_destroy(t_wolf *wolf);
void							free_wolf(t_wolf *wolf);
void							print_control(t_wolf *wolf);
void							print_menu(t_wolf *wolf);
int								deal_motion(int x, int y, t_wolf *wolf);

/*
 ** key_event.c
 */

int                                deal_key_up(int key, t_wolf *wolf);
int                                deal_key_down(int key, t_wolf *wolf);

/*
 ** button.c
 */

int                                deal_button(int button, int x, int y, t_wolf *wolf);
int                                deal_button_release(int button, int x, int y, t_wolf *wolf);

/*
 ** get_pack_check.c
 */

int check_texture(t_pack *pack, t_info info);
int check_sprite(t_pack *pack, t_info info);
int check_button_info(t_pack *pack, t_info info);
int check_menu(t_pack *pack, t_info info);

/*
 ** get_pack_check2.c
 */

int check_pack(char *path, t_pack *pack);
int check_line(int fd, char *line, t_pack *pack);
int check_head(char *line, t_pack *pack);


#endif
