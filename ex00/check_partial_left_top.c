/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_partial_left_top.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* Counts unused digits strictly taller than 'highest' that could add
	visibility */
/* Counts how many digits/cells are already set in a bitmask */
/* Scans row (is_col=0) or col (is_col=1) for placed heights and max height */
/* Left partial check: prunes if visible > clue, clue hit without max height,
	or unreachable */
/* Top partial check: same upper-bound pruning along column from top clue */

static int	count_taller_unused(int mask, int size, char highest)
{
	int	digit;
	int	count;

	digit = (highest - '0') + 1;
	count = 0;
	while (digit <= size)
	{
		if (!(mask & (1 << (digit - 1))))
			count++;
		digit++;
	}
	return (count);
}

static int	count_set_bits(int mask, int size)
{
	int	digit;
	int	count;

	digit = 1;
	count = 0;
	while (digit <= size)
	{
		if (mask & (1 << (digit - 1)))
			count++;
		digit++;
	}
	return (count);
}

static int	line_visible(t_data *master, int idx, int is_col, char *highest_out)
{
	int		step;
	int		visible;
	char	highest;
	char	cell;

	step = -1;
	visible = 0;
	highest = '0';
	while (++step < master->size)
	{
		cell = master->grid[idx][step];
		if (is_col)
			cell = master->grid[step][idx];
		if (cell != '0' && cell > highest)
		{
			highest = cell;
			visible++;
		}
	}
	if (highest_out)
		*highest_out = highest;
	return (visible);
}

int	check_left_clue_partial(t_data *master, int row, int column)
{
	int		visible;
	int		clue;
	int		max_extra;
	int		empty_cells;
	char	highest;

	(void)column;
	visible = line_visible(master, row, 0, &highest);
	clue = master->clues[2][row] - '0';
	if (visible > clue)
		return (0);
	if (visible == clue && highest < master->size + '0')
		return (0);
	empty_cells = master->size - count_set_bits(master->row_masks[row],
			master->size);
	max_extra = count_taller_unused(master->row_masks[row],
			master->size, highest);
	if (max_extra > empty_cells)
		max_extra = empty_cells;
	if (visible + max_extra < clue)
		return (0);
	return (1);
}

int	check_top_clue_partial(t_data *master, int row, int column)
{
	int		visible;
	int		clue;
	int		max_extra;
	int		empty_rows;
	char	highest;

	(void)row;
	visible = line_visible(master, column, 1, &highest);
	clue = master->clues[0][column] - '0';
	if (visible > clue)
		return (0);
	if (visible == clue && highest < master->size + '0')
		return (0);
	empty_rows = master->size - count_set_bits(master->col_masks[column],
			master->size);
	max_extra = count_taller_unused(master->col_masks[column],
			master->size, highest);
	if (max_extra > empty_rows)
		max_extra = empty_rows;
	if (visible + max_extra < clue)
		return (0);
	return (1);
}
