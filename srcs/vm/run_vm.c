/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:49:53 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/19 17:11:19 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	entropy(t_vm *vm)
{
	uint64_t		lives;
	t_proc			*proc;
	t_deque_elmt	*queue_elmt;
	t_deque_elmt	*proc_elmt;

	lives = 0;
	queue_elmt = vm->procs->head;
	while (queue_elmt)
	{
		proc = (t_proc*)queue_elmt->data;
		proc_elmt = queue_elmt;
		queue_elmt = queue_elmt->next;
		if (!proc->live)
			ft_deque_pop_elmt(vm->procs, proc_elmt);
		lives += proc->live;
	}
	if (lives >= NBR_LIVE)
		vm->cycles_to_die -= CYCLE_DELTA;
}

static void	exec_instr(t_vm *vm)
{
	t_proc			*proc;
	t_deque_elmt	*queue_elmt;

	queue_elmt = vm->procs->head;
	while (queue_elmt)
	{
		proc = (t_proc*)queue_elmt->data;
		if (proc->delay)
			proc->delay -= 1;
		else
			interpret_instr(vm, proc);
		queue_elmt = queue_elmt->next;
	}
}

void	run_vm(t_vm *vm)
{
	while (vm->dump && vm->procs->head)
	{
		vm->total_cycles += 1;
		if (vm->flags & (1 << DUMP))
			vm->dump -= 1;
		if (!(vm->total_cycles % vm->cycles_to_die))
			entropy(vm);
		exec_instr(vm);
	}
}
