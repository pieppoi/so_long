/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:34:14 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/23 03:56:13 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_error(ERR_MLX_INIT);
		return (0);
	}
	game->win = mlx_new_window(game->mlx,
		game->map.width * TILE_SIZE,
		game->map.height * TILE_SIZE,
		WINDOW_TITLE);
	if (!game->win)
	{
		ft_error(ERR_WINDOW);
		ft_cleanup(game);
		return (0);
	}
	return (1);
}

int	game_init(t_game *game, char *map_file)
{
	ft_memset(game, 0, sizeof(t_game));
	if (!parse_map(game, map_file))
	{
		ft_cleanup(game);
		return (0);
	}
	if (!init_mlx_and_window(game))
		return (0);
	init_textures(game);
	init_player(game);
	return (1);
}

void	init_textures(t_game *game)
{
	game->textures.wall = load_xpm_texture(game, "Resources/wall.xpm");
	game->textures.empty = load_xpm_texture(game, "Resources/empty.xpm");
	game->textures.collectible = load_xpm_texture(game, "Resources/coin.xpm");
	game->textures.exit = load_xpm_texture(game, "Resources/door.xpm");
	game->textures.player = load_xpm_texture(game, "Resources/player.xpm");
	
	if (!game->textures.wall)
	{
		game->textures.wall = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
		fill_wall_texture(game->textures.wall);
	}
	if (!game->textures.empty)
	{
		game->textures.empty = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
		fill_texture(game->textures.empty, WHITE);
	}
	if (!game->textures.collectible)
	{
		game->textures.collectible = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
		fill_collectible_texture(game->textures.collectible);
	}
	if (!game->textures.exit)
	{
		game->textures.exit = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
		fill_exit_texture(game->textures.exit);
	}
	if (!game->textures.player)
	{
		game->textures.player = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
		fill_player_texture(game->textures.player);
	}
}

void	fill_texture(void *img, int color)
{
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		pixel;
	
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
		return;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			if (pixel >= 0 && pixel < size_line * TILE_SIZE)
			{
				*(int*)(data + pixel) = color;
			}
			x++;
		}
		y++;
	}
}

static void	draw_player_background(char *data, int bits_per_pixel,
		int size_line)
{
	int		x;
	int		y;
	int		pixel;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			if (pixel >= 0 && pixel < size_line * TILE_SIZE)
			{
				*(int*)(data + pixel) = 0xFFA500;
			}
			x++;
		}
		y++;
	}
}

static void	draw_player_body(char *data, int bits_per_pixel,
		int size_line)
{
	int		x;
	int		y;
	int		center_x;
	int		center_y;
	int		radius;
	int		pixel;
	int		dx;
	int		dy;
	int		distance;

	center_x = TILE_SIZE / 2;
	center_y = TILE_SIZE / 2;
	radius = TILE_SIZE / 3;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			dx = x - center_x;
			dy = y - center_y;
			distance = dx * dx + dy * dy;
			if (distance <= radius * radius)
			{
				pixel = (y * size_line) + (x * (bits_per_pixel / 8));
				if (pixel >= 0 && pixel < size_line * TILE_SIZE)
				{
					*(int*)(data + pixel) = 0xFF8C00;
				}
			}
			x++;
		}
		y++;
	}
}

static void	draw_player_eyes(char *data, int bits_per_pixel,
		int size_line)
{
	int		x;
	int		y;
	int		center_x;
	int		center_y;
	int		eye_left_x;
	int		eye_right_x;
	int		eye_y;
	int		pixel;

	center_x = TILE_SIZE / 2;
	center_y = TILE_SIZE / 2;
	eye_left_x = center_x - TILE_SIZE / 6;
	eye_right_x = center_x + TILE_SIZE / 6;
	eye_y = center_y - TILE_SIZE / 8;
	y = eye_y - TILE_SIZE / 8;
	while (y <= eye_y + TILE_SIZE / 8)
	{
		x = eye_left_x - 1;
		while (x <= eye_left_x + 1)
		{
			if (x >= 0 && x < TILE_SIZE && y >= 0 && y < TILE_SIZE)
			{
				pixel = (y * size_line) + (x * (bits_per_pixel / 8));
				if (pixel >= 0 && pixel < size_line * TILE_SIZE)
				{
					*(int*)(data + pixel) = BLACK;
				}
			}
			x++;
		}
		x = eye_right_x - 1;
		while (x <= eye_right_x + 1)
		{
			if (x >= 0 && x < TILE_SIZE && y >= 0 && y < TILE_SIZE)
			{
				pixel = (y * size_line) + (x * (bits_per_pixel / 8));
				if (pixel >= 0 && pixel < size_line * TILE_SIZE)
				{
					*(int*)(data + pixel) = BLACK;
				}
			}
			x++;
		}
		y++;
	}
}

