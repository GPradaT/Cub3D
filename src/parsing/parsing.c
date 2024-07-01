/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:18:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/27 09:51:03 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_path(char *str)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i + j] && !ft_isspace(str[i + j]))
		j++;
	path = malloc(j + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, str + i, j + 1);
	return (path);
}

int	parse_texture_and_colors(t_game *game, char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!line)
		return (cub_error("Error\nInvalid texture\n", FAILURE));
	while (ft_isspace(line[i]) == TRUE)
		i++;
	new_line = ft_strdup(line + i);
	if (ft_strncmp(new_line, "NO", 2) == 0)
		game->map.north_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "SO", 2) == 0)
		game->map.south_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "EA", 2) == 0)
		game->map.east_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "WE", 2) == 0)
		game->map.west_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "F", 1) == 0)
	{
		game->map.floor.texture = get_path(new_line + 2);
		if (!game->map.floor.texture)
			return (cub_error("Error\nInvalid texture\n", FAILURE));
		if (game->map.floor.texture[0] == '.'
			&& game->map.floor.texture[1] == '/')
			game->map.floor_texture = game->map.floor.texture;
		else
			free(game->map.floor.texture);
		if (parse_color(game, new_line) == -3)
			return (cub_error("Error\nInvalid color\n", FAILURE));
	}
	else if (ft_strncmp(new_line, "C", 1) == 0)
	{
		game->map.ceiling.texture = get_path(new_line + 2);
		if (!game->map.ceiling.texture)
			return (cub_error("Error\nInvalid texture\n", FAILURE));
		if (game->map.ceiling.texture[0] == '.'
			&& game->map.ceiling.texture[1] == '/')
			game->map.ceiling_texture = game->map.ceiling.texture;
		else
			free(game->map.ceiling.texture);
		if (parse_color(game, new_line) == -3)
			return (FAILURE);
	}
	free(new_line);
	return (SUCCESS);
}

void	chose_direction(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player.angle = -1;
	}
	else if (c == 'S')
	{
		game->player.angle = M_PI - 1;
	}
	else if (c == 'E')
	{
		game->player.angle = M_PI_2 - 1;
	}
	else if (c == 'W')
	{
		game->player.angle = (3 * M_PI_2 - 1);
	}
}

int	parse_map(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '0'
			|| line[i] == '1' || line[i] == '2'
			|| line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W'
			|| line[i] == '7'))
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			game->player.x = i;
			game->player.y = game->map.mapy;
			game->map.player += 1;
			chose_direction(game, line[i]);
			if (game->map.player > 1)
			{
				return (printf("i = %d\n", i), cub_error("Error\n\
				Only 1 player videogame sorry\n", FAILURE));
			}
		}
		i++;
	}
	game->map.temp_map = ft_strjoin(game->map.temp_map, line);
	return (SUCCESS);
}

int	parse_file(t_game *game, char *argv)
{
	int		fd;
	char	*line;
	char	*temp;

	init_parsing_data(game);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (cub_error("Error: Invalid FILE\n", 2));
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (cub_error("Error: Empty file\n", 2));
	}
	while (line && !textures_and_colors_get(game))
	{
		temp = line;
		while (ft_isspace(*temp))
			temp++;
		if (!*temp)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (parse_texture_and_colors(game, temp))
		{
			free(line);
			close(fd);
			return (FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!have_to_paint(&game->map))
	{
		close(fd);
		return (cub_error("Error\nInvalid color\n", FAILURE));
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (parse_map(game, line) != SUCCESS)
		{
			free(line);
			close(fd);
			return (FAILURE);
		}
		free (line);
	}
	close(fd);
	return (SUCCESS);
}
