/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	apply_clue_row(t_data *master, int *cand, int r, int from_right)
{
	int	clue;
	int	step;
	int	col;

	if (from_right)
		clue = master->clues[3][r] - '0';
	else
		clue = master->clues[2][r] - '0';
	step = -1;
	while (++step < master->size)
	{
		if (from_right)
			col = master->size - 1 - step;
		else
			col = step;
		if (master->grid[r][col] == '0')
			if (mask_max_height(&cand[r * master->size + col], master->size,
					calc_max_h(master->size, clue, step)) < 0)
				return (-1);
	}
	return (0);
}

static int	apply_clue_col(t_data *master, int *cand, int c, int from_bottom)
{
	int	clue;
	int	step;
	int	row;

	if (from_bottom)
		clue = master->clues[1][c] - '0';
	else
		clue = master->clues[0][c] - '0';
	step = -1;
	while (++step < master->size)
	{
		if (from_bottom)
			row = master->size - 1 - step;
		else
			row = step;
		if (master->grid[row][c] == '0')
			if (mask_max_height(&cand[row * master->size + c], master->size,
					calc_max_h(master->size, clue, step)) < 0)
				return (-1);
	}
	return (0);
}

int	sweep_1d_candidates(t_data *master, int *cand)
{
	int	idx;
	int	rc[2];
	int	changed;

	changed = 0;
	idx = -1;
	while (++idx < master->size * master->size)
	{
		rc[0] = idx / master->size;
		rc[1] = idx % master->size;
		if (master->grid[rc[0]][rc[1]] == '0')
		{
			cand[idx] &= ~(master->row_masks[rc[0]] | master->col_masks[rc[1]]);
			if (cand[idx] == 0)
				return (-1);
			if ((cand[idx] & (cand[idx] - 1)) == 0)
			{
				if (lock_single(master, cand, idx, rc) < 0)
					return (-1);
				changed = 1;
			}
		}
	}
	return (changed);
}

static int	prefill_step(t_data *master, int *cand, int *changed)
{
	int	res;

	*changed = 0;
	res = sweep_1d_candidates(master, cand);
	if (res < 0)
		return (-1);
	if (res > 0)
		*changed = 1;
	res = sweep_hidden_singles(master, cand);
	if (res < 0)
		return (-1);
	if (res > 0)
		*changed = 1;
	res = sweep_naked_pairs(master, cand);
	if (res < 0)
		return (-1);
	if (res > 0)
		*changed = 1;
	return (0);
}

int	prefill(t_data *master)
{
	int	*cand;
	int	changed;
	int	i;

	cand = (int *)malloc(sizeof(int) * master->size * master->size);
	if (!cand)
		return (0);
	init_cand_1d(cand, master->size);
	changed = 1;
	while (changed)
	{
		i = -1;
		while (++i < master->size)
			if (apply_clue_row(master, cand, i, 0) < 0
				|| apply_clue_row(master, cand, i, 1) < 0
				|| apply_clue_col(master, cand, i, 0) < 0
				|| apply_clue_col(master, cand, i, 1) < 0)
				return (free(cand), 0);
		if (prefill_step(master, cand, &changed) < 0)
			return (free(cand), 0);
	}
	return (free(cand), 1);
}
