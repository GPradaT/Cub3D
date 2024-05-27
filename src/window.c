/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/05/26 10:42:31 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_3D(t_game *game)
{
    int i;
    int j;

    game->map.win_h = game->map.mapY * game->map.mapS;
    game->map.win_w = game->map.mapX * game->map.mapS;
    int ray_width = game->map.win_w / 120;
    game->rays->line_height = (game->map.mapS * game->map.win_h) / game->rays->total_length;
    
    if (game->rays->line_height > game->map.win_h)
        game->rays->line_height = game->map.win_h;
    game->rays->line_offset = game->map.win_h / 2 - game->rays->line_height / 2;
    i = 0;
    while (i < game->rays->line_offset)
    {
        j = 0;
        while (j < ray_width)
        {
            mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr,
            game->rays->ray * ray_width + j, i, 0x00FF00);
            j++;
        }
        i++;
    }

    while (i < game->rays->line_height + game->rays->line_offset)
    {
        j = 0;
        while (j < ray_width)
        {
            if (i < game->map.win_h) 
                mlx_pixel_put(game->mlx.mlx_ptr, \
                game->mlx.win_ptr, game->rays->ray * \
                ray_width + j, i, 0xFF0000);
            j++;
        }
        i++;
    }
    while (i < game->map.win_h)
    {
        j = 0;
        while (j < ray_width)
        {
            mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, \
            game->rays->ray * ray_width + j, i, 0x0000FF);
            j++;
        }
        i++;
    }
}

void draw_map(t_game *game)
{
    
    game->map.y = 0;
    game->map.mapS /= 4;
    game->map.cellSize /= 4;
    
    // Aqui se dibuja el mapa en y
    while ( game->map.y <  game->map.mapY)
    {
        game->map.x = 0;
        // Aqui se dibuja el mapa en x
        while ( game->map.x <  game->map.mapX)
        {
            // Aqui se obtiene la celda del mapa
            game->map.cell = game->map.map[ game->map.y * \
            game->map.mapX +  game->map.x];
            game->map.color =  game->map.cell \
            == 1 ? 0x0000FF : 0x808080;
            game->map.i = 0;
            // Aqui se dibuja la celda del mapa en y
            while ( game->map.i <  game->map.cellSize)
            {
                game->map.j = 0;
                // Aqui se dibuja la celda del mapa en x
                while ( game->map.j <  game->map.cellSize)
                {
                    mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr2,\
                    game->map.x * game->map.mapS + game->map.j, \
                    game->map.y * game->map.mapS + game->map.i, \
                    game->map.color);
                    game->map.j++;
                }
                game->map.i++;
            }
            game->map.j = 0;
            // Aqui se dibuja la linea de la celda
            game->map.x++;
        }
        game->map.y++;
    }
    game->map.mapS *= 4;
    game->map.cellSize *= 4; 

}