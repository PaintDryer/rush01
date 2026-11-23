/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_partial_right_bottom.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* Returns largest unused digit char in mask ('0' if none left) */
/* Counts cells at/left of column exceeding floor_char as we move left */
/* Counts cells at/above row exceeding floor_char as we move up */
/* Right partial check: optimistic max visible = remaining right + peaks
	above max_unused */
/* Bottom partial check: optimistic max visible = remaining below + peaks
	above max_unused */

static char	largest_unused_digit(int mask, int size)
{
	int	digit;

	digit = size;
	while (digit >= 1)
	{
		if (!(mask & (1 << (digit - 1))))
			return ((char)(digit + '0'));
		digit--;
	}
	return ('0');
}

static int	row_peaks_above_right(t_data *master, int row, int column,
		char floor_char)
{
	int		idx;
	int		peaks;
	char	highest_right;

	idx = column;
	peaks = 0;
	highest_right = floor_char;
	while (idx >= 0)
	{
		if (master->grid[row][idx] > highest_right)
		{
			highest_right = master->grid[row][idx];
			peaks++;
		}
		idx--;
	}
	return (peaks);
}

static int	col_peaks_above_bottom(t_data *master, int row, int column,
		char floor_char)
{
	int		idx;
	int		peaks;
	char	highest_bottom;

	idx = row;
	peaks = 0;
	highest_bottom = floor_char;
	while (idx >= 0)
	{
		if (master->grid[idx][column] > highest_bottom)
		{
			highest_bottom = master->grid[idx][column];
			peaks++;
		}
		idx--;
	}
	return (peaks);
}

int	check_right_clue_partial(t_data *master, int row, int column)
{
	int		remaining;
	int		max_vis;
	char	max_unused;

	remaining = master->size - column - 1;
	max_unused = largest_unused_digit(master->row_masks[row], master->size);
	max_vis = remaining + row_peaks_above_right(master, row, column,
			max_unused);
	if (max_vis < master->clues[3][row] - '0')
		return (0);
	return (1);
}

int	check_bottom_clue_partial(t_data *master, int row, int column)
{
	int		remaining;
	int		max_vis;
	char	max_unused;

	remaining = master->size - row - 1;
	max_unused = largest_unused_digit(master->col_masks[column], master->size);
	max_vis = remaining + col_peaks_above_bottom(master, row, column,
			max_unused);
	if (max_vis < master->clues[1][column] - '0')
		return (0);
	return (1);
}
