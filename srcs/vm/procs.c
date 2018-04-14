/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 13:06:08 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 09:29:37 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int8_t			exec_instr(t_vm *vm, t_proc *proc)
{
	if (proc->instr.op.opcode == -1)
	{
		proc->pc += proc->instr.instr_size;
		ft_bzero(&proc->instr, sizeof(t_instr));
		return (SUCCESS);
	}
	if (interpret_args(vm, proc) == ERROR)
	{
		proc->pc += proc->instr.instr_size;
		ft_bzero(&proc->instr, sizeof(t_instr));
		return (SUCCESS);
	}
	proc->pc--;
	debug_print_proc(vm, proc);
	if (proc->instr.op.opcode != 0)
		proc->instr.fn(vm, proc);
	proc->pc += proc->instr.instr_size + 1;
	ft_bzero(&proc->instr, sizeof(t_instr));
	return (SUCCESS);
}

int8_t			loop_procs(t_vm *vm)
{
	t_proc			*proc;
	t_deque_elmt	*queue_elmt;
	size_t			len;
	size_t			i;

	i = 0;
	len = vm->procs->size;
	queue_elmt = vm->procs->tail;
	while (i < len && queue_elmt)
	{
		if (!(proc = (t_proc*)queue_elmt->data))
			return (ERROR);
		if (proc->delay)
			proc->delay -= 1;
		else if (proc->instr.op.opcode == 0)
			interpret_instr(vm, proc);
		else if (exec_instr(vm, proc) == ERROR)
			return (ERROR);
		queue_elmt = queue_elmt->prev;
		++i;
	}
	return (SUCCESS);
}
