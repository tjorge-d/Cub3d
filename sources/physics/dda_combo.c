/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_combo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:51:37 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/05/21 11:54:07 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	actual_dda_door(t_cub *cub, t_ray *ray)
{
	int	hit;

	hit = 0;
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
		{
			hit = 1;
		}
	}
	ray->dir_wall = get_wall_direction(ray);
	return (calculate_dist(ray));
}

void	barrage_of_rays(t_cub *cub)
{
	t_camera	camera;
	t_ray		ray;
	t_ray		door_ray;
	int			ray_n;

	init_camera(cub, &camera);
	ray_n = 0;
	while (ray_n < X_RES)
	{
		initialize_ray(cub, &ray, ray_n, &camera);
		calc_delta_distance(&ray);
		calculate_ray_steps(&ray, cub);
		ray.perp_wall_dist = actual_dda(cub, &ray);
		render_lines(&ray, cub, ray_n);
		if (ray.door_hit)
		{
			initialize_ray(cub, &door_ray, ray_n, &camera);
			calc_delta_distance(&door_ray);
			calculate_ray_steps(&door_ray, cub);
			door_ray.perp_wall_dist = actual_dda_door(cub, &door_ray);
			render_door(&door_ray, cub, ray_n);
		}
		ray_n += 1 + PIXEL_SKIP;
	}
}
