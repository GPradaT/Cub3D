/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:23:50 by mgraaf            #+#    #+#             */
/*   Updated: 2024/07/05 12:54:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_c(char const *s, char c)
{
	int	i;
	int	c_count;

	i = 0;
	c_count = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
			c_count++;
		while (s[i] != c && i < ft_strlen(s))
			i++;
		i++;
	}
	return (c_count);
}

int	strlen_c(char const *s, char c, int s_i)
{
	int	i;

	i = 0;
	while (s[s_i] != c && s[s_i] != '\0')
	{
		s_i++;
		i++;
	}
	return (i);
}

char	**create_arr(char const *s, char c, int c_count, char **split_arr)
{
	int	s_i;
	int	s_a_i;
	int	num_of_char;

	s_i = 0;
	s_a_i = 0;
	num_of_char = 0;
	while (s_a_i < c_count)
	{
		while (s[s_i] == c)
			s_i++;
		num_of_char = strlen_c(s, c, s_i);
		split_arr[s_a_i] = (char *)ft_calloc(num_of_char + 1, sizeof(char));
		if (!split_arr)
			return (NULL);
		ft_strlcpy(split_arr[s_a_i], &s[s_i], num_of_char + 1);
		s_i += num_of_char;
		s_a_i++;
	}
	return (split_arr);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

char	**ft_split(char const *s, char c)
{
	int		c_count;
	char	**split_arr;

	if (!s)
		return (NULL);
	c_count = count_c(s, c);
	split_arr = ft_calloc(c_count + 1, sizeof(char *));
	if (!split_arr)
		return (NULL);
	if (!s || c_count == 0)
		return (split_arr);
	if (!create_arr(s, c, c_count, split_arr))
	{
		free_arr(split_arr);
		return (NULL);
	}
	return (split_arr);
}
