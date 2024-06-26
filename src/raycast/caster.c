/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:42:26 by akambou           #+#    #+#             */
/*   Updated: 2024/06/19 09:10:27 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	chose_lenght(t_game *game)
{
	if (game->rays->h_length < game->rays->v_length)
	{
		game->rays->total_length = game->rays->h_length;
		draw_ray(game, 0, game->rays->total_length);
	}
	else if (game->rays->h_length > game->rays->v_length)
	{
		game->rays->total_length = game->rays->v_length;
		draw_ray(game, 0, game->rays->total_length);
	}
}

void	get_angle(t_game *game)
{
	game->rays->angle = game->player.angle - (DR * 25);
	if (game->rays->angle < 0)
		game->rays->angle += 2 * M_PI;
	if (game->rays->angle > 2 * M_PI)
		game->rays->angle -= 2 * M_PI;
}

void	reset_angle(t_game *game)
{
	if (game->rays->angle < 0)
		game->rays->angle += 2 * M_PI;
	if (game->rays->angle >= 2 * M_PI)
		game->rays->angle -= 2 * M_PI;
}

void	cast_rays(t_game *game)
{
	get_angle(game);
	game->rays->ray = 0;
	while (game->rays->ray < 240)
	{
		reset_angle(game);
		reset_horizontal(game);
		horizontal_direction(game);
		cast_horizontal(game);
		reset_vertical(game);
		vertical_direction(game);
		cast_vertical(game);
		chose_lenght(game);
		draw_window(game);
		game->rays->angle += DR / 4;
		game->rays->ray++;
	}
}
