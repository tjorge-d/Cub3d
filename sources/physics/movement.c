/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:50:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/20 16:18:39 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_colliding_in_y(t_cub *cub, float old_y)
{
	float	flag;

	flag = 1;
	if ((cub->player.y < old_y))
		flag = -1;
	if (cub->map.map[(int)(cub->player.y + FAT * flag)] \
		[(int)(cub->player.x + FAT)] == '1' \
		|| cub->map.map[(int)(cub->player.y + FAT * flag)] \
		[(int)(cub->player.x - FAT)] == '1')
		return (1);
	if (cub->map.map[(int)(cub->player.y + FAT * flag)] \
		[(int)(cub->player.x + FAT)] == '2' \
		|| cub->map.map[(int)(cub->player.y + FAT * flag)] \
		[(int)(cub->player.x - FAT)] == '2')
		return (1);
	return (0);
}

int	is_colliding_in_x(t_cub *cub, float old_x)
{
	float	flag;

	flag = 1;
	if ((cub->player.x < old_x))
		flag = -1;
	if (cub->map.map[(int)(cub->player.y + FAT)] \
	[(int)(cub->player.x + (FAT * flag))] == '1' \
	|| cub->map.map[(int)(cub->player.y - FAT)] \
	[(int)(cub->player.x + (FAT * flag))] == '1')
		return (1);
	if (cub->map.map[(int)(cub->player.y + FAT)] \
	[(int)(cub->player.x + (FAT * flag))] == '2' \
	|| cub->map.map[(int)(cub->player.y - FAT)] \
	[(int)(cub->player.x + (FAT * flag))] == '2')
		return (1);
	return (0);
}

void	player_movement(t_cub *cub)
{
	float	old_x;
	float	old_y;

	old_x = cub->player.x;
	old_y = cub->player.y;
	if (cub->player.x_mov == 0 && cub->player.y_mov == 0)
		cub->player.mov_angle = -1;
	else
	{
		cub->player.mov_angle = cub->player.vis_angle + \
			cub->player.mov_tool[cub->player.y_mov + 1][cub->player.x_mov + 1];
		if (cub->player.mov_angle >= 360)
			cub->player.mov_angle -= 360;
	}
	if (cub->player.mov_angle >= 0)
	{
		cub->player.y = cub->player.y + \
			sin((cub->player.mov_angle * 2 * 3.141592) / 360) * SPEED;
		if (is_colliding_in_y(cub, old_y))
			cub->player.y = old_y;
		cub->player.x = cub->player.x + \
			cos((cub->player.mov_angle * 2 * 3.141592) / 360) * SPEED;
		if (is_colliding_in_x(cub, old_x))
			cub->player.x = old_x;
	}
}
