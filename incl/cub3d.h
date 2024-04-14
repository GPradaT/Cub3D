/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:50:20 by gprada-t          #+#    #+#             */
/*   Updated: 2024/04/13 18:34:49 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <string.h>

# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0


# define NUM_TEXTURES 4
# define TILE_SIZE 64
# define FOV 60
# define PI 3.14159265359


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

typedef struct s_file
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f;
	int			c;
}				t_file;
typedef struct s_game
{
	t_screen	*screen;
	t_data		img;
	t_map		*map;
	t_file		*file;
	void		*player;
	void		*ray;
	void		*texture;
}				t_game;

#endif
