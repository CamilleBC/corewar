/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:35:47 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/11 15:48:39 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "vm.h"

static void move_and_clear(WINDOW *windows, t_vm *vm, int x, int y)
{
	clear_win_line(windows, vm, x, y);
	wmove(windows, x, y);
}

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
	move_and_clear(vm->wins.children[id], vm, NAME_LINE, 1);
	print_player_string(vm, play, "Name: ", play->header.prog_name);
	move_and_clear(vm->wins.children[id], vm, SIZE_LINE, 1);
	print_player_string(vm, play, "Size: ", ft_itoa(play->header.prog_size));
	move_and_clear(vm->wins.children[id], vm, THREADS_LINE, 1);
	print_player_string(vm, play, "Threads: ", ft_itoa(play->nb_threads));
	move_and_clear(vm->wins.children[id], vm, LIVES_LINE, 1);
	print_player_string(vm, play, "Lives: ", ft_itoa(play->live));
	move_and_clear(vm->wins.children[id], vm, PERIOD_LIVES_LINE, 1);
	print_player_string(vm, play, "Lives in period: ", ft_itoa(play->live_in_period));
	move_and_clear(vm->wins.children[id], vm, ID_LINE, 1);
	print_player_string(vm, play, "ID: ", ft_itoa((-1) - play->id));
	move_and_clear(vm->wins.children[id], vm, 8, 1);
	//if (play->nb_threads > 0 && play->threads && play->threads[0] && play->threads[0]->delay)
	//	print_player_string(vm, play, "Proc delay: ", ft_itoa(play->threads[0]->delay));
	wrefresh(vm->wins.children[id]);
}

void		print_vm_stats(t_vm *vm)
{
	wattron(vm->wins.stats_win, COLOR_PAIR(WHITEP_BLACK));
	move_and_clear(vm->wins.stats_win, vm, 1, 1);
	wprintw(vm->wins.stats_win, "Cycles: %llu", vm->total_cycles);
	if (vm->flags & (1 << DUMP))
	{
		move_and_clear(vm->wins.stats_win, vm, 2, 1);
		wprintw(vm->wins.stats_win, "Dump: %llu", vm->dump);
	}
	move_and_clear(vm->wins.stats_win, vm, 3, 1);
	wprintw(vm->wins.stats_win, "Cycles to die: %lld", vm->cycles_to_die);
	move_and_clear(vm->wins.stats_win, vm, 4, 1);
	wprintw(vm->wins.stats_win, "Cycle delta: %d", CYCLE_DELTA);
	move_and_clear(vm->wins.stats_win, vm, 5, 1);
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
