/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 05:35:14 by mkazuhik          #+#    #+#             */
/*   Updated: 2025/09/22 07:07:04 by mkazuhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit(1);
	}
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size - 1);
	free(ptr);
	return (new_ptr);
}

static void	cleanup_map(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
}

static void	cleanup_textures(t_game *game)
{
	if (game->textures.wall)
		mlx_destroy_image(game->mlx, game->textures.wall);
	if (game->textures.empty)
		mlx_destroy_image(game->mlx, game->textures.empty);
	if (game->textures.collectible)
		mlx_destroy_image(game->mlx, game->textures.collectible);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx, game->textures.exit);
	if (game->textures.player)
		mlx_destroy_image(game->mlx, game->textures.player);
}

void	ft_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	ft_cleanup(t_game *game)
{
	cleanup_map(game);
	cleanup_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
}
