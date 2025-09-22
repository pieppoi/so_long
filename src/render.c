/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:35:01 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 05:50:39 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_fallback_tile(t_game *game, int x, int y, char tile);

int	render_game(t_game *game)
{
	render_map(game);
	render_player(game);
	return (0);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y, game->map.grid[y][x]);
			x++;
		}
		y++;
	}
}

void	render_tile(t_game *game, int x, int y, char tile)
{
	void	*texture;
	int		screen_x;
	int		screen_y;

	screen_x = x * TILE_SIZE;
	screen_y = y * TILE_SIZE;
	if (tile == WALL)
		texture = game->textures.wall;
	else if (tile == EMPTY)
		texture = game->textures.empty;
	else if (tile == COLLECTIBLE)
		texture = game->textures.collectible;
	else if (tile == EXIT)
		texture = game->textures.exit;
	else
		texture = game->textures.empty;
	if (texture)
		mlx_put_image_to_window(game->mlx, game->win, texture,
			screen_x, screen_y);
	else
		draw_fallback_tile(game, screen_x, screen_y, tile);
}

void	render_player(t_game *game)
{
	int		screen_x;
	int		screen_y;
	void	*fallback_img;

	screen_x = game->player.pos.x * TILE_SIZE;
	screen_y = game->player.pos.y * TILE_SIZE;
	if (game->textures.player)
		mlx_put_image_to_window(game->mlx, game->win, game->textures.player,
			screen_x, screen_y);
	else
	{
		fallback_img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
		if (!fallback_img)
			return ;
		fill_player_texture(fallback_img);
		mlx_put_image_to_window(game->mlx, game->win, fallback_img,
			screen_x, screen_y);
		mlx_destroy_image(game->mlx, fallback_img);
	}
}

void	draw_fallback_tile(t_game *game, int x, int y, char tile)
{
	void	*fallback_img;
	int		color;

	fallback_img = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	if (!fallback_img)
		return ;
	if (tile == WALL)
		color = 0x404040;
	else if (tile == EMPTY)
		color = WHITE;
	else if (tile == COLLECTIBLE)
		color = YELLOW;
	else if (tile == EXIT)
		color = GREEN;
	else
		color = WHITE;
	fill_texture(fallback_img, color);
	mlx_put_image_to_window(game->mlx, game->win, fallback_img, x, y);
	mlx_destroy_image(game->mlx, fallback_img);
}
