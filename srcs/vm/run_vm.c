/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:49:53 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/22 10:30:17 by briviere         ###   ########.fr       */
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
	queue_elmt = vm->procs->tail;
	while (queue_elmt)
	{
		proc = (t_proc*)queue_elmt->data;
		proc_elmt = queue_elmt;
		queue_elmt = queue_elmt->prev;
		if (!proc->live)
		{
			proc->owner->nb_threads--;
			ft_deque_pop_elmt(vm->procs, proc_elmt);
		}
		else
			lives += proc->live;
	}
	if (lives >= NBR_LIVE)
		vm->cycles_to_die -= CYCLE_DELTA;
	queue_elmt = vm->procs->head;
	while (queue_elmt)
	{
		proc = (t_proc*)queue_elmt->data;
		proc->live = 0;
		queue_elmt = queue_elmt->next;
	}
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
	queue_elmt = vm->procs->tail;
	while (i < len)
	{
		proc = (t_proc*)queue_elmt->data;
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
	else
		return (10000);
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
	while (vm->dump && vm->procs->head)
	{
		if (run || cycles)
		{
			vm->total_cycles += 1;
			if (vm->flags & (1 << DUMP))
				vm->dump -= 1;
			if (!(vm->total_cycles % vm->cycles_to_die))
				entropy(vm);
			if (loop_procs(vm) == ERROR)
				return ;
			if (vm->flags & (1 << VISUAL))
			{
				delay = manage_delay(run, cycles);
				print_screen(vm, delay);
			}
			if (cycles)
				--cycles;
		}
		cycles = manage_user_input(&run, cycles);
	}
}
