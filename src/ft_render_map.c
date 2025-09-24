/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 06:50:44 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/23 06:50:45 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		ft_render_map(t_game *game);
void	ft_identify_sprite(t_game *game, int x, int y);
void	ft_render_player(t_game *game, int x, int y);
void	ft_render_sprite(t_game *game, t_image sprite, int line, int column);
void	ft_print_movements(t_game *game);

int	ft_render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			ft_identify_sprite(game, y, x);
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_identify_sprite(t_game *game, int y, int x)
{
	char	parameter;

	parameter = game->map.full[y][x];
	if (parameter == WALL)
		ft_render_sprite (game, game->wall, y, x);
	else if (parameter == FLOOR)
		ft_render_sprite (game, game->floor, y, x);
	else if (parameter == COINS)
		ft_render_sprite (game, game->coins, y, x);
	else if (parameter == MAP_EXIT)
	{
		if (game->map.coins == 0)
			ft_render_sprite (game, game->open_exit, y, x);
		else
			ft_render_sprite (game, game->exit_closed, y, x);
	}
	else if (parameter == PLAYER)
		ft_render_player (game, y, x);
}

void	ft_render_player(t_game *game, int y, int x)
{
	if (game->player_sprite == FRONT)
		ft_render_sprite (game, game->player_front, y, x);
	if (game->player_sprite == LEFT)
		ft_render_sprite (game, game->player_left, y, x);
	if (game->player_sprite == RIGHT)
		ft_render_sprite (game, game->player_right, y, x);
	if (game->player_sprite == BACK)
		ft_render_sprite (game, game->player_back, y, x);
}

void	ft_render_sprite(t_game *game, t_image sprite, int line, int column)
{
    /* Draw base floor first so transparent (None) areas show it */
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
    game->floor.xpm_ptr, column * IMG_WIDTH, line * IMG_HEIGHT);
    /* Overlay the requested sprite */
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
    sprite.xpm_ptr, column * sprite.x, line * sprite.y);
}
