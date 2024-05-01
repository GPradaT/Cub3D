/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:36:56 by kmb               #+#    #+#             */
/*   Updated: 2024/05/02 00:49:04 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void cast_horizontal_ray(t_game *game)
{
    game->rays->angle = game->player.angle;
    game->rays->ray = 0;
    while ( game->rays->ray < 1)
    {
        game->rays->deapht_of_field = 0;
        float aTan = -1 / tan(game->rays->angle);
        if (game->rays->angle > M_PI)
        {
            game->rays->ray_y = (((int)game->player.y >> 6) << 6) - 0.0001;
            game->rays->ray_x = (game->player.y - game->rays->ray_y) * aTan + game->player.x;
            game->rays->y_offset = -64;
            game->rays->x_offset = -game->rays->y_offset * aTan;
        }
        if (game->rays->angle < M_PI)
        {
            game->rays->ray_y = (((int)game->player.y >> 6) << 6) + 64;
            game->rays->ray_x = (game->player.y - game->rays->ray_y) * aTan + game->player.x;
            game->rays->y_offset = 64;
            game->rays->x_offset = -game->rays->y_offset * aTan;
        }
        if (game->rays->angle == 0 || game->rays->angle == M_PI)
        {
            game->rays->ray_x = game->player.x;
            game->rays->ray_y = game->player.y;
            game->rays->deapht_of_field = 8;
        }
        while (game->rays->deapht_of_field < 8)
        {
            game->rays->mx = (int)game->rays->ray_x >> 6;
            game->rays->my = (int)game->rays->ray_y >> 6;
            if (game->rays->mx >= 0 && game->rays->mx < MAP_WIDTH 
            && game->rays->my >= 0 && game->rays->my < MAP_HEIGHT) {
                game->rays->mp = game->rays->my * MAP_WIDTH + game->rays->mx;
            }
            if (game->rays->mp < MAP_WIDTH * MAP_HEIGHT && map[game->rays->mp] == 1)
                game->rays->deapht_of_field = 8;
            else
            {
                game->rays->ray_x += game->rays->x_offset;
                game->rays->ray_y += game->rays->y_offset;
                game->rays->length = sqrt(pow(game->rays->ray_x - game->player.x, 2) + \
                pow(game->rays->ray_y - game->player.y, 2));
                game->rays->deapht_of_field++;
            }
        }
        game->rays->ray++;
    }
}

void cast_vertical_ray(t_game *game)
{
    game->rays->angle = game->player.angle;
    game->rays->ray = 0;
    while ( game->rays->ray < 1)
    {
        game->rays->deapht_of_field = 0;
        float nTan = -tan(game->rays->angle);
        if (game->rays->angle > M_PI_2 && game->rays->angle < 3 * M_PI_2)
        {
            game->rays->ray_x = (((int)game->player.x >> 6) << 6) - 0.0001;
            game->rays->ray_y = (game->player.x - game->rays->ray_x) * nTan + game->player.y;
            game->rays->x_offset = -64;
            game->rays->y_offset = -game->rays->x_offset * nTan;
        }
        if (game->rays->angle < M_PI_2 || game->rays->angle > 3 * M_PI_2)
        {
            game->rays->ray_x = (((int)game->player.x >> 6) << 6) + 64;
            game->rays->ray_y = (game->player.x - game->rays->ray_x) * nTan + game->player.y;
            game->rays->x_offset = 64;
            game->rays->y_offset = -game->rays->x_offset * nTan;
        }
        if (game->rays->angle == M_PI_2 || game->rays->angle == 3 * M_PI_2)
        {
            game->rays->ray_x = game->player.x;
            game->rays->ray_y = game->player.y;
            game->rays->deapht_of_field = 8;
        }
        while (game->rays->deapht_of_field < 8)
        {
            game->rays->mx = (int)game->rays->ray_x >> 6;
            game->rays->my = (int)game->rays->ray_y >> 6;
            if (game->rays->mx >= 0 && game->rays->mx < MAP_WIDTH && game->rays->my >= 0 && game->rays->my < MAP_HEIGHT) {
                game->rays->mp = game->rays->my * MAP_WIDTH + game->rays->mx;
            }
            if (game->rays->mp < MAP_WIDTH * MAP_HEIGHT && map[game->rays->mp] == 1)
                game->rays->deapht_of_field = 8;
            else
            {
                game->rays->ray_x += game->rays->x_offset;
                game->rays->ray_y += game->rays->y_offset;
                game->rays->length = sqrt(pow(game->rays->ray_x - game->player.x, 2) + pow(game->rays->ray_y - game->player.y, 2));
                game->rays->deapht_of_field++;
            }
        }
        game->rays->ray++;
    }
}