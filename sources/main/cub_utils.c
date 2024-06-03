/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:23 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/20 16:18:39 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

static void	free_args_n_assets(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 10)
	{
		if (cub->arg[i])
			free(cub->arg[i]);
	}
	i = -1;
	while (++i < ASSET_NUMBER + IMG_NUMBER)
	{
		if (cub->img[i].created)
			mlx_destroy_image(cub->mlx, cub->img[i].img); 
	}
}

static void	free_map(t_cub *cub)
{
	if (cub->map.pre_map)
		free(cub->map.pre_map);
	if (cub->map.map)
		free_split(cub->map.map);
}

void	free_cub(t_cub *cub, int exit_code)
{
	free_args_n_assets(cub);
	free_map(cub);
	if (exit_code == 2)
		exit(exit_code);
}

int	game_close(t_cub *cub, int exit_code)
{
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_destroy_window(cub->mlx, cub->window);
	free_cub(cub, 0);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(exit_code);
}
