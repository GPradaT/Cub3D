/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:18:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/05/15 13:54:39 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_map(t_game *game, char *line)
{
	int		i;
	static int		player;
	static int		mapX = 0;
	player = 0;
	i = -1;
	while (line[++i])
	{
		printf("caracter que leo --> %c\n", line[i]);
		if (line[i] == 'F' || line[i] == 'C')
			parse_color(game, line);
		if (player > 1)
		{
			ft_putstr_fd("Error\nInvalid map, cannot be more than 1 player\n", 2);
			return (FAILURE);
		}
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			game->player.x = i;
			game->player.y = game->map.mapY;
			game->player.angle = line[i];
			player++;
		}
		if (line[i] != ' ' || line[i] != '\t' || line[i] != '1' || line[i] != '0'
			|| line[i] != 'N' || line[i] != 'S'
			|| line[i] != 'E' || line[i] != 'W')
		{
			ft_putstr_fd("Error\nInvalid map\n", 2);
			return (FAILURE);
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
	char	*color;

	color = line;
	if (!line)
	{
		ft_putstr_fd("Error\nInvalid color\n", 2);
		return ;
	}
	if (line[0] == 'F')
	{
		i = 0;
		color = ft_strdup(line + 2);
		while (line[i] != ',')
			i++;
		char *j = malloc(sizeof(char) * i - 1);
		ft_strlcpy(j, color, i - 1);
		game->map.floor_color.r = ft_atoi(j);
		free(j);
		free(color);
		color = ft_strdup(line + i + 1);
		int i2 = i;
		i = 0;
		while (color[i] != ',')
			i++;
		char *k = malloc(sizeof(char) * i + 1);
		ft_strlcpy(k, color, i + 1);
		game->map.floor_color.g = ft_atoi(k);
		free(k);
		free(color);
		color = ft_strdup(line + i2 + i + 1);
		i = 0;
		while (color[i] != ',' && color[i] != '\0')
			i++;
		char *l = malloc(sizeof(char) * i);
		ft_strlcpy(l, color, i - 1);
		game->map.floor_color.b = ft_atoi(l);
		free(l);
		free(color);
	}
	else if (line[0] == 'C')
	{
		i = 0;
		color = ft_strdup(line + 2);
		while (line[i] != ',')
			i++;
		char *j = malloc(sizeof(char) * i - 1);
		ft_strlcpy(j, color, i - 1);
		game->map.ceiling_color.r = ft_atoi(j);
		free(j);
		free(color);
		color = ft_strdup(line + i + 1);
		int i2 = i;
		i = 0;
		while (color[i] != ',')
			i++;
		char *k = malloc(sizeof(char) * i + 1);
		ft_strlcpy(k, color, i + 1);
		game->map.ceiling_color.g = ft_atoi(k);
		free(k);
		free(color);
		color = ft_strdup(line + i2 + i + 1);
		i = 0;
		while (color[i] != ',' && color[i] != '\0')
			i++;
		char *l = malloc(sizeof(char) * i);
		ft_strlcpy(l, color, i - 1);
		game->map.ceiling_color.b = ft_atoi(l);
		free(l);
		free(color);
	}
}

void	parse_texture_and_colors(t_game *game, char *line)
{
	int		i;

	i		= 0;
	if (!line)
	{
		ft_putstr_fd("Error\nInvalid texture\n", 2);
		return ;
	}
	while (ft_isspace(line[i]) == TRUE)
		i++;
	{
		line++;
	}
	if (strncmp(line, "NO", 2) == 0)
	{
		game->map.north_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.north_texture);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		game->map.south_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.south_texture);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		game->map.east_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.east_texture);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		game->map.west_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.west_texture);
	}
	else if (strncmp(line, "F", 1) == 0)
	{
		parse_color(game, line);
		printf("floor color: %d %d %d\n", game->map.floor_color.r, game->map.floor_color.g, game->map.floor_color.b);
	}
	else if (strncmp(line, "C", 1) == 0)
	{
		parse_color(game, line);
		printf("ceiling color: %d %d %d\n", game->map.ceiling_color.r, game->map.ceiling_color.g, game->map.ceiling_color.b);
	}
}

int	textures_and_colors_get(t_game *game)
{
	if (game->map.north_texture && game->map.south_texture
		&& game->map.east_texture && game->map.west_texture
		&& game->map.floor_color.r != -1 && game->map.floor_color.g != -1
		&& game->map.floor_color.b != -1 && game->map.ceiling_color.r != -1
		&& game->map.ceiling_color.g != -1 && game->map.ceiling_color.b != -1)
		return (TRUE);
	return (FALSE);
}

int	parse_file(t_game *game, char *argv)
{
	int		fd;
	char	*line;

	game->map.width = 100;
	game->map.height = 100;
	game->map.floor_color.b = -1;
	game->map.floor_color.g = -1;
	game->map.floor_color.r = -1;
	game->map.ceiling_color.b = -1;
	game->map.ceiling_color.g = -1;
	game->map.ceiling_color.r = -1;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid file\n", 2);
		return (FAILURE);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("line: %s\n", line);
		while (line[0] == ' ')
			line++;
		parse_texture_and_colors(game, line);
		if (textures_and_colors_get(game) == TRUE)
			break;
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			return (printf("no hay mapa en el archivo"), FAILURE);
		printf("line: %s\n", line);
		parse_map(game, line);
	}
	return (close(fd));
}