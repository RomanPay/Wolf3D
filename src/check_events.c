/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:27:50 by hdwarven          #+#    #+#             */
/*   Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mouse_relative_handling(t_union *my_union, t_player *player)
{
	int x;
	int y;

	SDL_GetRelativeMouseState(&x, &y);
	if (x)
	{
		player->view_direction += (x * my_union->sens * my_union->time);
		player->view_direction_rad = player->view_direction * RAD;
		my_union->mouse_x = x;
	}
}

void	check_weapons_and_quit(t_union *my_union, t_map *map, t_player *player,
							t_map *objects)
{
	if (!my_union->escape_timer && my_union->key_game[SDL_SCANCODE_ESCAPE])
	{
		my_union->escape_timer = SDL_GetTicks();
		my_union->go_to_menu = 1;
	}
	if (my_union->key_game[SDL_SCANCODE_SPACE])
		check_door(map, objects, player, my_union);
	if (!player->shoot_mode && (my_union->key_game[SDL_SCANCODE_1] ||
	my_union->key_game[SDL_SCANCODE_2] || my_union->key_game[SDL_SCANCODE_3]))
	{
		my_union->change_weapon_mode = 1;
		change_weapon(player, my_union->key_game, my_union);
	}
	if (!my_union->reload_timer && my_union->key_game[SDL_SCANCODE_R])
	{
		my_union->reload_timer = SDL_GetTicks();
		reload(my_union, player);
	}
}

void	check_rotates_keys(t_union *my_union, t_player *player)
{
	float temp;

	if (!my_union->mouse_handling && my_union->key_game[SDL_SCANCODE_Q])
	{
		if (player->view_direction - player->rotate_angle >= 0)
			player->view_direction -= player->rotate_angle;
		else
		{
			temp = 360 + player->view_direction - player->rotate_angle;
			player->view_direction = temp;
		}
		player->view_direction_rad = player->view_direction * RAD;
	}
	if (!my_union->mouse_handling && my_union->key_game[SDL_SCANCODE_E])
	{
		if (player->view_direction + player->rotate_angle < 360)
			player->view_direction += player->rotate_angle;
		else
		{
			temp = 360 - player->view_direction - player->rotate_angle;
			player->view_direction = -temp;
		}
		player->view_direction_rad = player->view_direction * RAD;
	}
}

void	check_movement_shooting_keys(t_union *my_union, t_map *map,
		t_player *player)
{
	if (my_union->mouse_handling)
		mouse_relative_handling(my_union, player);
	if (my_union->key_game[SDL_SCANCODE_UP] ||
	my_union->key_game[SDL_SCANCODE_W])
		move_forward(player, map, 1);
	if (my_union->key_game[SDL_SCANCODE_DOWN] ||
		my_union->key_game[SDL_SCANCODE_S])
		move_forward(player, map, -1);
	if (my_union->key_game[SDL_SCANCODE_LEFT] ||
		my_union->key_game[SDL_SCANCODE_A])
		strafe(player, map, -1);
	if (my_union->key_game[SDL_SCANCODE_RIGHT] ||
		my_union->key_game[SDL_SCANCODE_D])
		strafe(player, map, 1);
	if (!my_union->weapon_down_mode && !my_union->shoot_timer &&
			(my_union->key_game[SDL_SCANCODE_KP_ENTER] ||
			(my_union->mouse_handling && (SDL_GetMouseState(NULL, NULL) &
			SDL_BUTTON(SDL_BUTTON_LEFT))))
			&& !player->shoot_mode && player->clip[player->weapon])
	{
		if (player->weapon)
			player->clip[player->weapon]--;
		my_union->shoot_timer = SDL_GetTicks();
		player->shoot_mode = 1;
	}
}
