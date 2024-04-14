/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:42:40 by gprada-t          #+#    #+#             */
/*   Updated: 2024/04/14 09:19:53 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_game	*init_game()
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	game->map = (t_map *)malloc(sizeof(t_map));
	game->map->rows = 0;
	game->map->cols = 0;
	return (game);
	return (NULL);
}

int	check_path(char *path)
{
	int		i;

	i = ft_strlen(path);
	if (path[i - 1] == 'b' && path[i - 2] == 'u' && path[i - 3] == 'c' && path[i - 4] == '.')
		return (SUCCESS);
	return (FAILURE);
}

int main(int argc, char **argv)
{
	t_game *game;

	if (argc == 2)
	{
		if(check_path(argv[1]) == SUCCESS)
		{
			game = init_game();
			if (parse_file(game, argv[1]) == FAILURE)
				return (FAILURE);

		}
		else
		{
			ft_putstr_fd("Error\nInvalid file\n", 2);
			return (FAILURE);
		}
	}
	else
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
