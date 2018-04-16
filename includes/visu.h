/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 22:12:41 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/16 14:12:02 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <ncurses.h>
# include <stdint.h>

# define HIGHLIGHT_TIME 50

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

# define NAME_LINE			1
# define SIZE_LINE			3
# define THREADS_LINE		4
# define LIVES_LINE			5
# define PERIOD_LIVES_LINE	6
# define ID_LINE			7

/*
** Colour Pairs
*/

# define COLOUR_OFFSET	10
# define RED_BLACK		COLOUR_OFFSET
# define GREEN_BLACK	COLOUR_OFFSET + 1
# define YELLOW_BLACK	COLOUR_OFFSET + 2
# define BLUE_BLACK		COLOUR_OFFSET + 3
# define BLACK_RED		COLOUR_OFFSET + 4
# define BLACK_GREEN	COLOUR_OFFSET + 5
# define BLACK_YELLOW	COLOUR_OFFSET + 6
# define BLACK_BLUE		COLOUR_OFFSET + 7
# define MAGENTA_BLACK	COLOUR_OFFSET + 8
# define CYAN_BLACK		COLOUR_OFFSET + 9
# define BLACK_MAGENTA	COLOUR_OFFSET + 10
# define BLACK_CYAN		COLOUR_OFFSET + 11
# define WHITE_BLACK	COLOUR_OFFSET + 12
# define BLACK_WHITE	COLOUR_OFFSET + 13
# define WHITEP_BLACK	COLOUR_OFFSET + 14
# define BLACK_WHITEP	COLOUR_OFFSET + 15
# define BLACK			98
# define ARENA			99
# define ARENA_PLAYER1	101
# define ARENA_PLAYER2	102
# define ARENA_PLAYER3	103
# define ARENA_PLAYER4	104
# define TEST			1000

/*
** User input
*/

# define KEY_SPACE	99
# define KEY_ETR	0x0a

struct s_vm;

typedef struct	s_win
{
	WINDOW	*arena_win;
	WINDOW	**children;
	WINDOW	*header_win;
	WINDOW	*stats_win;
}				t_win;

void			clear_win_line(WINDOW *win, struct s_vm *vm, int y, int x);
WINDOW			*create_newwin(int height, int width, int starty, int startx);
int8_t			free_visu(t_win windows, uint8_t nb_players);
int8_t			init_user_input(void);
int8_t			init_visu(struct s_vm *vm);
int				manage_user_input(uint8_t *run, int old_cycles);
void			print_arena(struct s_vm *vm);
void			print_header(struct s_vm *vm);
void			print_stats(struct s_vm *vm);

#endif
