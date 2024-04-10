/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:50:20 by gprada-t          #+#    #+#             */
/*   Updated: 2024/04/10 14:51:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <string.h>

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_screen
{
	void		*mlx;
	void		*win;
}				t_screen;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			cols;
}				t_map;

typedef struct s_game
{
	t_screen	*screen;
	t_data		img;
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	t_texture	*texture;
}				t_game;
