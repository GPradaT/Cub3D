/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:18:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/05/11 22:17:18 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_map(t_game *game, char *line)
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
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			game->player.x = i;
			game->player.y = game->map.mapY;
			game->player.angle = line[i];
		}
		if (line[i] == '1' || line[i] == '0')
			game->map.mapX++;
	}
	game->map.mapY++;
	game->map.map = ft_realloc(game->map.map, sizeof(char) * (game->map.mapX + 1));
	return (SUCCESS);
}
void	parse_color(t_game *game, char *line)
{
	int		i;

	i = 0;
	if (!line)
	{
		ft_putstr_fd("Error\nInvalid color\n", 2);
		return (FAILURE);
	}
	if (line[0] == 'F')
	{
		while (line[i] != ',')
			i++;
		game->map.floor_color.r = ft_atoi(line + i);
		while (line[i] != ',')
			i++;
		game->map.floor_color.g = ft_atoi(line + i);
		while (line[i] != ',')
			i++;
		game->map.floor_color.b = ft_atoi(line + i);
	}
	else if (line[0] == 'C')
	{
		while (line[i] != ',')
			i++;
		game->map.ceiling_color.r = ft_atoi(line + i);
		while (line[i] != ',')
			i++;
		game->map.ceiling_color.g = ft_atoi(line + i);
		while (line[i] != ',')
			i++;
		game->map.ceiling_color.b = ft_atoi(line + i);
	}
}

void	parse_texture(t_game *game, char *line)
{
	int		i;
	char	*path;
	i = 0;
	if (!line)
	{
		ft_putstr_fd("Error\nInvalid texture\n", 2);
		return (FAILURE);
	}
	if (line[i] == 'N')
	{
		while (line[i] != ' ')
			i++;
		game->map.north_texture = ft_strdup(line + i);
	}
	else if (line[i] == 'S')
	{
		while (line[i] != ' ')
			i++;
		game->map.south_texture = ft_strdup(line + i);
	}
	else if (line[i] == 'E')
	{
		while (line[i] != ' ')
			i++;
		game->map.east_texture = ft_strdup(line + i);
	}
	else if (line[i] == 'W')
	{
		while (line[i] != ' ')
			i++;
		game->map.west_texture = ft_strdup(line + i);
	}
}

int	parse_file(t_game *game, char *argv)
{
	int		i;
	int		fd;
	char	*line;
	i = -1;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid file\n", 2);
		return (FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
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
		line = get_next_line(fd);
	}
}
