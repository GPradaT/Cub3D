/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:06:20 by akambou           #+#    #+#             */
/*   Updated: 2024/06/19 17:07:19 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	texture_pos_cf(t_game *game)
{
	game->data.texture_width = 64;
	game->data.texture_height = 64;
	game->data.current_dist = game->map.win_h / (2.0 * \
	game->rays->win_i - game->map.win_h);
	game->data.weight = game->data.current_dist / game->rays->v_length;
	game->data.current_ceiling_x = game->data.weight * \
	game->rays->ray_x + (1.0 - game->data.weight) * game->player.x;
	game->data.current_ceiling_y = game->data.weight * \
	game->rays->ray_y + (1.0 - game->data.weight) * game->player.y;
	game->data.texture_x = (int)(game->data.current_ceiling_x * \
	game->data.texture_width) % game->data.texture_width;
	game->data.texture_y = (int)(game->data.current_ceiling_y * \
	game->data.texture_height) % game->data.texture_height;
}

int	get_texture_color1(int *texture, int tex_x, \
int tex_y, t_game *game)
{
	int	index;

	if (tex_x < 0 || tex_x >= game->data.texture_width
		|| tex_y < 0 || tex_y >= game->data.texture_height)
		return (-1);
	index = tex_y * game->data.texture_width + tex_x;
	return (texture[index]);
}

int	get_texture_color(int *texture, t_game *game)
{
	int	index;

	if (game->data.texture_x < 0
		|| game->data.texture_x >= game->data.texture_width
		|| game->data.texture_x < 0
		|| game->data.texture_y >= game->data.texture_height)
		return (-1);
	index = game->data.texture_y * game->data.texture_width \
	+ game->data.texture_x;
	return (texture[index]);
}

void	get_texture_pos(t_game *game)
{
	if (game->rays->h_length < game->rays->v_length)
		game->data.wall_x = fmod(game->rays->horizontal_x, \
		game->data.texture_width);
	else
		game->data.wall_x = fmod(game->rays->vertical_y, \
		game->data.texture_width);
	game->data.texture_x = (int)(game->data.wall_x);
	game->data.texture_y = (int)((game->rays->win_i - \
	game->rays->line_offset) / (float)game->rays->line_height \
	* game->data.texture_height);
}

void	select_wall(t_game *game)
{
	if (is_north(game))
	{
		get_texture_pos(game);
		game->data.color = get_texture_color((int *)game->data.n_addr, game);
	}
	else if (game->rays->win_i < game->map.win_h && game->rays->h_length \
	< game->rays->v_length && game->rays->angle < M_PI)
	{
		get_texture_pos(game);
		game->data.color = get_texture_color((int *)game->data.s_addr, game);
	}
	else if (is_west(game))
	{
		get_texture_pos(game);
		game->data.color = get_texture_color((int *)game->data.w_addr, game);
	}
	else
	{
		get_texture_pos(game);
		game->data.color = get_texture_color((int *)game->data.e_addr, game);
		check_door(game);
	}
}
