/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/05/02 00:54:52 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void draw_map(t_game *game)
{
    int x = 0, y = 0, i = 0, j = 0;
    int mapX = 8, mapY = 8, mapS = 64;
    int cellSize = mapS - 1;

    while (y < mapY)
    {
        x = 0;
        while (x < mapX)
        {
            int cell = map[y * mapX + x];
            int color = cell == 1 ? 0x0000FF : 0x808080;
            i = 0;
            while (i < cellSize)
            {
                j = 0;
                while (j < cellSize)
                {
                    mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x * mapS + j, y * mapS + i, color);
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}