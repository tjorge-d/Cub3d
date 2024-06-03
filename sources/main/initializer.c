/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/21 12:24:44 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_tools(t_cub *cub)
{
	cub->player.mov_tool[0][1] = 0;
	cub->player.mov_tool[0][2] = 45;
	cub->player.mov_tool[1][2] = 90;
	cub->player.mov_tool[2][2] = 135;
	cub->player.mov_tool[2][1] = 180;
	cub->player.mov_tool[2][0] = 225;
	cub->player.mov_tool[1][0] = 270;
	cub->player.mov_tool[0][0] = 315;
	cub->player.mov_tool[1][1] = -1;
}

static void	set_layout(t_cub *cub)
{
	cub->layout.border_size = (X_RES + Y_RES) / 2 / 30;
	cub->layout.map_size = 128;
	cub->layout.map_x = X_RES - cub->layout.border_size \
		- cub->layout.map_size * UI_SCALE;
	cub->layout.map_y = cub->layout.border_size;
	cub->layout.mario_x = (128) / 2 - (16 / 2);
	cub->layout.mario_y = (128) / 2 - (16 / 2);
	cub->layout.hand_x = X_RES / 2 - (32 * HAND_SIZE) / 2; 
	cub->layout.hand_y = Y_RES - (32 * HAND_SIZE);
	cub->img[M_BACKGROUND].scale = 1;
	cub->img[M_LAYER].scale = 1;
	cub->img[M_MAP].w = cub->layout.map_size;
	cub->img[M_MAP].h = cub->layout.map_size;
	cub->img[M_MAP].scale = UI_SCALE;
	cub->img[FRAME].w = X_RES;
	cub->img[FRAME].h = Y_RES;
	cub->img[HAND1].scale = HAND_SIZE;
	cub->img[HAND2].scale = HAND_SIZE;
	cub->img[HAND3].scale = HAND_SIZE;
	cub->img[HAND4].scale = HAND_SIZE;
	cub->img[HAND5].scale = HAND_SIZE;
}

static void	set_asset_paths(t_cub *cub)
{
	cub->img[DOOR].path = "./Assets/door.xpm";
	cub->img[M_BACKGROUND].path = "./Assets/minimap2.xpm";
	cub->img[M_LAYER].path = "./Assets/mini_layer2.xpm";
	cub->img[M_WALL].path = "./Assets/mini_wall.xpm";
	cub->img[M_MARIO].path = "./Assets/mini_mario.xpm";
	cub->img[M_DOOR2].path = "./Assets/mini_door.xpm";
	cub->img[M_DOOR3].path = "./Assets/mini_open_door.xpm";
	cub->img[HAND1].path = "./Assets/hand1.xpm";
	cub->img[HAND2].path = "./Assets/hand2.xpm";
	cub->img[HAND3].path = "./Assets/hand3.xpm";
	cub->img[HAND4].path = "./Assets/hand4.xpm";
	cub->img[HAND5].path = "./Assets/hand5.xpm";
	(void)cub;
}

void	cub_initializer(t_cub *cub)
{
	static t_image			img[ASSET_NUMBER + IMG_NUMBER];
	static t_player			player;
	static t_map			map;
	static char				*arg[10];

	cub->img = img;
	cub->player = player;
	cub->map = map;
	cub->arg = arg;
	set_tools(cub);
	set_layout(cub);
	set_asset_paths(cub);
	(void)cub;
}
