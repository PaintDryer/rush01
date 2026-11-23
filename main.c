/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 17:06:58 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/23 14:32:25 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "string.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (1);
	if (((strlen(argv[1]) + 1) % 8) != 0)
	{
		ft_putstr(STDERR_FILENO, "Invalid input\n");
		return (1);
	}
	data = new_data(argv[1]);
	if (!data)
		return (1);
	recursive_solve(data, 0, data->size);
	if (data->board[data->size * data->size] != 0)
		print_board(data->board, data->size);
	else
		write(1, "Error\n", 6);
	print_board(data->board, data->size);
	free_data(data);
}
