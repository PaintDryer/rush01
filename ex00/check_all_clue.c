/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_clue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* Bitwise O(1) duplicate check using row and column bitmasks */
/* Full right-to-left scan: counts strictly increasing heights
	from right edge */
/* Full left-to-right scan; chains into check_right_clue on match */
/* Full bottom-to-top scan: counts strictly increasing heights
	from bottom edge */
/* Full top-to-bottom scan; chains into check_bottom_clue on match */

int	check_no_duplicate(t_data *master, int row, int column, int digit)
{
	int	bit;

	bit = 1 << (digit - 1);
	if (master->row_masks[row] & bit)
		return (0);
	if (master->col_masks[column] & bit)
		return (0);
	return (1);
}

int	check_right_clue(t_data *master, int row)
{
	int		index;
	char	visible;
	char	highest;

	index = master->size - 1;
	visible = '1';
	highest = master->grid[row][index];
	while (index >= 0)
	{
		if (master->grid[row][index] > highest)
		{
			highest = master->grid[row][index];
			visible++;
		}
		index--;
	}
	return (master->clues[3][row] == visible);
}

int	check_left_clue(t_data *master, int row)
{
	int		index;
	char	visible;
	char	highest;

	index = 0;
	visible = '1';
	highest = master->grid[row][index];
	while (index < master->size)
	{
		if (master->grid[row][index] > highest)
		{
			highest = master->grid[row][index];
			visible++;
		}
		index++;
	}
	if (master->clues[2][row] == visible)
		return (check_right_clue(master, row));
	return (0);
}

int	check_bottom_clue(t_data *master, int column)
{
	int		index;
	char	visible;
	char	highest;

	index = master->size - 1;
	visible = '1';
	highest = master->grid[index][column];
	while (index >= 0)
	{
		if (master->grid[index][column] > highest)
		{
			highest = master->grid[index][column];
			visible++;
		}
		index--;
	}
	return (master->clues[1][column] == visible);
}

int	check_top_clue(t_data *master, int column)
{
	int		index;
	char	visible;
	char	highest;

	index = 0;
	visible = '1';
	highest = master->grid[index][column];
	while (index < master->size)
	{
		if (master->grid[index][column] > highest)
		{
			highest = master->grid[index][column];
			visible++;
		}
		index++;
	}
	if (master->clues[0][column] == visible)
		return (check_bottom_clue(master, column));
	return (0);
}
