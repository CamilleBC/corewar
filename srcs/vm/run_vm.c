/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:49:53 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/12 12:33:07 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int8_t	exec_instr(t_vm *vm, t_proc *proc)
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

static int8_t	loop_procs(t_vm *vm)
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

static void	print_screen(t_vm *vm, uint32_t delay)
{
	print_arena(vm);
	print_header(vm);
	print_stats(vm);
	usleep(delay);
}

uint32_t	manage_delay(uint8_t run, int cycles)
{
	if (run == 1)
		return (20000);
	else if (cycles <= 1)
		return (0);
	else if (cycles <= 10)
		return (250000);
	else if (cycles <= 100)
		return (50000);
	else if (cycles <= 500)
		return (20000);
	else if (cycles <= 1000)
		return (10000);
	else
		return (500);
}

void	run_vm(t_vm *vm)
{
	uint8_t		run;
	int			cycles;
	uint32_t	delay;

	run = 0;
	cycles = 0;
	delay = 0;
	refresh();
	if (vm->flags & (1 << VISUAL))
		print_screen(vm, delay);
	while (vm->cycles_to_die > 0 && vm->dump && vm->procs->head)
	{
		if (run || cycles)
		{
			vm->total_cycles += 1;
			if (vm->flags & (1 << DUMP))
				vm->dump -= 1;
			if (!(vm->total_cycles % vm->cycles_to_die))
				entropy(vm);
			if (loop_procs(vm) == ERROR)
				break ;
			if (vm->flags & (1 << VISUAL))
			{
				delay = manage_delay(run, cycles);
				print_screen(vm, delay);
			}
			if (cycles)
				--cycles;
		}
		if (vm->flags & (1 << VISUAL))
			cycles = manage_user_input(&run, cycles);
		else
			cycles = 1;
	}
	// ft_deque_delete_data(vm->procs);
}
