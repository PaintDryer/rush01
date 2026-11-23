/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 17:36:01 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/22 21:42:13 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// left to right
int	look_right(int *board, int size, int row_index)
{
	int	col_index;
	int	seen;
	int	highest;

	highest = -1;
	seen = 0;
	col_index = 0;
	while (col_index < size)
	{
		if (board[size * row_index + col_index] > highest)
		{
			highest = board[size * row_index + col_index];
			seen++;
		}
		col_index++;
	}
	return (seen);
}

// right to left
int	look_left(int *board, int size, int row_index)
{
	int	col_index;
	int	seen;
	int	highest;

	highest = -1;
	seen = 0;
	col_index = size - 1;
	while (col_index >= 0)
	{
		if (board[size * row_index + col_index] > highest)
		{
			highest = board[size * row_index + col_index];
			seen++;
		}
		col_index--;
	}
	return (seen);
}

// top to bottom
int	look_down(int *board, int size, int col_index)
{
	int	row_index;
	int	seen;
	int	highest;

	highest = -1;
	seen = 0;
	row_index = 0;
	while (row_index < size)
	{
		if (board[size * row_index + col_index] > highest)
		{
			highest = board[size * row_index + col_index];
			seen++;
		}
		row_index++;
	}
	return (seen);
}

// bottom to top
int	look_up(int *board, int size, int col_index)
{
	int	row_index;
	int	seen;
	int	highest;

	highest = -1;
	seen = 0;
	row_index = size - 1;
	while (row_index >= 0)
	{
		if (board[size * row_index + col_index] > highest)
		{
			highest = board[size * row_index + col_index];
			seen++;
		}
		row_index--;
	}
	return (seen);
}

int	valid_lines(t_data *data, int i)
{
	int	size;
	int	index;

	size = data->size;
	if (i % size == 0)
	{
		index = i / size - 1;
		if (look_right(data->board, size, index)
			!= data->clues[size * 2 + index])
			return (0);
		if (look_left(data->board, size, index)
			!= data->clues[size * 3 + index])
			return (0);
	}
	if (i > size * (size - 1))
	{
		index = i - 1 - size * (size - 1);
		if (look_down(data->board, size, index) != data->clues[index])
			return (0);
		if (look_up(data->board, size, index) != data->clues[size + index])
			return (0);
	}
	return (1);
}
