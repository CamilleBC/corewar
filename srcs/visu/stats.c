/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:35:47 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/11 10:25:58 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

static void	print_player_string(t_vm *vm, t_player *player,
				const char *title, const char *content)
{
	wattron(vm->wins.children[player->id], COLOR_PAIR(WHITEP_BLACK));
	wprintw(vm->wins.children[player->id], title);
	wattroff(vm->wins.children[player->id], COLOR_PAIR(WHITEP_BLACK));
	wattron(vm->wins.children[player->id], COLOR_PAIR(player->colour));
	wprintw(vm->wins.children[player->id], "%s", content);
	wattroff(vm->wins.children[player->id], COLOR_PAIR(player->colour));
}

static void	print_player_subwin(t_vm *vm, t_player *play)
{
	uint8_t	id;

	id = play->id;
	wattron(vm->wins.stats_win, COLOR_PAIR(play->id + 1));
	box(vm->wins.children[id], '|', '-');
	wattroff(vm->wins.children[id], COLOR_PAIR(play->id + 1));
	wmove(vm->wins.children[id], NAME_LINE, 1);
	print_player_string(vm, play, "Name: ", play->header.prog_name);
	wmove(vm->wins.children[id], SIZE_LINE, 1);
	print_player_string(vm, play, "Size: ", ft_itoa(play->header.prog_size));
	wmove(vm->wins.children[id], THREADS_LINE, 1);
	print_player_string(vm, play, "Threads: ", ft_itoa(play->nb_threads));
	wmove(vm->wins.children[id], LIVES_LINE, 1);
	print_player_string(vm, play, "Lives: ", ft_itoa(play->live));
	wmove(vm->wins.children[id], ID_LINE, 1);
	print_player_string(vm, play, "ID: ", ft_itoa((-1) - play->id));
	wrefresh(vm->wins.children[id]);
}

void		print_vm_stats(t_vm *vm)
{
	wattron(vm->wins.stats_win, COLOR_PAIR(WHITEP_BLACK));
	clear_win_line(vm->wins.stats_win, vm, 1, 1);
	wmove(vm->wins.stats_win, 1, 1);
	wprintw(vm->wins.stats_win, "Cycles: %llu", vm->total_cycles);
	if (vm->flags & (1 << DUMP))
	{
		clear_win_line(vm->wins.stats_win, vm, 2, 1);
		wmove(vm->wins.stats_win, 2, 1);
		wprintw(vm->wins.stats_win, "Dump: %llu", vm->dump);
	}
	clear_win_line(vm->wins.stats_win, vm, 3, 1);
	wmove(vm->wins.stats_win, 3, 1);
	wprintw(vm->wins.stats_win, "Cycles to die: %lld", vm->cycles_to_die);
	wmove(vm->wins.stats_win, 4, 1);
	wprintw(vm->wins.stats_win, "Cycle delta: %d", CYCLE_DELTA);
	clear_win_line(vm->wins.stats_win, vm, 5, 1);
	wmove(vm->wins.stats_win, 5, 1);
	wattroff(vm->wins.stats_win, COLOR_PAIR(WHITEP_BLACK));
}

void		print_stats(t_vm *vm)
{
	int	i;

	wattron(vm->wins.stats_win, COLOR_PAIR(WHITEP_BLACK));
	box(vm->wins.stats_win, '|', '-');
	wattroff(vm->wins.stats_win, COLOR_PAIR(WHITEP_BLACK));
	print_vm_stats(vm);
	i = -1;
	while (++i < vm->nb_players)
		print_player_subwin(vm, vm->players[i]);
	wrefresh(vm->wins.stats_win);
}
