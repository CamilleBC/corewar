/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:35:47 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/19 10:26:32 by cbaillat         ###   ########.fr       */
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
	wattron(vm->wins.children[player->id], COLOR_PAIR(player->id + 1));
	wprintw(vm->wins.children[player->id],"%s", content);
	wattroff(vm->wins.children[player->id], COLOR_PAIR(player->id + 1));
}

static void	print_player_subwin(t_vm *vm, t_player *play)
{
	uint8_t	id;

	id = play->id;
	wattron(vm->wins.stats_win,COLOR_PAIR(play->id + 1));
	box(vm->wins.children[id], '|' , '-');
	wattroff(vm->wins.children[id] ,COLOR_PAIR(play->id + 1));
	wmove(vm->wins.children[id], NAME_LINE, 1);
	print_player_string(vm ,play, "Name: ", play->header.prog_name);
	wmove(vm->wins.children[id], SIZE_LINE, 1);
	print_player_string(vm ,play, "Size: ", ft_itoa(play->header.prog_size));
	wmove(vm->wins.children[id], COMMENT_LINE, 1);
	print_player_string(vm ,play, "Comment: ", play->header.comment);
	wmove(vm->wins.children[id], THREADS_LINE, 1);
	print_player_string(vm ,play, "Threads: ", ft_itoa(play->nb_threads));
	wmove(vm->wins.children[id], LIVES_LINE, 1);
	print_player_string(vm ,play, "Lives: ", ft_itoa(play->live));
	wmove(vm->wins.children[id], ID_LINE, 1);
	print_player_string(vm ,play, "ID: ", ft_itoa(play->id));
	wrefresh(vm->wins.children[id]);
}

void	print_stats(t_vm *vm)
{
	int	i;

	wattron(vm->wins.stats_win,COLOR_PAIR(WHITEP_BLACK));
	box(vm->wins.stats_win, '|' , '-');
	wattroff(vm->wins.stats_win,COLOR_PAIR(WHITEP_BLACK));
	i = -1;
	while (++i < vm->nb_players)
		print_player_subwin(vm, vm->players[i]);
	wrefresh(vm->wins.stats_win);
}