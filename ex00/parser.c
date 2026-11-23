/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	extract_size_from_clues(int *size, char *str)
{
	int	clues_length;

	clues_length = ft_strlen(str);
	if ((clues_length + 1) % 8 != 0)
		return (1);
	*size = (clues_length + 1) / 8;
	return (0);
}

static int	clues_format_is_valid(int size, char *str)
{
	while (*str)
	{
		if (*str < '1' || *str > size + '0' || (*(str + 1)
				&& *(str + 1) != ' '))
			return (1);
		if (*(str + 1) == '\0')
			break ;
		str += 2;
	}
	return (0);
}

int	parser(t_data *master, char *str)
{
	if (extract_size_from_clues(&master->size, str))
		return (1);
	if (clues_format_is_valid(master->size, str))
		return (1);
	master->clues = save_clues(str, master->size);
	return (0);
}
