/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:51:28 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/05/21 12:29:01 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	get_wallx(t_cub *cub, t_ray *ray)
{
	double	ans;

	if (ray->side_hit == 0)
		ans = cub->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ans = cub->player.x + ray->perp_wall_dist * ray->dir_x;
	ans -= floor((ans));
	return (ans);
}

int	coordinate_x_text(t_cub *cub, t_ray *ray, double wall_x, int asset_n)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double) cub->img[asset_n].w);
	if (ray->side_hit == 0 && ray->dir_x > 0)
		tex_x = cub->img[asset_n].w - tex_x - 1;
	if (ray->side_hit == 1 && ray->dir_y < 0)
		tex_x = cub->img[asset_n].w - tex_x - 1;
	return (tex_x);
}

int	get_wall_direction(t_ray *ray)
{
	if (ray->dir_y < 0 && ray->side_hit == 1)
		return (NORTH);
	else if (ray->side_hit == 1)
		return (SOUTH);
	else if (ray->dir_x > 0)
		return (EAST);
	else
		return (WEST);
}
