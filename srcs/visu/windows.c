/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:27:49 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/11 12:48:53 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

void	clear_win_line(WINDOW *win, t_vm *vm, int y, int x)
{
	size_t	width;
	size_t	i;

	wmove(win, y, x);
	if (win == vm->wins.arena_win)
		width = ARENA_W - 1;
	else if (win == vm->wins.stats_win)
		width = STATS_W - 1;
	else if (win == vm->wins.header_win)
		width = HEADER_W - 1;
	else
		width = CHILD_W - 1;
	i = 0;
	wattron(vm->wins.stats_win, COLOR_PAIR(BLACK));
	while (++i < width)
		wprintw(win, " ");
	wattroff(vm->wins.stats_win, COLOR_PAIR(BLACK));
}

WINDOW	*create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *win;

	win = newwin(height, width, starty, startx);
	return (win);
}
