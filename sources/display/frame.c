/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:19:08 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/21 12:27:07 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_weapon(t_cub *cub)
{
	if (cub->player.shooting)
		cub->player.shooting++;
	if (cub->player.shooting == (FRAME_RATE / 20))
		cub->player.hand = cub->img[HAND2];
	else if (cub->player.shooting == (FRAME_RATE / 20) * 2)
		cub->player.hand = cub->img[HAND3];
	else if (cub->player.shooting == (FRAME_RATE / 20) * 3)
		cub->player.hand = cub->img[HAND4];
	else if (cub->player.shooting == (FRAME_RATE / 20) * 4)
		cub->player.hand = cub->img[HAND5];
	else if (cub->player.shooting == (FRAME_RATE / 20) * 6)
	{
		cub->player.hand = cub->img[HAND1];
		cub->player.shooting = 0;
	}
	image_to_frame(cub, cub->player.hand, \
		cub->layout.hand_x, cub->layout.hand_y);
}

void	build_frame(t_cub *cub)
{
	barrage_of_rays(cub);
	render_minimap(cub);
	render_weapon(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img[FRAME].img, 0, 0);
}
