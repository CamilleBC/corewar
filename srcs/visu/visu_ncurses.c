/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:31:15 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/15 17:45:44 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

void	print_arena(t_vm *vm)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	erase();
	wattron(vm->arena_win,COLOR_PAIR(14));
	box(vm->arena_win, '|' , '-');
	wattroff(vm->arena_win,COLOR_PAIR(14));
	wmove(vm->arena_win, j, 3);
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % 64 == 0)
		{
			j++;
			wmove(vm->arena_win, j, 3);
		}
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
		i++;
	}
	wrefresh(vm->arena_win);
}

void	print_header(t_vm *vm)
{
	int	x_offset;

	x_offset = (HEADER_WIDTH / 2) - 22;
	wattron(vm->header_win,COLOR_PAIR(14));
	wborder(vm->header_win, '#', '#', '#', '#', '#', '#', '#', '#');
	mvwprintw(vm->header_win, 1, x_offset, HEADER_LINE_1);
	mvwprintw(vm->header_win, 2, x_offset, HEADER_LINE_2);
	mvwprintw(vm->header_win, 3, x_offset, HEADER_LINE_3);
	mvwprintw(vm->header_win, 4, x_offset, HEADER_LINE_4);
	mvwprintw(vm->header_win, 5, x_offset, HEADER_LINE_5);
	wattroff(vm->header_win,COLOR_PAIR(14));
	wrefresh(vm->header_win);
}

void	print_stats(t_vm *vm)
{
	wattron(vm->stats_win,COLOR_PAIR(14));
	box(vm->stats_win, '|' , '-');
	wattroff(vm->stats_win,COLOR_PAIR(14));
	wrefresh(vm->stats_win);
}
