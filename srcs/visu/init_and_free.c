/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:44:09 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/11 10:27:06 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

int8_t		free_visu(t_win windows, uint8_t nb_players)
{
	int32_t	i;

	i = -1;
	if (windows.arena_win)
		delwin(windows.arena_win);
	if (windows.header_win)
		delwin(windows.arena_win);
	if (windows.stats_win)
		delwin(windows.arena_win);
	if (windows.children)
		while (++i < nb_players)
			if (windows.children[i])
				delwin(windows.children[i]);
	endwin();
	return (ERROR);
}

static void	init_colors(void)
{
	init_color(COLOR_WHITEPLUS, 1000, 1000, 1000);
	init_color(COLOR_WHITE, 500, 500, 500);
	init_color(COLOR_WHITERED, 1000, 500, 500);
	init_color(COLOR_WHITEGREEN, 500, 500, 1000);
	init_color(COLOR_WHITEYELLOW, 1000, 1000, 500);
	init_color(COLOR_WHITEBLUE, 500, 1000, 500);
	init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
	init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair(BLACK_BLUE, COLOR_BLACK, COLOR_BLUE);
	init_pair(BLACK_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);
	init_pair(BLACK_RED, COLOR_BLACK, COLOR_RED);
	init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
	init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(WHITEP_BLACK, COLOR_WHITEPLUS, COLOR_BLACK);
	init_pair(BLACK_WHITEP, COLOR_BLACK, COLOR_WHITEPLUS);
}

int8_t		init_visu(t_vm *vm)
{
	int	i;

	if (!initscr() || start_color() == ERR
		|| noecho() == ERR || curs_set(FALSE) == ERR
		|| clear() == ERR)
		return (ERROR);
	init_colors();
	if (init_user_input() == ERROR)
		return (ERROR);
	if (!(vm->wins.header_win = create_newwin(HEADER_H, HEADER_W, 0, 0)))
		return (free_visu(vm->wins, vm->nb_players));
	if (!(vm->wins.arena_win = create_newwin(ARENA_H, ARENA_W, HEADER_H, 0)))
		return (free_visu(vm->wins, vm->nb_players));
	if (!(vm->wins.stats_win = create_newwin(ARENA_H, STATS_W, HEADER_H,
					ARENA_W)))
		return (free_visu(vm->wins, vm->nb_players));
	if (!(vm->wins.children = ft_memalloc(sizeof(WINDOW*) * vm->nb_players)))
		return (free_visu(vm->wins, vm->nb_players));
	i = -1;
	while (++i < vm->nb_players)
		if (!(vm->wins.children[i] = derwin(vm->wins.stats_win, CHILD_H,
			CHILD_W, i * CHILD_H + CHILD_OFFSET, 1)))
			return (free_visu(vm->wins, vm->nb_players));
	return (SUCCESS);
}
