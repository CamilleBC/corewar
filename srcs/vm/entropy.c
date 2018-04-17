/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entropy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 12:10:49 by briviere          #+#    #+#             */
/*   Updated: 2018/04/17 13:08:57 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	reset_player_period_lives(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < vm->nb_players)
	{
		vm->players[i]->live_in_period = 0;
		++i;
	}
}

static void	free_player_proc(t_player *player, t_proc *proc)
{
	uint64_t	i;

	i = 0;
	if (!proc || !player)
		return ;
	while (i < player->nb_threads)
	{
		if (player->threads[i] == proc)
		{
			player->threads[i] = NULL;
			while (i < player->nb_threads)
			{
				player->threads[i] = player->threads[i + 1];
				i++;
				return ;
			}
		}
		++i;
	}
}

static void	free_if_dead_proc(t_vm *vm, t_deque_elmt *proc_elmt,
		uint64_t *lives)
{
	t_proc			*proc;

	proc = (t_proc *)proc_elmt->data;
	if (proc->live)
	{
		*lives += proc->live;
		proc->live = 0;
	}
	else
	{
		free_player_proc(proc->owner, proc);
		proc->owner->nb_threads--;
		ft_deque_pop_elmt(vm->procs, proc_elmt);
		free(proc);
	}
}

void		entropy(t_vm *vm)
{
	uint64_t		lives;
	static uint64_t	last_check;
	t_deque_elmt	*queue_elmt;
	t_deque_elmt	*proc_elmt;

	queue_elmt = vm->procs->tail;
	lives = 0;
	while (queue_elmt && queue_elmt->data)
	{
		proc_elmt = queue_elmt;
		queue_elmt = queue_elmt->prev;
		free_if_dead_proc(vm, proc_elmt, &lives);
	}
	if (lives > NBR_LIVE)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		reset_player_period_lives(vm);
		last_check = 0;
	}
	else if (++last_check >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		reset_player_period_lives(vm);
		last_check = 0;
	}
}
