/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/* Sets bit (digit - 1) in row and column masks */
/* Clears bit (digit - 1) from row and column masks on backtrack */
/* Tries 1..size if left clue == size (ascending), else size..1 (descending) */
/* Enforces immediate edge rules for clue '1' and clue 'size' on borders */
/* Core recursive backtracker: place -> mask -> partial prune
	-> recurse -> unplace */

static void	set_masks(t_data *master, int row, int column, int digit)
{
	int	bit;

	bit = 1 << (digit - 1);
	master->row_masks[row] |= bit;
	master->col_masks[column] |= bit;
}

static void	unset_masks(t_data *master, int row, int column, int digit)
{
	int	bit;

	bit = 1 << (digit - 1);
	master->row_masks[row] &= ~bit;
	master->col_masks[column] &= ~bit;
}

static void	set_digit_order(t_data *master, int row, int *digit, int *step)
{
	if (master->clues[2][row] == master->size + '0')
	{
		*digit = 1;
		*step = 1;
	}
	else
	{
		*digit = master->size;
		*step = -1;
	}
}

static int	check_fixed_clue(t_data *master, int row, int column, int digit)
{
	if (column == 0)
	{
		if (master->clues[2][row] == '1' && digit != master->size)
			return (0);
		if (master->clues[2][row] == master->size + '0' && digit != 1)
			return (0);
	}
	if (column == master->size - 1 && master->clues[3][row] == '1'
		&& digit != master->size)
		return (0);
	if (row == 0)
	{
		if (master->clues[0][column] == '1' && digit != master->size)
			return (0);
		if (master->clues[0][column] == master->size + '0' && digit != 1)
			return (0);
	}
	if (row == master->size - 1 && master->clues[1][column] == '1'
		&& digit != master->size)
		return (0);
	return (1);
}

int	rush_recursive(t_data *master, int row, int column)
{
	int	digit;
	int	step;

	if (row == master->size)
		return (is_rush_solved(master, column));
	if (column == master->size)
		return (is_rush_solved_2(master, row));
	set_digit_order(master, row, &digit, &step);
	while (digit >= 1 && digit <= master->size)
	{
		if (check_no_duplicate(master, row, column, digit)
			&& check_fixed_clue(master, row, column, digit))
		{
			master->grid[row][column] = digit + '0';
			set_masks(master, row, column, digit);
			if (check_clue_partial(master, row, column)
				&& rush_recursive(master, row, column + 1))
				return (1);
			unset_masks(master, row, column, digit);
			master->grid[row][column] = '0';
		}
		digit += step;
	}
	return (0);
}
