/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefill_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_cand_1d(int *cand, int size)
{
	int	idx;
	int	total;
	int	full_mask;

	total = size * size;
	full_mask = (1 << size) - 1;
	idx = 0;
	while (idx < total)
	{
		cand[idx] = full_mask;
		idx++;
	}
}

int	mask_max_height(int *mask, int size, int max_h)
{
	int	before;
	int	allowed;

	if (max_h == -2)
		allowed = 1 << (size - 1);
	else
	{
		if (max_h < 1)
			return (-1);
		if (max_h >= size)
			return (0);
		allowed = (1 << max_h) - 1;
	}
	before = *mask;
	*mask &= allowed;
	if (*mask == 0)
		return (-1);
	if (*mask != before)
		return (1);
	return (0);
}

int	calc_max_h(int size, int clue, int step)
{
	if (clue == 1 && step == 0)
		return (-2);
	if (clue == 1)
		return (size - 1);
	return (size - clue + 1 + step);
}

static int	find_set_digit(int mask, int size)
{
	int	digit;

	digit = 1;
	while (digit <= size)
	{
		if (mask & (1 << (digit - 1)))
			return (digit);
		digit++;
	}
	return (0);
}

int	lock_single(t_data *master, int *cand, int idx, int *rc)
{
	int	digit;
	int	bit;
	int	i;

	digit = find_set_digit(cand[idx], master->size);
	if (digit == 0 || !check_no_duplicate(master, rc[0], rc[1], digit))
		return (-1);
	bit = 1 << (digit - 1);
	master->grid[rc[0]][rc[1]] = (char)(digit + '0');
	master->row_masks[rc[0]] |= bit;
	master->col_masks[rc[1]] |= bit;
	cand[idx] = bit;
	i = -1;
	while (++i < master->size)
	{
		if (i != rc[1])
			cand[rc[0] * master->size + i] &= ~bit;
		if (i != rc[0])
			cand[i * master->size + rc[1]] &= ~bit;
	}
	return (1);
}
