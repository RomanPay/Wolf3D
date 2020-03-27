/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 11:39:08 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_surface_pixel(t_union *my_union, int x, int y, SDL_Color *color)
{
	Uint8		*pixel;

	pixel = my_union->surface->pixels + y * my_union->surface->pitch;
	pixel += x * my_union->surface->format->BytesPerPixel;
	SDL_GetRGB(*pixel, my_union->surface->format,
			&color->r, &color->g, &color->b);
}

void	put_pixel(t_union *my_union, int x, int y, SDL_Color *color)
{
	int shift;

	shift = y * my_union->cur_win_x + x;
	my_union->pixel_array[shift] = (Uint32)((color->r << 16) +
		(color->g << 8) + color->b);
}

void	choose_surface_wall(t_union *my_union, t_ray ray, t_map map)
{
	int wall;
	int x;
	int y;

	y = (int)ray.y >> 6;
	x = (int)ray.x >> 6;
	if (map.map[y][x] == 2)
		my_union->surface = my_union->wall_surfaces_array[9];
	else
	{
		wall = map.map[y][x];
		my_union->surface = my_union->wall_surfaces_array[wall + ray.mode];
	}
}

void	choose_surface_floor_ceiling_hud(t_union *my_union, char mode)
{
	if (mode == 'c')
		my_union->surface = my_union->wall_surfaces_array[7];
	else if (mode == 'h')
		my_union->surface = my_union->hud_surface;
	else
		my_union->surface = my_union->wall_surfaces_array[6];
}
