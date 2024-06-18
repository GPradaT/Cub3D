/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:57:05 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/18 19:16:19 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_doors(t_game *game)
{
	game->data.door_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/door.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	game->data.door1_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	"./textures/door_o.xpm", &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.door_texture || !game->data.door1_texture)
		return cub_error("Error\nInvalid DOOR texture\n", FAILURE);
	game->data.door_addr = mlx_get_data_addr(game->data.door_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	game->data.door1_addr = mlx_get_data_addr(game->data.door1_texture, \
	&game->data.bits_per_pixel, &game->data.line_length, \
	&game->data.endian);
	if (!game->data.door_addr || !game->data.door1_addr)
		return (cub_error("Error\nInvalid DOOR image\n", FAILURE));
}

int	invalid_texture(t_game *game)
{
	game->data.n_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.north_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.n_texture)
		return cub_error("Error\nInvalid NORTH texture\n", FAILURE);
		game->data.s_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.south_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.s_texture)
		return cub_error("Error\nInvalid SOUTH texture\n", FAILURE);
		game->data.w_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.west_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.w_texture)
		return cub_error("Error\nInvalid WEST texture\n", FAILURE);
	game->data.e_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.east_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.e_texture)
		return cub_error("Error\nInvalid EAST texture\n", FAILURE);

	return (SUCCESS);
}
