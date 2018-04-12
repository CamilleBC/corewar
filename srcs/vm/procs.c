/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 13:06:08 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 13:06:13 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int8_t			exec_instr(t_vm *vm, t_proc *proc)
{
	uint16_t	old_pc;

	old_pc = proc->pc;
	if (interpret_args(vm, proc) == ERROR)
	{
		ft_bzero(&proc->instr, sizeof(t_instr));
		return (SUCCESS);
	}
	debug_print_proc(vm, proc);
	if (proc->instr.fn && proc->instr.op)
		proc->instr.fn(vm, proc);
	if (proc->instr.op->opcode != 9)
	{
		if (proc->instr.instr_size == 0)
			proc->pc++;
		else
			proc->pc += proc->instr.instr_size;
		proc->pc %= MEM_SIZE;
	}
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
		else if (proc->instr.op == NULL)
			interpret_instr(vm, proc);
		else if (exec_instr(vm, proc) == ERROR)
			return (ERROR);
		queue_elmt = queue_elmt->prev;
		++i;
	}
	return (SUCCESS);
}
