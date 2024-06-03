/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:50:54 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/05/21 11:53:37 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put_real(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > X_RES || y > Y_RES)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_limits(t_cub *cub, int x, int c_pos, int f_pos)
{
	int	i;

	i = 0;
	while (i <= c_pos)
	{
		my_mlx_pixel_put_real(&cub->img[FRAME], x, i, cub->ceiling);
		i += 1 + (1 * PIXEL_SKIP);
	}
	i = (f_pos / (1 + PIXEL_SKIP) * (1 + PIXEL_SKIP));
	while (i < Y_RES)
	{
		my_mlx_pixel_put_real(&cub->img[FRAME], x, i, cub->floor);
		i += 1 + (1 * PIXEL_SKIP);
	}
}

void	draw_textured_line(t_cub *cub, t_line *d_line, \
	int asset_n)
{
	int				y_in_tex;
	int				i;
	int				normalized;
	int				y;
	double			step;

	render_limits(cub, d_line->x_coordinate, d_line->start, d_line->end);
	normalized = ((int) d_line->start / (1 + PIXEL_SKIP)) * (1 + PIXEL_SKIP);
	i = 0;
	step = 1.0 * cub->img[asset_n].h / d_line->height;
	while (normalized + i < d_line->end)
	{
		y_in_tex = (int) d_line->y_stepper % cub->img[asset_n].h;
		d_line->y_stepper += step;
		if (i % (PIXEL_SKIP + 1) != 0)
		{
			i ++;
			continue ;
		}
		y = normalized + i;
		my_mlx_pixel_put_real(&cub->img[FRAME], d_line->x_coordinate, y, \
		get_color(&cub->img[asset_n], d_line->x_in_texture, y_in_tex));
		i ++;
	}
}

void	render_lines(t_ray *ray, t_cub *cub, int ray_n)
{
	double		step;
	t_line		d_line;

	if (ray->perp_wall_dist > 0)
	{
		d_line.height = (int)(Y_RES / ray->perp_wall_dist);
		step = 1.0 * (cub->img[ray->dir_wall].h / d_line.height);
		d_line.start = -d_line.height / 2 + Y_RES / (2);
		d_line.end = d_line.height / 2 + Y_RES / (2);
		d_line.x_in_texture = coordinate_x_text(cub, ray, \
		get_wallx(cub, ray), ray->dir_wall);
		d_line.y_stepper = (d_line.start - Y_RES / 2 + d_line.height / 2) \
			* step;
		d_line.x_coordinate = ray_n;
		draw_textured_line(cub, &d_line, ray->dir_wall);
	}
}

void	render_door(t_ray *ray, t_cub *cub, int ray_n)
{
	double		step;
	t_line		d_line;

	if (ray->perp_wall_dist > 0)
	{
		d_line.height = (int)(Y_RES / ray->perp_wall_dist);
		step = 1.0 * cub->img[DOOR].h / d_line.height;
		d_line.start = -d_line.height / 2 + Y_RES / (2);
		d_line.end = d_line.height / 2 + Y_RES / (2);
		d_line.x_in_texture = coordinate_x_text(cub, ray, \
		get_wallx(cub, ray), DOOR);
		d_line.y_stepper = (d_line.start - Y_RES / 2 + d_line.height / 2) \
			* step;
		d_line.x_coordinate = ray_n;
		draw_textured_line(cub, &d_line, DOOR);
	}
}
