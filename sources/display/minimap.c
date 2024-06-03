/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:20:51 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/20 17:29:54 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	image_to_minimap(t_cub *cub, int asset, int x, int y)
{
	int		x_pos;
	int		y_pos;
	int		b;

	x_pos = x;
	b = x_pos;
	y_pos = y;
	if (y_pos < 0)
		y = 0;
	if (x_pos < 0)
		b = 0;
	while (y < y_pos + (cub->img[asset].h) && y < cub->img[M_MAP].h)
	{
		x = b;
		while (x < x_pos + (cub->img[asset].w) && x < cub->img[M_MAP].w)
		{
			if (x >= 0 && y >= 0)
				my_mlx_pixel_put(&cub->img[M_MAP], x, y, \
				get_color(&cub->img[asset], (x - x_pos), \
				(y - y_pos)));
			x++;
		}
		y++;
	}
}

static void	create_transparent_frame(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
		{
			if ((x < 6 || x > 122) || (y < 6 || y > 122))
				my_mlx_pixel_force(&cub->img[M_MAP], x, y, 16777215);
		}
	}
}

void	draw_minimap_ray(t_cub *cub, float angle, float x, float y)
{
	float	old_x;
	float	old_y;

	while (x > 4 && x < 124 && y > 4 && y < 124)
	{
		my_mlx_pixel_put(&cub->img[M_MAP], x - 1, y, 0);
		my_mlx_pixel_put(&cub->img[M_MAP], x, y - 1, 0);
		my_mlx_pixel_put(&cub->img[M_MAP], x + 1, y, 0);
		my_mlx_pixel_put(&cub->img[M_MAP], x, y + 1, 0);
		my_mlx_pixel_put(&cub->img[M_MAP], x, y, 0);
		old_y = y;
		old_x = x;
		y = y + sin((angle * 2 * 3.141592) / 360) * 0.5;
		if (cub->map.map[(int)((cub->player.y + (y - 64) / 16))] \
		[(int)((cub->player.x + (old_x - 64) / 16))] == '1' \
		|| cub->map.map[(int)((cub->player.y + (y - 64) / 16))] \
		[(int)((cub->player.x + (old_x - 64) / 16))] == '2')
			return ;
		x = x + cos((angle * 2 * 3.141592) / 360) * 0.5;
		if (cub->map.map[(int)((cub->player.y + (old_y - 64) / 16))] \
		[(int)((cub->player.x + (x - 64) / 16))] == '1' \
		|| cub->map.map[(int)((cub->player.y + (old_y - 64) / 16))] \
		[(int)((cub->player.x + (x - 64) / 16))] == '2')
			return ;
	}
}

void	minimap_rays(t_cub *cub)
{
	int		i;
	float	ray_range[2];

	i = 0;
	(void)cub;
	ray_range[0] = (int)(cub->player.vis_angle - FOV / 2);
	if (ray_range[0] < 0)
		ray_range[0] = ray_range[0] + 360;
	ray_range[1] = (int)(cub->player.vis_angle + FOV / 2);
	if (ray_range[1] < 0)
		ray_range[1] = ray_range[1] + 360;
	while (i < FOV)
	{
		draw_minimap_ray(cub, ray_range[0] + i, 64, 64);
		i++;
	}
}

void	render_minimap(t_cub *cub)
{
	image_to_minimap(cub, M_BACKGROUND, 0, 0);
	minimap_rays(cub);
	image_to_minimap(cub, MAP, cub->layout.mario_x + 8 - cub->player.x * 16, \
		cub->layout.mario_y + 8 - cub->player.y * 16);
	image_to_minimap(cub, M_MARIO, cub->layout.mario_x, cub->layout.mario_y);
	create_transparent_frame(cub);
	image_to_minimap(cub, M_LAYER, 0, 0);
	image_to_frame_ui(cub, cub->img[M_MAP], \
		cub->layout.map_x, cub->layout.map_y);
}
