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

// print.c
void	print_error(void);
void	print_solution(t_data *master);

// set.c
void	free_memory(char **str, int rows);
char	**create_grid(int size);
char	**save_clues(char *str, int size);

// check_all_clue.c
int		check_no_duplicate(t_data *master, int row, int column, int digit);
int		check_left_clue(t_data *master, int row);
int		check_right_clue(t_data *master, int row);
int		check_top_clue(t_data *master, int column);
int		check_bottom_clue(t_data *master, int column);

// check_partial_left_top.c
int		check_left_clue_partial(t_data *master, int row, int column);
int		check_top_clue_partial(t_data *master, int row, int column);

// check_partial_right_bottom.c
int		check_right_clue_partial(t_data *master, int row, int column);
int		check_bottom_clue_partial(t_data *master, int row, int column);

// parser.c
int		parser(t_data *master, char *str);

// rush_utils.c
int		is_rush_solved(t_data *master, int column);
int		is_rush_solved_2(t_data *master, int row);
int		check_clue_partial(t_data *master, int row, int column);
void	rush(t_data *master);

// rush.c
int		rush_recursive(t_data *master, int row, int column);

#endif
