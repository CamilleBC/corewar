/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:44:09 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/16 11:13:01 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

static void	init_colors(void)
{
	init_color(COLOR_WHITEPLUS, 1000, 1000, 1000);
	init_color(COLOR_WHITE, 600, 600, 600);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(7, COLOR_BLACK, COLOR_CYAN);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_YELLOW, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_GREEN, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_GREEN);
	init_pair(14, COLOR_WHITEPLUS, COLOR_BLACK);
	init_pair(15, COLOR_BLACK, COLOR_WHITEPLUS);
}

void		init_visu(t_vm *vm)
{
	initscr();
	noecho();
	start_color();
	init_colors();
	curs_set(FALSE);
	vm->wins.header_win = create_newwin(HEADER_HEIGHT, HEADER_WIDTH, 0, 0);
	vm->wins.arena_win = create_newwin(ARENA_HEIGHT, ARENA_WIDTH, HEADER_HEIGHT, 0);
	vm->wins.stats_win = create_newwin(ARENA_HEIGHT, STATS_WIDTH, HEADER_HEIGHT, ARENA_WIDTH);
	refresh();
}

void		free_visu(t_vm *vm)
{
	delwin(vm->wins.arena_win);
	delwin(vm->wins.header_win);
	delwin(vm->wins.stats_win);
	endwin();
}
