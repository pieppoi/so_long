/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 06:51:21 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/25 20:14:47 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

# define IMG_HEIGHT			64
# define IMG_WIDTH			64
# define BUFFER_SIZE		1024

# define WALL				'1'
# define FLOOR 				'0'
# define COINS  			'C'
# define PLAYER				'P'
# define MAP_EXIT 		 	'E'

# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

# define KEY_UP  			65362
# define KEY_LEFT  			65361
# define KEY_RIGHT 			65363
# define KEY_DOWN  			65364

# define KEY_ESC  			65307

# define FRONT				1
# define LEFT				2
# define RIGHT				3
# define BACK				4

# define WALL_XPM			"textures/wall.xpm"
# define FLOOR_XPM			"textures/empty.xpm"
# define COINS_XPM			"textures/coin.xpm"
# define PLAYER_FRONT_XPM	"textures/player.xpm"
# define PLAYER_LEFT_XPM	"textures/player.xpm"
# define PLAYER_RIGHT_XPM	"textures/player.xpm"
# define PLAYER_BACK_XPM	"textures/player.xpm"
# define OPEN_EXIT_XPM		"textures/door.xpm"
# define EXIT_CLOSED_XPM	"textures/door.xpm"

# define GREEN				"\033[0;32m"
# define RED 				"\033[1;31m"
# define GREY 				"\033[0;90m"
# define CYAN				"\033[1;96m"
# define RESET 				"\033[0m"

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_position
{
	int	x;
	int	y;
}	t_positon;

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_map
{
	char		**full;
	int			rows;
	int			columns;
	int			coins;
	int			exit;
	int			players;
	t_positon	player;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			movements;
	int			player_sprite;
	t_map		map;
	t_bool		map_alloc;
	t_image		wall;
	t_image		floor;
	t_image		coins;
	t_image		open_exit;
	t_image		exit_closed;
	t_image		player_front;
	t_image		player_left;
	t_image		player_right;
	t_image		player_back;
}	t_game;

typedef struct s_ff
{
	char	**grid;
	int		rows;
	int		cols;
	int		*coins;
}	t_ff;

/* ft_check_map.c */
void	ft_check_map(t_game *game);
void	ft_check_rows(t_game *game);
void	ft_check_columns(t_game *game);
void	ft_count_map_parameters(t_game *game);
void	ft_verify_map_parameters(t_game *game);
void	ft_check_rectangle(t_game *game);

/* ft_path_check.c */
void	ft_check_reachability(t_game *game);

/* ft_close_game.c */
int		ft_victory(t_game *game);
int		ft_close_game(t_game *game);
int		ft_error_msg(char *message, t_game *game);

/* ft_free_memory.c */
void	ft_free_all_allocated_memory(t_game *game);
void	ft_destroy_images(t_game *game);
void	ft_free_map(t_game *game);

/* ft_handle_input.c */
int		ft_handle_input(int keysym, t_game *game);
void	ft_player_move(t_game *game, int new_y, int new_x, int player_sprite);

/* ft_init_game.c */
void	ft_init_vars(t_game *game);
void	ft_init_mlx(t_game *game);
void	ft_init_sprites(t_game *game);
t_image	ft_new_sprite(void *mlx, char *path, t_game *game);

/* ft_init_map.c */
void	ft_check_command_line_arguments(int argc, char **argv, t_game *game);
char	*ft_read_file_content(t_game *game, char *argv);
void	ft_init_map(t_game *game, char *argv);
void	ft_check_for_empty_line(char *map, t_game *game);

/* ft_render_map.c */
int		ft_render_map(t_game *game);
void	ft_identify_sprite(t_game *game, int y, int x);
void	ft_render_player(t_game *game, int y, int x);
void	ft_render_sprite(t_game *game, t_image sprite, int line, int column);

/* ft_utils.c */
char	*ft_strappend(char **s1, const char *s2);

/* get_next_line.c */
char	*get_next_line(int fd);
char	*ft_read_and_stash(int fd, char *stash);
char	*ft_extract_line(char *stash);
char	*ft_update_stash(char *stash);

#endif