void	fill_player_texture(void *img)
{
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
		return;
	draw_player_background(data, bits_per_pixel, size_line);
	draw_player_body(data, bits_per_pixel, size_line);
	draw_player_eyes(data, bits_per_pixel, size_line);
}

void	fill_wall_texture(void *img)
{
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		color;
	int		pixel;
	
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
		return;
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			color = 0x404040;
			if ((x + y) % 8 < 4)
				color = 0x505050;
			if (pixel >= 0 && pixel < size_line * TILE_SIZE)
			{
				*(int*)(data + pixel) = color;
			}
			x++;
		}
		y++;
	}
}

void	fill_collectible_texture(void *img)
{
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		center_x;
	int		center_y;
	int		radius;
	int		pixel;
	int		dx;
	int		dy;
	
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
		return;
	
	center_x = TILE_SIZE / 2;
	center_y = TILE_SIZE / 2;
	radius = TILE_SIZE / 4;
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			if (pixel >= 0 && pixel < size_line * TILE_SIZE)
			{
				*(int*)(data + pixel) = YELLOW;
			}
			x++;
		}
		y++;
	}
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			dx = (x - center_x < 0) ? -(x - center_x) : (x - center_x);
			dy = (y - center_y < 0) ? -(y - center_y) : (y - center_y);
			if (dx + dy <= radius)
			{
				pixel = (y * size_line) + (x * (bits_per_pixel / 8));
				if (pixel >= 0 && pixel < size_line * TILE_SIZE)
				{
					*(int*)(data + pixel) = 0xFFD700;
				}
			}
			x++;
		}
		y++;
	}
}

void	fill_exit_texture(void *img)
{
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		pixel;
	int		color;
	
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
		return;
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			color = GREEN;
			if (x < 4 || x >= TILE_SIZE - 4 || y < 4 || y >= TILE_SIZE - 4)
				color = 0x006400;
			else if (x == TILE_SIZE / 2 && y > TILE_SIZE / 3 && y < TILE_SIZE * 2 / 3)
				color = 0x8B4513;
			if (pixel >= 0 && pixel < size_line * TILE_SIZE)
			{
				*(int*)(data + pixel) = color;
			}
			x++;
		}
		y++;
	}
}

void	*load_xpm_texture(t_game *game, char *filename)
{
	void	*img;
	int		width;
	int		height;
	
	img = mlx_xpm_file_to_image(game->mlx, filename, &width, &height);
	if (!img)
	{
		if (ft_strnstr(filename, "coin.xpm", ft_strlen(filename)))
			return (create_simplified_coin_texture(game));
		else if (ft_strnstr(filename, "door.xpm", ft_strlen(filename)))
			return (create_simplified_door_texture(game));
		else if (ft_strnstr(filename, "empty.xpm", ft_strlen(filename)))
			return (create_simplified_empty_texture(game));
		
		return (NULL);
	}
	
	if (width <= 0 || height <= 0)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	if (width == TILE_SIZE && height == TILE_SIZE)
		return (img);
	
	void	*resized_img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!resized_img)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	t_scale_params params = {
		.mlx = game->mlx,
		.src_img = img,
		.dst_img = resized_img,
		.src_w = width,
		.src_h = height,
		.dst_w = TILE_SIZE,
		.dst_h = TILE_SIZE
	};
	scale_image(&params);
	
	mlx_destroy_image(game->mlx, img);
	
	return (resized_img);
}

static void	copy_pixel_data(char *src_data, char *dst_data,
		t_scale_params *params)
{
	int		x;
	int		y;
	int		src_bpp;
	int		src_sl;
	int		src_endian;
	int		dst_bpp;
	int		dst_sl;
	int		dst_endian;

	mlx_get_data_addr(params->src_img, &src_bpp, &src_sl, &src_endian);
	mlx_get_data_addr(params->dst_img, &dst_bpp, &dst_sl, &dst_endian);
	y = 0;
	while (y < params->dst_h)
	{
		x = 0;
		while (x < params->dst_w)
		{
			scale_single_pixel(src_data, dst_data, params, x, y);
			x++;
		}
		y++;
	}
}

