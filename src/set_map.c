/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:47:08 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/10 13:28:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		calculate_size(const char *map)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (map[++i])
	{
		if (map[i] != '\t' && map[i] != '\n')
			size++;
		else if (map[i] == '\t')
			size += 4;
	}
	return (size);
}

int		*str_to_int_array(char *map, int max_x)
{
	int i;
	int j;
	int *array;
	int len;

	i = 0;
	j = 0;
	len = calculate_size(map);
	printf("mapsize-->: %d\n", len);
	array = malloc(sizeof(int) * len);
	if (!array)
		return (NULL);
	int index = 0;
	while (map[i] && index < len)
	{
		if (map[i] == '0') {
			array[index++] = 0;
		}
		else if (map[i] == '1')
			array[index++] = 1;
		else if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
			array[index++] = 3;
		else if (map[i] == ' ')
			array[index++] = 2;
		else if (map[i] == '\n' && (index % max_x) != 0)
			while (index % max_x != 0)
				array[index++] = 2;
		else if (map[i] == '\t') {
			for (int k = 0; k < 4; k++){
				array[index++] = 2;
			}
		}
		i++;
	}
	return (array);
}

void	setting_map_x_map_y(char *str_map, t_game *game)
{
	int i;
	int line = 0;

	i = -1;
	while (str_map[++i])
	{
		if (str_map[i] == '\n')
		{
			if (line > game->map.mapX)
				game->map.mapX = line;
			line = 0;
			game->map.mapY++;
		}
		else
		{
			if (str_map[i] == '\t')
				line += 4;
			else
				line++;
		}
	}
	game->map.mapY++;
}

int		check_closed_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	if (game->map.mapX < 3 || game->map.mapY < 3)
		return (cub_error("Error\nToo Small map\n", FAILURE));
	while (i < game->map.mapX * game->map.mapY)
	{
		if (game->map.map[i] == 0 && (game->map.map[i + 1] == 2 || game->map.map[i - 1] == 2))
			return (cub_error("Error\nInvalid map\n", FAILURE));
		i++;
	}
	return (SUCCESS);
}

int		mapping(t_game *game)
{
	while (*game->map.temp_map == '\n')
		game->map.temp_map++;
	if (!game->map.temp_map)
		return (cub_error("Error\nInvalid map\n", FAILURE));
	setting_map_x_map_y(game->map.temp_map, game);
	game->map.map = str_to_int_array(game->map.temp_map, game->map.mapX);
	//if (check_closed_map(game))
	//	return (cub_error("Error\nMap is open\n", FAILURE));
	return (SUCCESS);
}
