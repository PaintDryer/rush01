/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 18:45:29 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/22 21:30:34 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	validate_mask(t_data *data, int row, int col, int digit)
{
	if (data->row_mask[row] & itob(digit))
		return (0);
	if (data->col_mask[col] & itob(digit))
		return (0);
	return (1);
}

int	set_mask(t_data *data, int row, int col, int digit)
{
	int	bit;

	bit = itob(digit);
	if (data->row_mask[row] & bit || data->col_mask[col] & bit)
	{
		printf("invalid mask set");
		return (0);
	}
	else
	{
		data->row_mask[row] |= bit;
		data->col_mask[col] |= bit;
	}
	return (1);
}
// TRUE on success

void	remove_mask(t_data *data, int row, int col, int digit)
{
	data->row_mask[row] &= ~itob(digit);
	data->col_mask[col] &= ~itob(digit);
}
