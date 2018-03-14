/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:31:15 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/14 19:05:27 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

void	init_visu(t_vm *vm)
{
	initscr();
	noecho();
	start_color();
	init_pair(0, COLOR_BLUE, COLOR_BLACK);
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_CYAN);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);
	init_pair(9, COLOR_YELLOW, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_GREEN);
	curs_set(FALSE);
	vm->arena_win = create_newwin(64, 100, 0, 0);
	vm->stats_win = create_newwin(64, 28, 0, 100);
	refresh();
}

void	print_arena(t_vm *vm)
{
	int i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		if (vm->arena[i].new_value == 1)
			attron(A_BOLD);
		attron(COLOR_PAIR(vm->arena[i].colour));
		wprintw(vm->arena_win, "%02x", 0xFF & vm->arena[i].hex);
		attroff(COLOR_PAIR(vm->arena[i].colour));
		if (vm->arena[i].new_value == 1)
		{
			attroff(A_BOLD);
			vm->arena[i].new_value = 0;
		}
		wprintw(vm->arena_win, " ");
		if ((i + 1) % 33 == 0)
			wprintw(vm->arena_win, "\n");
		i++;
	}
	wrefresh(vm->arena_win);
}

void	destroy_visu(void)
{
	endwin();
}
