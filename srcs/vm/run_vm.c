/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:49:53 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/21 16:09:36 by briviere         ###   ########.fr       */
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

static int8_t	exec_instr(t_vm *vm, t_proc *proc)
{
	uint16_t	old_pc;
	if (vm->verbose >= VERBOSE_PC && !(vm->flags & (1 << VISUAL)))
	{
		ft_putchar('(');
		debug_print_pc(proc->pc);
		ft_putstr(" -> ");
		debug_print_pc(proc->pc + proc->instr.instr_size);
		ft_putchar(')');
		ft_putchar(' ');
		debug_print_arena(vm->arena, proc->pc, proc->instr.instr_size);
		ft_putchar('\n');
	}
	old_pc = proc->pc;
	if (proc->instr.fn && proc->instr.op)
		proc->instr.fn(vm, proc);
	// check if instr wasn't zjmp
	if (proc->pc == old_pc)
	{
		proc->pc += proc->instr.instr_size;
		proc->pc %= MEM_SIZE;
	}
	ft_bzero(&proc->instr, sizeof(t_instr));
	return (SUCCESS);
}

static int8_t	loop_procs(t_vm *vm)
{
	t_proc			*proc;
	t_deque_elmt	*queue_elmt;
	size_t			len;
	size_t			i;

	i = 0;
	len = vm->procs->size;
	queue_elmt = vm->procs->head;
	while (i < len)
	{
		proc = (t_proc*)queue_elmt->data;
		if (proc->delay)
			proc->delay -= 1;
		else if (proc->instr.op == NULL)
			interpret_instr(vm, proc);
		else if (exec_instr(vm, proc) == ERROR)
				return (ERROR);
		queue_elmt = queue_elmt->next;
		++i;
	}
	return (SUCCESS);
}

static void	print_screen(t_vm *vm)
{
	print_arena(vm);
	print_header(vm);
	print_stats(vm);
	usleep(5000);
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
		if (loop_procs(vm) == ERROR)
			return ;
		if (vm->flags & (1 << VISUAL))
			print_screen(vm);
	}
}
