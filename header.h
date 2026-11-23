/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajohari <ajohari@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 17:07:43 by ajohari           #+#    #+#             */
/*   Updated: 2026/11/22 22:12:41 by ajohari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

// offsets
# define TOP 0
# define BOT 1
# define LEFT 2
# define RIGHT 3

typedef struct s_data
{
	int	size;
	int	mask;
	int	*row_mask;
	int	*col_mask;
	int	*clues;
	int	*board;
}	t_data;

// board.c
void	*ft_calloc(size_t count, size_t size);
t_data	*new_data(char *clues);
void	print_board(int *board, int size);
void	free_data(t_data *data);

// recursive_solve.c
int		recursive_solve(t_data *data, int index, int size);
int		validate(t_data *data, int row, int col, int num);

// binary.c
int		itob(int i);

// mask.c
int		validate_mask(t_data *data, int row, int col, int digit);
int		set_mask(t_data *data, int row, int col, int digit);
void	remove_mask(t_data *data, int row, int col, int digit);

// prefill.c
void	prefill(t_data *data);
void	min_clue(t_data *data, int i);

// validation.c
int		look_right(int *board, int size, int row_index);
int		look_left(int *board, int size, int row_index);
int		look_down(int *board, int size, int col_index);
int		look_up(int *board, int size, int col_index);
int		valid_lines(t_data *data, int i);

// string.c
int		ft_strlen(char *str);
void	ft_putstr(int fd, char *str);
int		is_num(char c, int size);

// numbers.c
void	ft_putdigit(int i);
void	put_digits(int *nums, int len);
void	print_board(int *board, int size);
void	put_bits(int value, int size, int is_solved);
#endif
