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

/* Verifies all four partial clue bounds after a placement */
/* Validates row left/right clues when column reaches size, then moves to
	next row */
/* Validates all column top/bottom clues when row reaches size,
	prints first solution */
/* Allocates grid, runs solver, reports error if unsolved,
	frees allocated memory */

int	is_rush_solved(t_data *master, int column)
{
	column = 0;
	while (column < master->size)
	{
		if (!check_top_clue(master, column))
			return (0);
		column++;
	}
	print_solution(master);
	master->solved = 1;
	return (1);
}

int	is_rush_solved_2(t_data *master, int row)
{
	if (check_left_clue(master, row))
		return (rush_recursive(master, row + 1, 0));
	return (0);
}

int	check_clue_partial(t_data *master, int row, int column)
{
	if (check_left_clue_partial(master, row, column)
		&& check_top_clue_partial(master, row, column)
		&& check_right_clue_partial(master, row, column)
		&& check_bottom_clue_partial(master, row, column))
		return (1);
	return (0);
}

void	rush(t_data *master)
{
	master->grid = create_grid(master->size);
	master->solved = 0;
	rush_recursive(master, 0, 0);
	if (master->solved == 0)
		print_error();
	free_memory(master->grid, master->size);
	free_memory(master->clues, MAX_DIRECTION);
}