static void	scale_single_pixel(char *src_data, char *dst_data, t_scale_params *params,
		int x, int y)
{
	int				src_x;
	int				src_y;
	int				src_bpp;
	int				src_sl;
	int				src_endian;
	int				dst_bpp;
	int				dst_sl;
	int				dst_endian;
	unsigned int	color;

	mlx_get_data_addr(params->src_img, &src_bpp, &src_sl, &src_endian);
	mlx_get_data_addr(params->dst_img, &dst_bpp, &dst_sl, &dst_endian);
	src_x = (x * params->src_w) / params->dst_w;
	src_y = (y * params->src_h) / params->dst_h;
	if (src_x >= params->src_w)
		src_x = params->src_w - 1;
	if (src_y >= params->src_h)
		src_y = params->src_h - 1;
	if (src_x < 0)
		src_x = 0;
	if (src_y < 0)
		src_y = 0;
	color = *(unsigned int*)(src_data + (src_y * src_sl) +
		(src_x * (src_bpp / 8)));
	if (color == 0x00000000 || color == 0xFF000000 ||
		(color & 0xFF000000) == 0x00000000)
		*(unsigned int*)(dst_data + (y * dst_sl) +
			(x * (dst_bpp / 8))) = 0x00000000;
	else
		*(unsigned int*)(dst_data + (y * dst_sl) +
			(x * (dst_bpp / 8))) = color;
}

void	scale_image(t_scale_params *params)
{
	char	*src_data;
	char	*dst_data;
	int		src_bpp;
	int		src_sl;
	int		src_endian;
	int		dst_bpp;
	int		dst_sl;
	int		dst_endian;

	src_data = mlx_get_data_addr(params->src_img, &src_bpp, &src_sl, &src_endian);
	if (!src_data)
		return;
	dst_data = mlx_get_data_addr(params->dst_img, &dst_bpp, &dst_sl, &dst_endian);
	if (!dst_data)
		return;
	copy_pixel_data(src_data, dst_data, params);
}

void	init_player(t_game *game)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == PLAYER)
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				game->player.moves = 0;
				game->player.collected = 0;
				return;
			}
			x++;
		}
		y++;
	}
}

void	*create_simplified_coin_texture(t_game *game)
{
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		center_x;
	int		center_y;
	int		radius;
	int		pixel;
	int		dx;
	int		dy;
	int		distance;
	
	img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img)
		return (NULL);
	
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	center_x = TILE_SIZE / 2;
	center_y = TILE_SIZE / 2;
	radius = TILE_SIZE / 3;
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			*(int*)(data + pixel) = 0x00000000;
			x++;
		}
		y++;
	}
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			dx = x - center_x;
			dy = y - center_y;
			distance = dx * dx + dy * dy;
			if (distance <= radius * radius)
			{
				pixel = (y * size_line) + (x * (bits_per_pixel / 8));
				*(int*)(data + pixel) = 0xFFD700;
			}
			x++;
		}
		y++;
	}
	
	return (img);
}

void	*create_simplified_door_texture(t_game *game)
{
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		pixel;
	int		color;
	
	img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img)
	{
		return (NULL);
	}
	
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			color = 0x8B4513;
			if (x < 4 || x >= TILE_SIZE - 4 || y < 4 || y >= TILE_SIZE - 4)
				color = 0x654321;
			else if (x == TILE_SIZE / 2 && y > TILE_SIZE / 3 && y < TILE_SIZE * 2 / 3)
				color = 0xCD853F;
			*(int*)(data + pixel) = color;
			x++;
		}
		y++;
	}
	
	return (img);
}

void	*create_simplified_empty_texture(t_game *game)
{
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		pixel;
	
	img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!img)
		return (NULL);
	
	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!data)
	{
		mlx_destroy_image(game->mlx, img);
		return (NULL);
	}
	
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = (y * size_line) + (x * (bits_per_pixel / 8));
			*(int*)(data + pixel) = WHITE;
			x++;
		}
		y++;
	}
	
	return (img);
}
