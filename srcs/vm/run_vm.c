/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:49:53 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/19 13:51:42 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int32_t	players_alive(t_vm *vm)
{
	uint8_t	i;
	int32_t	is_alive;

	i = 1;
	is_alive = -1;
	while (i < vm->nb_players)
	{
		if (vm->players[i]->alive)
			++is_alive;
		++i;
	}
	return (is_alive);
}

// Pseudocode
void	run_vm(t_vm *vm)
{
	t_deque_elmt	*queue_elmt;
	t_proc			*proc;

	while (players_alive(vm) > 0 || !vm->dump)
	{
		queue_elmt = vm->procs->head;
		while (queue_elmt)
		{
			proc = (t_proc*)queue_elmt->data;
			if (proc->alive)
			{
				interpret_instr(vm, proc->owner, proc);
			}
			queue_elmt = queue_elmt->next;
		}
		if (vm->flags & (1 << DUMP))
			vm->dump -= 1;
		vm->total_cycles += 1;
	}
}
