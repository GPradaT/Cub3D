/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/04/27 05:49:40 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 3, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
}; 

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W)
    {
        game->player.x += game->player.delta_x;
        game->player.y += game->player.delta_y;
    }
    else if (keycode == KEY_S)
    {
        game->player.x -= game->player.delta_x;
        game->player.y -= game->player.delta_y;
    }
    else if (keycode == KEY_A)
    {
        game->player.angle -= 0.1;
        if (game->player.angle > 0)
            game->player.angle += (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }   
    else if (keycode == KEY_D)
    {
        game->player.angle += 0.1;
        if (game->player.angle > 0)
            game->player.angle -= (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }
    else if (keycode == KEY_ESC)
        exit(0);

    return 0;
}

int main(void)
{
    t_game game;

    init_game(&game);
    mlx_hook(game.mlx.win_ptr, 2, 1L<<0, key_press, &game);
    mlx_loop_hook(game.mlx.mlx_ptr, loop, &game);
    mlx_loop(game.mlx.mlx_ptr);
}