/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiew <ktiew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:00:00 by ktiew             #+#    #+#             */
/*   Updated: 2026/07/25 13:00:06 by ktiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <unistd.h>

# define MAX_DIRECTION 4
# define MAX_SIZE 9

typedef struct s_data
{
	char	**grid;
	char	**clues;
	int		size;
	int		solved;
	int		row_masks[MAX_SIZE];
	int		col_masks[MAX_SIZE];
}	t_data;

void	ft_putchar(char c);
void	print_error(void);
void	print_solution(t_data *master);

void	free_memory(char **str, int rows);
char	**allocate_memory(int rows, int columns);
char	**create_grid(int size);
char	**save_clues(char *str, int size);

int		check_left_clue(t_data *master, int row);
int		check_right_clue(t_data *master, int row);
int		check_top_clue(t_data *master, int column);
int		check_bottom_clue(t_data *master, int column);
int		check_left_clue_partial(t_data *master, int row, int column);
int		check_top_clue_partial(t_data *master, int row, int column);
int		check_right_clue_partial(t_data *master, int row, int column);
int		check_bottom_clue_partial(t_data *master, int row, int column);
int		parser(t_data *master, char *str);
int		check_no_duplicate(t_data *master, int row, int column, int digit);

// prefill_pairs.c
int		sweep_naked_pairs(t_data *master, int *cand);

// prefill_hidden.c
int		sweep_hidden_singles(t_data *master, int *cand);

// prefill_utils.c
void	init_cand_1d(int *cand, int size);
int		mask_max_height(int *mask, int size, int max_h);
int		calc_max_h(int size, int clue, int step);
int		lock_single(t_data *master, int *cand, int idx, int *rc);

// prefill.c
int		prefill(t_data *master);
int		sweep_1d_candidates(t_data *master, int *cand);

int		is_rush_solved(t_data *master, int column);
int		is_rush_solved_2(t_data *master, int row);
int		rush_recursive(t_data *master, int row, int column);
void	rush(t_data *master);

#endif
