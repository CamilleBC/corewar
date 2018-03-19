/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:36:10 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/19 13:39:43 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

static void	print_hex(t_vm *vm, int i)
{
	if (vm->arena[i].new_value)
			wattron(vm->wins.arena_win, A_BOLD);
	// init_pair(ARENA, vm->arena[i].colour, vm->arena[i].background);
	wattron(vm->wins.arena_win, COLOR_PAIR(vm->arena[i].colour));
	wprintw(vm->wins.arena_win, "%02x", 0xFF & vm->arena[i].hex);
	wattroff(vm->wins.arena_win, COLOR_PAIR(vm->arena[i].colour));
	if (vm->arena[i].new_value)
	{
		wattroff(vm->wins.arena_win, A_BOLD);
		vm->arena[i].new_value -= 1;
	}
	wprintw(vm->wins.arena_win, " ");
}

void		print_arena(t_vm *vm)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	// clear();
	// refresh();
	wattron(vm->wins.arena_win,COLOR_PAIR(WHITEP_BLACK));
	box(vm->wins.arena_win, '|' , '-');
	wattroff(vm->wins.arena_win,COLOR_PAIR(WHITEP_BLACK));
	wmove(vm->wins.arena_win, j, 3);
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % 64 == 0)
		{
			j++;
			wmove(vm->wins.arena_win, j, 3);
		}
		print_hex(vm, i);
		i++;
	}
	wrefresh(vm->wins.arena_win);
}
