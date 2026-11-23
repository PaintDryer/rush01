/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 21:24:19 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/22 21:30:50 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// prints out the possible values in a square 
/*
void	put_bits(int value, int size, int is_solved)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (value & 1)
			ft_putdigit(i + 1);
		else if (!is_solved)
			write(1, "-", 1);
		value = value >> 1;
		i++;
	}
}
*/
void	ft_putdigit(int i)
{
	char	c;

	c = i + '0';
	write(1, &c, 1);
}

void	put_digits(int *nums, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_putdigit(nums[i]);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	print_board(int	*board, int size)
{
	int	i;

	i = 0;
	while (i < size * size)
	{
		ft_putdigit(board[i]);
		if ((i + 1) % size)
			write(1, " ", 1);
		else
			write(1, "\n", 1);
		i++;
	}
}
