/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 17:18:11 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/22 21:31:31 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "string.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

t_data	*new_data(char *str)
{
	t_data	*data;
	int		size;
	int		i;

	size = ft_strlen(str);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->size = (size + 1) / 8;
	data->board = ft_calloc(data->size * data-> size, sizeof(int));
	data->clues = ft_calloc((size + 1) / 2, sizeof(int));
	data->mask = ((1 << data->size) - 1);
	data->row_mask = ft_calloc(data->size, sizeof(int));
	data->col_mask = ft_calloc(data->size, sizeof(int));
	i = 0;
	while (i < data->size * 4)
	{
		data->clues[i] = str[2 * i] - '0';
		i++;
	}
	return (data);
}

void	free_data(t_data *data)
{
	free(data->board);
	free(data->clues);
	free(data->row_mask);
	free(data->col_mask);
	free(data);
}
