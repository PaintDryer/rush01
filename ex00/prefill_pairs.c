/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefill_pairs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_pair_mask(int mask, int size)
{
	int	bit;
	int	count;

	bit = 0;
	count = 0;
	while (bit < size)
	{
		if (mask & (1 << bit))
			count++;
		bit++;
	}
	return (count == 2);
}

static int	get_line_idx(int size, int line, int pos, int is_col)
{
	if (is_col)
		return (pos * size + line);
	return (line * size + pos);
}

static int	eliminate_pair(t_data *master, int *cand, int *info, int mask)
{
	int	k;
	int	t;
	int	changed;

	changed = 0;
	k = -1;
	while (++k < master->size)
	{
		t = get_line_idx(master->size, info[2], k, info[3]);
		if (k != info[0] && k != info[1]
			&& master->grid[t / master->size][t % master->size] == '0'
			&& (cand[t] & mask))
		{
			cand[t] &= ~mask;
			if (cand[t] == 0)
				return (-1);
			changed = 1;
		}
	}
	return (changed);
}

static int	match_pair_from(t_data *master, int *cand, int *info, int mask)
{
	int	j;
	int	res;
	int	changed;

	changed = 0;
	j = info[0];
	while (++j < master->size)
	{
		if (cand[get_line_idx(master->size, info[2], j, info[3])] == mask)
		{
			info[1] = j;
			res = eliminate_pair(master, cand, info, mask);
			if (res < 0)
				return (-1);
			if (res > 0)
				changed = 1;
		}
	}
	return (changed);
}

int	sweep_naked_pairs(t_data *master, int *cand)
{
	int	line;
	int	pos;
	int	info[4];
	int	mask;
	int	changed;

	changed = 0;
	line = -1;
	while (++line < master->size)
	{
		pos = -1;
		while (++pos < master->size)
		{
			mask = cand[get_line_idx(master->size, line, pos, 0)];
			info[0] = pos;
			info[2] = line;
			info[3] = 0;
			if (is_pair_mask(mask, master->size)
				&& match_pair_from(master, cand, info, mask) < 0)
				return (-1);
		}
	}
	return (changed);
}
