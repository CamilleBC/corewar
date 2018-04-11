/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:49:53 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/11 15:13:52 by briviere         ###   ########.fr       */
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

static void free_player_proc(t_player *player, t_proc *proc)
{
	uint64_t	i;

	i = 0;
	while (i < player->nb_threads)
	{
		if (player->threads[i] == proc)
		{
			player->threads[i] = NULL;
			while (i < (player->nb_threads))
			{
				player->threads[i] = player->threads[i + 1];
				i++;
				return ;
			}
		}
			++i;
	}
}

static void	entropy(t_vm *vm)
{
	static uint64_t	lives;
	t_proc			*proc;
	t_deque_elmt	*queue_elmt;
	t_deque_elmt	*proc_elmt;
	static uint64_t	last_check;

	queue_elmt = vm->procs->tail;
	while (queue_elmt)
	{
		if (!(proc = (t_proc*)queue_elmt->data))
			break ;
		proc_elmt = queue_elmt;
		queue_elmt = queue_elmt->prev;
		if (proc->live)
		{
			lives += proc->live;
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
	if (lives >= NBR_LIVE)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		reset_player_period_lives(vm);
		last_check = 0;
		lives = 0;
	}
	if (!(++last_check % MAX_CHECKS))
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		reset_player_period_lives(vm);
	}
}

static int8_t	exec_instr(t_vm *vm, t_proc *proc)
{
	uint16_t	old_pc;
	old_pc = proc->pc;
	if (interpret_args(vm, proc) == ERROR)
	{
		ft_bzero(&proc->instr, sizeof(t_instr));
		return (SUCCESS);
	}
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
	if (proc->instr.fn && proc->instr.op)
		proc->instr.fn(vm, proc);
	if (proc->pc == old_pc)
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
	ft_deque_delete_data(vm->procs);
	free_visu(vm->wins, vm->nb_players);
	ft_print("finished!\n");
}
