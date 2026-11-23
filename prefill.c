/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 17:59:33 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/22 23:41:36 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header.h"

/*
void	prefill(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size * 4)
	{
		//if (data->clues[i] == 1)
			//min_clue(data, i);
		i++;
	}
}

void	min_clue(t_data *data, int i)
{
	int	size;

	(void)i;
	(void)data;
	(void)size;

	size = data->size;
	if (i >= 0 && i < size)
		data->board[i] = size;
	else if (i >= size && i < size * 2)
		data->board[i + size * 2] = size;
	else if (i >= size * 2 && i < size * 3)
		data->board[(i - size * 2) * size] = size;
	else
		data->board[(i - size * 3) * size + (size - 1)] = size;
}
*/
