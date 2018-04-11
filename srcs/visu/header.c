/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:34:45 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/11 10:27:51 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

void	print_header(t_vm *vm)
{
	int	x_offset;

	x_offset = (HEADER_W / 2) - 22;
	// wattron(vm->wins.header_win, A_BOLD);
	// wattron(vm->wins.header_win, COLOR_PAIR(RED_BLACK));
	wattron(vm->wins.header_win, COLOR_PAIR(WHITEP_BLACK));
	wborder(vm->wins.header_win, '#', '#', '#', '#', '#', '#', '#', '#');
	mvwprintw(vm->wins.header_win, 1, x_offset, HEADER_LINE_1);
	mvwprintw(vm->wins.header_win, 2, x_offset, HEADER_LINE_2);
	mvwprintw(vm->wins.header_win, 3, x_offset, HEADER_LINE_3);
	mvwprintw(vm->wins.header_win, 4, x_offset, HEADER_LINE_4);
	mvwprintw(vm->wins.header_win, 5, x_offset, HEADER_LINE_5);
	wattroff(vm->wins.header_win, COLOR_PAIR(WHITEP_BLACK));
	// wattroff(vm->wins.header_win, COLOR_PAIR(RED_BLACK));
	// wattroff(vm->wins.header_win, A_BOLD);
	wrefresh(vm->wins.header_win);
}
