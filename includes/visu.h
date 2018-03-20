/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 22:12:41 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/20 18:49:55 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <ncurses.h>
# include <stdint.h>

/*
** Arena Window
*/

# define ARENA_W		197
# define ARENA_H		68
# define COLOR_WHITEPLUS	9
# define COLOR_WHITERED		101
# define COLOR_WHITEBLUE	102
# define COLOR_WHITEYELLOW	103
# define COLOR_WHITEGREEN	104
/*
** HEADER Corewar
*/

# define HEADER_W		(ARENA_W + STATS_W)
# define HEADER_H		7
# define HEADER_LINE_1		"   ______                                  "
# define HEADER_LINE_2		"  / ____/___  ________ _      ______ ______"
# define HEADER_LINE_3		" / /   / __ \\/ ___/ _ \\ | /| / / __ `/ ___/"
# define HEADER_LINE_4		"/ /___/ /_/ / /  /  __/ |/ |/ / /_/ / /    "
# define HEADER_LINE_5		"\\____/\\____/_/   \\___/|__/|__/\\__,_/_/     "

/*
** Stats Window
*/

# define STATS_W		48
# define CHILD_H		12
# define CHILD_W		(STATS_W - 2)
# define CHILD_OFFSET	19

/*
** Player Sub-windows
*/

# define NAME_LINE		1
# define SIZE_LINE		3
# define THREADS_LINE	4
# define LIVES_LINE		5
# define ID_LINE		6

/*
** Colour Pairs
*/

# define RED_BLACK		1
# define GREEN_BLACK	2
# define YELLOW_BLACK	3
# define BLUE_BLACK		4
# define BLACK_RED		5
# define BLACK_GREEN	6
# define BLACK_YELLOW	7
# define BLACK_BLUE		6
# define MAGENTA_BLACK	8
# define CYAN_BLACK		9
# define BLACK_MAGENTA	10
# define BLACK_CYAN		11
# define WHITE_BLACK	12
# define BLACK_WHITE	13
# define WHITEP_BLACK	14
# define BLACK_WHITEP	15
# define BLACK			98
# define ARENA			99
# define ARENA_PLAYER1	101
# define ARENA_PLAYER2	102
# define ARENA_PLAYER3	103
# define ARENA_PLAYER4	104
# define TEST			1000

struct	s_vm;

typedef struct	s_win
{
	WINDOW	*arena_win;
	WINDOW	**children;
	WINDOW	*header_win;
	WINDOW	*stats_win;
}				t_win;

WINDOW	*create_newwin(int height, int width, int starty, int startx);
void	free_visu(t_win windows, uint8_t nb_players);
void	init_visu(struct s_vm *vm);
void	print_arena(struct s_vm *vm);
void	print_header(struct s_vm *vm);
void	print_stats(struct s_vm *vm);

#endif
