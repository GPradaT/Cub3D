/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:42:40 by gprada-t          #+#    #+#             */
/*   Updated: 2024/04/13 18:39:02 by gprada-t         ###   ########.fr       */
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

void	parse_color(t_game *game, char *line)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (line[i] != ',')
		i++;
	r = ft_atoi(line + 1);
	g = ft_atoi(line + i + 1);
	b = ft_atoi(line + i + 1);
}

void	parse_texture(t_game *game, char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] != ' ')
		i++;
	path = ft_strdup(line + i);
}

int	parse_map(t_game *game, char *argv)
{
	int		i;
	int		fd;
	char	*line;
	i = -1;
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd) > 0)
	{
		if (line[0] == 'F' || line[0] == 'C')
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
}

void	parse_map(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' || line[i] != '1' || line[i] != '0'
			|| line[i] != 'N' || line[i] != 'S'
			|| line[i] != 'E' || line[i] != 'W')
		{
			ft_putstr_fd("Error\nInvalid map\n", 2);
			return (FAILURE);
		}
	}
	return (SUCCESS);
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
			if (parse_map(game, argv[1]) == FAILURE)
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
