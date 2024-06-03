/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:16:45 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/21 15:17:34 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_up_cub(t_cub *cub)
{
	cub->player.x = (cub->map.player_x + 0.5);
	cub->player.y = (cub->map.player_y + 0.5); 
	cub->player.mov_angle = -1;
	if (cub->map.player_dir == 'N')
		cub->player.vis_angle = 270.0;
	else if (cub->map.player_dir == 'S')
		cub->player.vis_angle = 90.0;
	else if (cub->map.player_dir == 'E')
		cub->player.vis_angle = 0.0;
	else if (cub->map.player_dir == 'W')
		cub->player.vis_angle = 180.0;
	cub->player.height = 1;
	cub->player.angle = cub->player.vis_angle * (M_PI / 180);
	gettimeofday(&cub->time, NULL);
	cub->last_frame = cub->time.tv_sec * 1000000 \
		+ cub->time.tv_usec;
}

static void	paint_background(t_cub *cub, int asset, int width, int height)
{
	int	x;
	int	y;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			my_mlx_pixel_force(&cub->img[asset], x, y, 16777215);
	}
}

void	create_mini_map(t_cub *cub)
{
	int	i;
	int	j;

	j = -1;
	paint_background(cub, MAP, cub->img[MAP].w, cub->img[MAP].h);
	while (++j < cub->img[MAP].h)
	{
		i = -1;
		while (++i < cub->img[MAP].w)
		{
			if (cub->map.map[j / 16][i / 16] == '\0')
				break ;
			if (cub->map.map[j / 16][i / 16] == '1')
				my_mlx_pixel_put(&cub->img[MAP], i, j, \
					get_color(&cub->img[M_WALL], (i % 16), (j % 16)));
			else if (cub->map.map[j / 16][i / 16] == '2')
				my_mlx_pixel_put(&cub->img[MAP], i, j, \
					get_color(&cub->img[M_DOOR2], (i % 16), (j % 16)));
		}
	}
	paint_background(cub, M_MAP, cub->layout.map_size, \
		cub->layout.map_size);
}

void	load_cub(t_cub *cub)
{
	int	i;

	cub->mlx = mlx_init();
	gettimeofday(&cub->time, NULL);
	cub->last_frame = cub->time.tv_sec * 1000000 + cub->time.tv_usec;
	cub->window = mlx_new_window(cub->mlx, X_RES, Y_RES, "Window");
	mlx_do_key_autorepeatoff(cub->mlx);
	set_up_cub(cub);
	i = -1;
	while (++i < ASSET_NUMBER + IMG_NUMBER)
	{
		if (i >= ASSET_NUMBER)
			cub->img[i].img = mlx_new_image(cub->mlx, cub->img[i].w, \
				cub->img[i].h);
		else
		{
			cub->img[i].img = mlx_xpm_file_to_image(cub->mlx, \
				cub->img[i].path, &cub->img[i].w, &cub->img[i].h);
		}
		if (!cub->img[i].img)
			game_close(cub, 2);
		cub->img[i].addr = mlx_get_data_addr(cub->img[i].img, \
			&cub->img[i].bpp, &cub->img[i].line_length, &cub->img[i].endian);
		cub->img[i].created = 1;
	}
}
