/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/04/28 00:40:08 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_game(t_game *game)
{
    int x, y;

    game->mlx.mlx_ptr = mlx_init();
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, 1200, 900, "cub3d");

    game->rays->direction = 0;
    game->rays->length = 0;
    game->rays->hit_wall = 0;

    game->map.width = 0;
    game->map.height = 0;
    game->map.floor_color.b = 128;
    game->map.floor_color.g = 128;
    game->map.floor_color.r = 128;
    game->map.ceiling_color.b = 0;
    game->map.ceiling_color.g = 0;
    game->map.ceiling_color.r = 0;

    // Find the player's spawn position in the map
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x] == 3)
            {
                game->player.x = x * SCALE_X;
                game->player.y = y * SCALE_Y;
                return;
            }
        }
    }
}

int loop(t_game *game)
{
    draw_map(game);
    draw_player(game, 25, 25, 0xFF0000);
    draw_player_angle(game, 300);
    return 0;
}


void draw_map(t_game *game)
{
    int x, y, i, j = 0;

    y = 0;
    while (y < MAP_HEIGHT)
    {
        while (x < MAP_WIDTH)
        {
            while (i < SCALE_Y)
            {
                while (j < SCALE_X)
                {
                    if (map[y][x] == 1)
                        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, \
                        x * SCALE_X + j, y * SCALE_Y + i, 0x0000FF);
                    else
                        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, \
                        x * SCALE_X + j, y * SCALE_Y + i, 0x808080);
                    if (i == 0 || i == SCALE_Y - 1 || j == 0 || j == SCALE_X - 1)
                        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, \
                        x * SCALE_X + j, y * SCALE_Y + i, 0xFFFF00);
                    j++;
                }
                j = 0;
                i++;
            }
            i = 0;
            x++;
        }
        x = 0;
        y++;
    }
}