/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:13:19 by akambou           #+#    #+#             */
/*   Updated: 2024/06/19 02:42:43 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//---->>> me falta trasladar comprobar si es path para meter el color por textura o por color
//----> me falta controlar que soolo haya  1 jugador  de vdd con el mapa que tengo de colorfulled

void	init_floor_ceiling_and_doors(t_game *game)
{
	game->data.f_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/floor1.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.floor_addr = mlx_get_data_addr(game->data.f_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.c_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/metal1.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.ceiling_addr = mlx_get_data_addr(game->data.c_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.door_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/door.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.door_addr = mlx_get_data_addr(game->data.door_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.door1_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/door_o.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.door1_addr = mlx_get_data_addr(game->data.door1_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
}

int	init_textures(t_game *game)
{
	init_hud(game);
	if (invalid_texture(game))
		return (FAILURE);
	game->data.n_addr = mlx_get_data_addr(game->data.n_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.s_addr = mlx_get_data_addr(game->data.s_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	game->data.w_addr = mlx_get_data_addr(game->data.w_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	game->data.e_addr = mlx_get_data_addr(game->data.e_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	if (!game->data.n_addr || !game->data.s_addr || !game->data.w_addr \
		|| !game->data.e_addr)
		return (FAILURE);
	init_floor_ceiling_and_doors(game);
	return (SUCCESS);
}

int	init_window(t_game *game)
{
	game->data.mlx_ptr = mlx_init();
	if (init_textures(game))
	 return (-12);
	game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, \
	1200, 800, "Game");
	game->data.img = mlx_new_image(game->data.mlx_ptr, \
	1200, 800);
	game->data.addr = mlx_get_data_addr(game->data.img, \
	&game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	return (SUCCESS);
}

int	init_game(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	init_map(game);
	init_window(game);
	spawn_player(game);
	game->player.angle -= (M_PI / 6);
	game->map.height = game->map.mapy;
	game->map.width = game->map.mapx;
	game->map.win_h = (game->map.mapy * game->map.maps);
	game->map.win_w = (game->map.mapx * game->map.maps);
	return (SUCCESS);
}
