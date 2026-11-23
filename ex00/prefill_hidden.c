/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefill_hidden.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	scan_row_digit(t_data *master, int *cand, int r, int digit)
{
	int	c;
	int	bit;
	int	count;
	int	target_col;

	bit = 1 << (digit - 1);
	if (master->row_masks[r] & bit)
		return (-2);
	count = 0;
	target_col = -1;
	c = -1;
	while (++c < master->size)
	{
		if (master->grid[r][c] == '0' && (cand[r * master->size + c] & bit))
		{
			count++;
			target_col = c;
		}
	}
	if (count == 0)
		return (-1);
	if (count == 1)
		return (target_col);
	return (-2);
}

static int	scan_col_digit(t_data *master, int *cand, int c, int digit)
{
	int	r;
	int	bit;
	int	count;
	int	target_row;

	bit = 1 << (digit - 1);
	if (master->col_masks[c] & bit)
		return (-2);
	count = 0;
	target_row = -1;
	r = -1;
	while (++r < master->size)
	{
		if (master->grid[r][c] == '0' && (cand[r * master->size + c] & bit))
		{
			count++;
			target_row = r;
		}
	}
	if (count == 0)
		return (-1);
	if (count == 1)
		return (target_row);
	return (-2);
}

static int	find_row_hidden(t_data *master, int *cand, int r)
{
	int	digit;
	int	col;
	int	rc[2];
	int	found;

	found = 0;
	digit = 0;
	while (++digit <= master->size)
	{
		col = scan_row_digit(master, cand, r, digit);
		if (col == -1)
			return (-1);
		if (col >= 0)
		{
			rc[0] = r;
			rc[1] = col;
			cand[r * master->size + col] = 1 << (digit - 1);
			if (lock_single(master, cand, r * master->size + col, rc) < 0)
				return (-1);
			found = 1;
		}
	}
	return (found);
}

static int	find_col_hidden(t_data *master, int *cand, int c)
{
	int	digit;
	int	row;
	int	rc[2];
	int	idx;

	digit = 0;
	while (++digit <= master->size)
	{
		row = scan_col_digit(master, cand, c, digit);
		if (row == -1)
			return (-1);
		if (row >= 0)
		{
			rc[0] = row;
			rc[1] = c;
			idx = row * master->size + c;
			cand[idx] = 1 << (digit - 1);
			if (lock_single(master, cand, idx, rc) < 0)
				return (-1);
			return (1);
		}
	}
	return (0);
}

int	sweep_hidden_singles(t_data *master, int *cand)
{
	int	line;
	int	res;
	int	changed;

	changed = 0;
	line = -1;
	while (++line < master->size)
	{
		res = find_row_hidden(master, cand, line);
		if (res < 0)
			return (-1);
		if (res > 0)
			changed = 1;
		res = find_col_hidden(master, cand, line);
		if (res < 0)
			return (-1);
		if (res > 0)
			changed = 1;
	}
	return (changed);
}
