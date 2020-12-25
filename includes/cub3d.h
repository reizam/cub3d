/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3d.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kmazier <kmazier@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/12/15 13:03:25 by kmazier		   #+#	#+#			 */
/*   Updated: 2020/12/15 18:01:13 by kmazier		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define W_KEY 119
# define A_KEY 97
# define D_KEY 100
# define S_KEY 115
# define ESC_KEY 65307

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mlx.h"
# include <math.h>

typedef struct  s_sprite
{
	int			 	x;
	int			 	y;
	struct s_sprite *next;
}				   t_sprite;

typedef struct  s_img
{
	char		*img_ptr;
	int		 	*addr;
	int		 	width;
	int		 	height;
	int		 	bits_per_pixel;
	int		 	line_length;
	int		 	endian;
}			   t_img;

typedef struct	s_cub
{
	char		*save_first_image;
	int		 	height;
	int		 	width;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*north_texture;
	char		*sprite_texture;
	int		 	rgb_ground;
	int		 	rgb_roof;
	int		 	spawn_x;
	int		 	spawn_y;
	double	  	dir_x;
	double	  	dir_y;
	double	  	plane_x;
	double	  	plane_y;
	char		*error;
	char		**map;
	t_sprite	*sprite;
}				t_cub;

typedef struct  s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	double  pos_x;
	double  pos_y;
	double  dir_x;
	double  dir_y;
	double  plane_x;
	double  plane_y;
	double  move_speed;
	double  rot_speed;
	char	*addr;
	int	 	bits_per_pixel;
	int	 	line_length;
	int	 	endian;
	int	 	keys[4];
	t_img   textures[5];
	double  *h_buffer;
	t_cub   *cub;
}			   t_vars;

void		ft_draw_pixel_if_not_black(t_vars *vars, int x, int y, int color);
void		ft_sort_sprites(t_sprite **begin, int pos_x, int pos_y);
void		ft_lstclear(t_sprite **lst);
void		ft_lstadd_front(t_sprite **alst, int x, int y);
t_sprite	*ft_create_elem(void);
void		ft_save_image(t_vars *vars, char *file_name);
void		ft_do_controls(t_vars *vars);
int		 	ft_key_release(int keycode, t_vars *vars);
int		 	ft_key_press(int keycode, t_vars *vars);
int		 	ft_check_map_line(char *line);
int		 	ft_check_map(t_cub *cub);
int		 	ft_is_map_char(char c, int just_spawn);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
int		 	ft_strcmp(char *s1, char *s2);
int		 	ft_strncmp(char *s1, char *s2, size_t n);
int		 	ft_check_file_ext(char *file, char *extension);
int			get_next_line(int fd, char **line);
int		 	ft_parse_map(int fd, t_cub *cub);
int			ft_nb_len(int nb);
t_cub	   *ft_parse_exit(t_cub *cub);
int			ft_is_full(t_cub *cub);
int			ft_atoi(char *str);
int		 	ft_parse_rgb(char *line, int id, t_cub *cub);
t_cub	   *ft_parse_cub_file(char *file);
int		 	ft_isnum(char *str);
char		*ft_strjoin(char *s1, char *s2, int n);
int		 	ft_check_rgb(int r, int g, int b);
char		**ft_split(char const *s, char c);
char		*ft_strdup(char *src);
void		ft_open_screen(t_cub *cub);
void		ft_draw_pixel(t_vars *vars, int x, int y, int color);
void		ft_draw_ver_line(t_vars *vars, int x, int start_y, int end_y, int color);
void		ft_screen_exit(t_vars *vars);
int		 	ft_parse_texture(char *line, int id, t_cub *cub);
void		ft_print_error(char *error);
int		 	ft_load_all_texture(t_vars *vars);
void		ft_draw_texture_line(t_vars *vars, t_img img, int x, int k[4]);
void		ft_screen_init_exit(t_vars *vars, int do_exit);
void		ft_draw_wall(t_vars *vars, double **h_buffer);
void		ft_draw_sprite(t_vars *vars, double *h_buffer);
void		ft_draw_roof(t_vars *vars);
void		ft_draw_ground(t_vars *vars);
int			ft_leave_parse_map(char *map);

#endif