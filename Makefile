# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 10:42:10 by gprada-t          #+#    #+#              #
#    Updated: 2024/04/14 09:17:27 by gprada-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf
MKFLAGS = --no-print-directory

LINKED_L = -lmath -lm -lmlx
FRAMEWRK = -framework OpenGL -framework AppKit

