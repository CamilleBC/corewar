/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:36:10 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/19 15:18:56 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

static int	is_pc(int pos, t_deque_elmt *elem)
{
	while (elem)
	{
		if (((t_proc *)elem->data)->pc == (size_t)pos)
			return (1);
		elem = elem->next;
	}
	return (0);
}

static int	create_color(int color, int player)
{
	short		front;
	short		back;

	pair_content(color, &front, &back);
	init_pair(ARENA_PLAYER, front, player + 100);
	return (COLOR_PAIR(ARENA_PLAYER));
}

static void	print_hex(t_vm *vm, int i)
{
	int	player;

	player = 0;
	if (vm->arena[i].new_value)
			wattron(vm->wins.arena_win, A_BOLD);
	// init_pair(ARENA, vm->arena[i].colour, vm->arena[i].background);
	if ((player = is_pc(i, vm->procs->head)))
		wattron(vm->wins.arena_win, create_color(vm->arena[i].colour, player));
	else
		wattron(vm->wins.arena_win, COLOR_PAIR(vm->arena[i].colour));
	wprintw(vm->wins.arena_win, "%02x", 0xFF & vm->arena[i].hex);
	if (player)
		wattroff(vm->wins.arena_win, create_color(vm->arena[i].colour, player));
	else
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
	refresh();
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
