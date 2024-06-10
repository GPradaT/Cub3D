/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/06/10 12:48:31 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// En este caso, la función do_map() se encarga de asignar los valores de la \
matriz map[] a la estructura map del juego.

int	cub_error(char *str, int error)
{
	while (*str)
		write (2, str++, 1);
	return (error);
}

int close_window(t_game *game)
{
	exit(0);
}

int main(int argc, char **argv)
{
	t_game game;
	int fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (FAILURE);
	}
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return (FAILURE);
	}
	if (parse_file(&game, argv[1]))
		return (FAILURE);
	if (mapping(&game))
		return (cub_error("Error\nInvalid map\n", FAILURE));
	init_game(&game);
	mlx_hook(game.data.win_ptr, 2, 1, key_press, &game);
	mlx_loop_hook(game.data.mlx_ptr, loop, &game);
	mlx_loop(game.data.mlx_ptr);
}
