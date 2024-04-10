/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:42:40 by gprada-t          #+#    #+#             */
/*   Updated: 2024/04/10 15:02:19 by gprada-t         ###   ########.fr       */
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

int	parse_map(t_game *game, char *argv)
{
	int		i;
	int		fd;

	i = -1;
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'R')
			parse_resolution(game, line);
		else if (line[0] == 'F' || line[0] == 'C')
			parse_color(game, line);
		else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
			parse_texture(game, line);
		else if (line[0] == '1' || line[0] == '0' || line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
			parse_map(game, line);
		else
		{
			ft_putstr_fd("Error\nInvalid map\n", 2);
			return (FAILURE);
		}
		free(line);
	}
	{
		if (argv[i] != ' ' || argv[i] != '1' || argv[i] != '0'
			|| argv[i] != 'N' || argv[i] != 'S'
			|| argv[i] != 'E' || argv[i] != 'W')
		{
			ft_putstr_fd("Error\nInvalid map\n", 2);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_game *game;

	if (argc == 2)
		if (parse_map(argv[1]) == FAILURE)
			return (FAILURE);
	else
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
