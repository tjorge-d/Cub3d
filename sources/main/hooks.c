/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:39:41 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/27 14:36:22 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	refresh_door_asset(t_cub *cub, int mode, int x, int y)
{
	int	i;
	int	j;

	j = -1;
	x = x * 16;
	y = y * 16;
	while (++j < 16)
	{
		i = -1;
		while (++i < 16)
		{
			if (mode == 2)
				my_mlx_pixel_force(&cub->img[MAP], x + i, y + j, \
					get_color(&cub->img[M_DOOR2], i, j));
			else
				my_mlx_pixel_force(&cub->img[MAP], x + i, y + j, \
					get_color(&cub->img[M_DOOR3], i, j));
		}
	}
}

void	*refresh_door(t_cub *cub)
{
	float	x;
	float	y;
	int		i;

	i = -1;
	x = cub->player.x;
	y = cub->player.y;
	while (++i <= 20)
	{
		y = y + sin((cub->player.vis_angle * 2 * M_PI) / 360) * 0.1;
		x = x + cos((cub->player.vis_angle * 2 * M_PI) / 360) * 0.1;
		if (cub->map.map[(int)y][(int)x] == '1')
			return (NULL);
		else if (cub->map.map[(int)y][(int)x] == '2')
		{
			return (cub->map.map[(int)y][(int)x] = '3', \
				refresh_door_asset(cub, 3, (int)x, (int)y), NULL);
		}
		else if (cub->map.map[(int)y][(int)x] == '3')
		{
			return (cub->map.map[(int)y][(int)x] = '2', \
				refresh_door_asset(cub, 2, (int)x, (int)y), NULL);
		}
	}
	return (NULL);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == TAB)
		cub->tab++;
	else if (keycode == LEFT_VIEW)
		cub->player.changing_view --;
	else if (keycode == RIGHT_VIEW)
		cub->player.changing_view ++;
	else if (keycode == FORE)
		cub->player.y_mov--;
	else if (keycode == LEFT)
		cub->player.x_mov--;
	else if (keycode == AFT)
		cub->player.y_mov++;
	else if (keycode == RIGHT)
		cub->player.x_mov++;
	else if (keycode == 101 && \
		cub->map.map[(int)(cub->player.y)][(int)(cub->player.x)] == '0')
		refresh_door(cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == TAB)
	{
		cub->tab--;
		mlx_mouse_move(cub->mlx, cub->window, X_RES / 2, Y_RES / 2);
	}
	else if (keycode == LEFT_VIEW)
		cub->player.changing_view ++;
	else if (keycode == RIGHT_VIEW)
		cub->player.changing_view --;
	else if (keycode == ESC)
		game_close(cub, 2);
	else if (keycode == FORE)
		cub->player.y_mov++;
	else if (keycode == LEFT)
		cub->player.x_mov++;
	else if (keycode == AFT)
		cub->player.y_mov--;
	else if (keycode == RIGHT)
		cub->player.x_mov--;
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (!cub->player.shooting && keycode == 1)
		cub->player.shooting = 1;
	return (0);
}
