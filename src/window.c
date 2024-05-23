/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/05/23 02:08:15 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_3D(t_game *game)
{
    int i;
    int j;

    game->map.win_h = game->map.mapY * game->map.mapS;
    game->map.win_w = game->map.mapX * game->map.mapS;
    int ray_width = game->map.win_w / 60;
    game->rays->line_height = (game->map.mapS * game->map.win_h) / game->rays->total_length;
    
    if (game->rays->line_height > game->map.win_h)
        game->rays->line_height = game->map.win_h;
    game->rays->line_offset = game->map.win_h / 2 - game->rays->line_height / 2;
    i = 0;
    while (i < game->rays->line_height)
    {
        j = 0;
        while (j < ray_width)
        {
            // Offset the y-coordinate by the height of the map grid
            int y_position = game->map.win_h + game->rays->line_offset + i;
            if (y_position < game->map.win_h * 2) 
                mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, game->rays->ray * ray_width + j, y_position, 0xFF0000);
            j++;
        }
        i++;
    }   
}

void draw_map(t_game *game)
{
    
    game->map.y = 0;
    game->map.height = game->map.mapY;
    game->map.width = game->map.mapX;
    
    // Draw the map
    while ( game->map.y <  game->map.mapY)
    {
        game->map.x = 0;
        // Draw the cell
        while ( game->map.x <  game->map.mapX)
        {
            game->map.cell = game->map.map[ game->map.y * \
            game->map.mapX +  game->map.x];
            game->map.color =  game->map.cell \
            == 1 ? 0x0000FF : 0x808080;
            game->map.i = 0;
            // Draw the cell size
            while ( game->map.i <  game->map.cellSize)
            {
                game->map.j = 0;
                while ( game->map.j <  game->map.cellSize)
                {
                    mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr,\
                    game->map.x * game->map.mapS + game->map.j, \
                    game->map.y * game->map.mapS + game->map.i, \
                    game->map.color);
                    game->map.j++;
                }
                game->map.i++;
            }
            game->map.j = 0;
            // Draw the grid
            while (game->map.j < game->map.mapS)
            {
                mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, \
                game->map.x * game->map.mapS + game->map.j, \
                game->map.y * game->map.mapS + game->map.cellSize, 0xFFFFFF);
                game->map.j++;
            }
            game->map.x++;
        }
        game->map.y++;
    }

}