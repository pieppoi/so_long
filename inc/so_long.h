/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:35:14 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/23 03:40:55 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 50
# define WINDOW_TITLE "So Long Game"
# define BUFFER_SIZE 1024

// Key codes
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Map characters
# define WALL '1'
# define EMPTY '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

// Colors (RGB)
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define PURPLE 0xFF00FF
# define CYAN 0x00FFFF

// Error messages
# define ERR_ARGS "Error\nInvalid number of arguments"
# define ERR_FILE "Error\nCannot open file"
# define ERR_MAP_FORMAT "Error\nInvalid map format"
# define ERR_MAP_RECTANGLE "Error\nMap is not rectangular"
# define ERR_MAP_WALLS "Error\nMap is not surrounded by walls"
# define ERR_MAP_ELEMENTS "Error\nInvalid map elements"
# define ERR_MAP_INVALID "Error\nInvalid map"
# define ERR_MAP_PLAYER "Error\nMap must have exactly one player"
# define ERR_MAP_PLAYER_DUPLICATE "Error\nMap contains duplicate players"
# define ERR_MAP_EXIT "Error\nMap must have exactly one exit"
# define ERR_MAP_EXIT_DUPLICATE "Error\nMap contains duplicate exit characters"
# define ERR_MAP_COLLECTIBLE "Error\nMap must have at least one collectible"
# define ERR_MAP_PATH "Error\nNo valid path to collect all items and reach exit"
# define ERR_MLX_INIT "Error\nFailed to initialize MLX"
# define ERR_WINDOW "Error\nFailed to create window"
# define ERR_IMAGE "Error\nFailed to create image"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_flood_fill
{
	char	**map;
	int		x;
	int		y;
	int		width;
	int		height;
	int		*collectibles;
	int		*exit_found;
}	t_flood_fill;

typedef struct s_scale_params
{
	void	*mlx;
	void	*src_img;
	void	*dst_img;
	int		src_w;
	int		src_h;
	int		dst_w;
	int		dst_h;
}	t_scale_params;

typedef struct s_player
{
	t_point	pos;
	int		moves;
	int		collected;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		players;
}	t_map;

typedef struct s_textures
{
	void	*wall;
	void	*empty;
	void	*collectible;
	void	*exit;
	void	*player;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_textures	textures;
	int			game_over;
	int			win_condition;
}	t_game;

// Game initialization
int		game_init(t_game *game, char *map_file);
void	init_textures(t_game *game);
void	init_player(t_game *game);

// Map parsing
int		parse_map(t_game *game, char *map_file);
int		validate_map(t_game *game);
int		check_map_format(t_game *game);
int		check_map_walls(t_game *game);
int		check_map_elements(t_game *game);
int		check_valid_path(t_game *game);
void	flood_fill(t_flood_fill *ff);

// Player movement
int		handle_keypress(int keycode, t_game *game);
int		move_player(t_game *game, int dx, int dy);
int		is_valid_move(t_game *game, int x, int y);

// Rendering
int		render_game(t_game *game);
void	render_map(t_game *game);
void	render_tile(t_game *game, int x, int y, char tile);
void	render_player(t_game *game);
void	render_texture_with_transparency(t_game *game, void *texture,
			int x, int y);
void	draw_fallback_tile(t_game *game, int x, int y, char tile);
void	draw_fallback_player(t_game *game, int x, int y);

// Events
int		handle_close(t_game *game);
int		game_loop(t_game *game);

// Utilities
void	*ft_malloc(size_t size);
void	ft_free_map(t_game *game);
void	ft_free_array(char **array);
void	ft_free_map_array(char **map, int height);
void	ft_free_textures(t_game *game);
void	ft_error(char *message);
void	ft_cleanup(t_game *game);

// Get next line
char	*get_next_line(int fd);
void	*ft_realloc(void *ptr, size_t size);

// Printf
int		ft_printf(const char *format, ...);

// XPM loading
void	*load_xpm_texture(t_game *game, char *filename);
void	scale_image(t_scale_params *params);

// Texture generation
void	fill_texture(void *img, int color);
void	fill_player_texture(void *img);
void	fill_wall_texture(void *img);
void	fill_collectible_texture(void *img);
void	fill_exit_texture(void *img);

// Simplified texture creation
void	*create_simplified_coin_texture(t_game *game);
void	*create_simplified_door_texture(t_game *game);
void	*create_simplified_empty_texture(t_game *game);

// Map validation functions
int		check_basic_validation(t_game *game);

// Map copy functions
char	**create_map_copy(t_game *game);

// Player finder functions
void	find_player_and_flood(t_game *game, char **copy,
		int *collectibles, int *exit_found);

#endif
