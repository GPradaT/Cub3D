/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:38:00 by kmb               #+#    #+#             */
/*   Updated: 2024/05/02 00:57:05 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_game(t_game *game)
{
    int x = 0, y = 0;
    int mapX = 8, mapY = 8, mapS = 64;


    game->mlx.mlx_ptr = mlx_init();
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");

    game->map.width = 0;
    game->map.height = 0;
    game->map.floor_color.b = 128;
    game->map.floor_color.g = 128;
    game->map.floor_color.r = 128;
    game->map.ceiling_color.b = 0;
    game->map.ceiling_color.g = 0;
    game->map.ceiling_color.r = 0;

    while ( y < mapY)
    {
        x = 0;
        while (x < mapX)
        {
            if (map[y * mapX + x] == 3)
            {
                game->player.x = x * mapS;
                game->player.y = y * mapS;
                return;
            }
            x++;
        }
        y++;
    }
}

int loop(t_game *game)
{
    draw_map(game);
    cast_horizontal_ray(game);
    cast_vertical_ray(game);
    draw_player_angle(game, game->rays->length);
    draw_player(game, 25, 25, 0xFF0000);
    return 0;
}