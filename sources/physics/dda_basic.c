/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:51:47 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/05/20 16:18:39 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	calculate_dist(t_ray *ray)
{
	if (ray->side_hit == 0)
		return (ray->side_d_x - ray->delta_d_x);
	else
		return (ray->side_d_y - ray->delta_d_y);
}

void	calculate_ray_steps(t_ray *ray, t_cub *cub)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_d_x = (cub->player.x - ray->x) * ray->delta_d_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_d_x = ((ray->x + 1) - cub->player.x) * ray->delta_d_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_d_y = (cub->player.y - ray->y) * ray->delta_d_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_d_y = ((ray->y + 1) - cub->player.y) * ray->delta_d_y;
	}
}

void	calc_delta_distance(t_ray *ray)
{
	if (ray->dir_x != 0)
		ray->delta_d_x = fabs(1 / ray->dir_x);
	else 
		ray->delta_d_x = X_RES;
	if (ray->dir_y != 0)
		ray->delta_d_y = fabs(1 / ray->dir_y);
	else
		ray->delta_d_y = Y_RES;
}

double	actual_dda(t_cub *cub, t_ray *ray)
{
	int	hit;

	hit = 0;
	ray->door_hit = 0;
	while (!hit)
	{
		if (ray->side_d_x < ray->side_d_y)
		{
			ray->side_d_x += ray->delta_d_x;
			ray->x += ray->step_x;
			ray->side_hit = NORTHSOUTH;
		}
		else
		{
			ray->side_d_y += ray->delta_d_y;
			ray->y += ray->step_y;
			ray->side_hit = WESTEAST;
		}
		if (cub->map.map[ray->y][ray->x] == '2')
			ray->door_hit = 1;
		if (cub->map.map[ray->y][ray->x] == '1')
			hit = 1;
	}
	ray->dir_wall = get_wall_direction(ray);
	return (calculate_dist(ray));
}

void	initialize_ray(t_cub *cub, t_ray *ray, int ray_n, t_camera *camera)
{
	ray->x = (int)cub->player.x;
	ray->y = (int)cub->player.y;
	camera->x = 2 * ray_n / (double)X_RES - 1;
	ray->dir_x = camera->dir_x + camera->plane_x * camera->x;
	ray->dir_y = camera->dir_y + camera->plane_y * camera->x;
}
