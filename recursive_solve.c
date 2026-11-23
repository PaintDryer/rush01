/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_solve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 18:32:41 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/22 21:50:56 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// assume start from 0 to end
// 1 is solved
int	recursive_solve(t_data *data, int i, int size)
{
	int	num;

	if (i && (i % size == 0 || i > size * (size - 1)) && !valid_lines(data, i))
		return (0);
	if (i == size * size)
		return (1);
	if (data->board[i] != 0)
		return (recursive_solve(data, i + 1, size));
	num = size + 1;
	while (num-- > 1)
	{
		if (validate(data, i / size, i % size, num))
		{
			data->board[i] = num;
			if (set_mask(data, i / size, i % size, num))
			{
				if (recursive_solve(data, i + 1, size))
					return (1);
				remove_mask(data, i / size, i % size, num);
			}
			data->board[i] = 0;
		}
	}
	return (0);
}
// return (0) is a fail state;

// precheck edges based on placed max number
int	validate(t_data *data, int row, int col, int num)
{
	if (!validate_mask(data, row, col, num))
		return (0);
	return (1);
}
