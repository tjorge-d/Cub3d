/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:16:53 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/27 14:41:41 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_valid_map_element(char element)
{
	if (element == '0' || element == '1' || element == '\n' \
		|| element == ' ' || element == '2')
		return (1);
	return (0);
}

static void	*find_player_coords(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	while (cub->map.map[++y])
	{
		x = -1;
		while (cub->map.map[y][++x])
		{
			if (cub->map.map[y][x] == 'N' || cub->map.map[y][x] == 'S' \
			|| cub->map.map[y][x] == 'W' || cub->map.map[y][x] == 'E')
			{
				if (cub->map.player_dir)
					return (printf("Error\nToo many player spawns\n"), \
						free_cub(cub, 2), NULL);
				else
				{
					cub->map.player_dir = cub->map.map[y][x];
					cub->map.player_x = x + 0.5;
					cub->map.player_y = y + 0.5;
				}
			}
		}
	}
	return (NULL);
}

static void	*check_for_invalid_neighbour(t_cub *cub, int x, int y)
{
	if (x == -1 || y == -1 \
	|| !cub->map.map[y] || (int)ft_strlen(cub->map.map[y]) < x \
	|| (cub->map.map[y][x] != -42 && cub->map.map[y][x] != '0' \
	&& cub->map.map[y][x] != '1' && cub->map.map[y][x] != '2'))
		return (printf("Error\nInvalid map\n"), free_cub(cub, 2), NULL);
	return (NULL);
}

void	*check_for_invalid_chars(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	cub->map.map[cub->map.player_y][cub->map.player_x] = '0';
	while (cub->map.map[++y])
	{
		x = -1;
		while (cub->map.map[y][++x])
		{
			if (!is_valid_map_element(cub->map.map[y][x]))
				return (printf("Error\nInvalid map\n"), \
						free_cub(cub, 2), NULL);
			else if (cub->map.map[y][x] == '0' || cub->map.map[y][x] == '2')
			{
				check_for_invalid_neighbour(cub, x + 1, y);
				check_for_invalid_neighbour(cub, x - 1, y);
				check_for_invalid_neighbour(cub, x, y + 1);
				check_for_invalid_neighbour(cub, x, y - 1);
			}
		}
	}
	return (NULL);
}

void	*cub_map_validator(t_cub *cub)
{
	find_player_coords(cub);
	if (!cub->map.player_dir)
		return (printf("Error\nThere is no player spawn\n"), \
			free_cub(cub, 2), NULL);
	check_for_invalid_chars(cub);
	return (NULL);
}
