/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:51:16 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/05/27 14:36:40 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	open_window_4k(t_cub *cub)
{
	cub->window = mlx_new_window(cub->mlx, (int)X_RES, (int)Y_RES, "Window");
	return (1);
}

void	init_camera(t_cub *cub, t_camera *camera)
{
	camera->fov_rad = FOV * (M_PI / 180);
	camera->dir_x = cos(cub->player.angle);
	camera->dir_y = sin(cub->player.angle);
	camera->plane_x = -camera->dir_y * tan(camera->fov_rad / 2);
	camera->plane_y = camera->dir_x * tan(camera->fov_rad / 2);
}

void	update_player_mouse_angle(t_cub *cub)
{
	int	x;
	int	y;

	if (!cub->player.changing_view && !cub->tab)
	{
		mlx_mouse_get_pos(cub->mlx, cub->window, &x, &y);
		cub->player.vis_angle += (x - X_RES / 2) / SENSITIVITY;
	}
	else 
		cub->player.vis_angle += cub->player.changing_view * 2;
	if (cub->player.vis_angle >= 360.0)
		cub->player.vis_angle = cub->player.vis_angle - \
		(360.0 / cub->player.vis_angle) * 360.0;
	else if (cub->player.vis_angle < 0.0)
		cub->player.vis_angle += 360;
	cub->player.angle = cub->player.vis_angle * (M_PI / 180);
	if (!cub->tab)
		mlx_mouse_move(cub->mlx, cub->window, X_RES / 2, Y_RES / 2);
}
