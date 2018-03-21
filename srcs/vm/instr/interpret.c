/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/03/21 09:46:11 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_op	get_op(int opcode)
{
	size_t	idx;
	t_op	*ops;

	idx = 0;
	ops = get_ops();
	while (idx < OP_COUNT)
	{
		if (ops[idx].opcode == opcode)
			return (ops[idx]);
		idx++;
	}
	return (ops[idx - 1]);
}

static size_t fill_arg(t_arena *mem, t_proc *proc, t_arg *arg, int dir_size)
{
	if (arg->code == REG_CODE)
	{
		arg->value.reg = mem[proc->pc++].hex;
		arg->size = 1;
	}
	else if (arg->code == IND_CODE)
	{
		arg->value.ind = array_to_int_arena(mem + proc->pc, IND_SIZE);
		proc->pc += IND_SIZE;
		arg->size = IND_SIZE;
	}
	else if (arg->code == DIR_CODE)
	{
		arg->value.dir = array_to_int_arena(mem + proc->pc, dir_size);
		proc->pc += dir_size;
		arg->size = dir_size;
	}
	proc->pc %= MEM_SIZE;
	return (arg->size);
}

static size_t	fill_args(t_vm *vm, t_proc *proc, t_op op)
{
	size_t	idx;
	int		octal;
	size_t	arg_size;

	octal = 0;
	arg_size = 0;
	if (op.octal)
	{
		arg_size++;
		octal = vm->arena[proc->pc++].hex;
	}
	idx = 0;
	while (idx < op.nb_args)
	{
		if (octal)
			proc->instr.args[idx].code = octal >> ((3 - idx) * 2) & 0b11;
		else
			proc->instr.args[idx].code = op.args[idx];
		arg_size += fill_arg(vm->arena, proc, proc->instr.args + idx,
				(op.dir_size ? DIR_SIZE / 2 : DIR_SIZE));
		proc->instr.nb_args++;
		idx++;
	}
	return (arg_size);
}

void	clear_win_line(WINDOW *win, t_vm *vm, int y, int x)
{
	size_t	width;
	char	*erase;
	size_t	i;

	wmove(win, y, x);
	if (win == vm->wins.arena_win)
		width = ARENA_W - 1;
	else if (win == vm->wins.stats_win)
		width = STATS_W - 1;
	else if (win == vm->wins.header_win)
		width = HEADER_W - 1;
	else
		return ;
	if (!(erase = ft_strnew(sizeof(char) * width)))
		return ;
	i = 0;
	wattron(vm->wins.stats_win, COLOR_PAIR(BLACK));
	while (++i < width)
		wprintw(win, " ");
	wattroff(vm->wins.stats_win, COLOR_PAIR(BLACK));
}

void	print_player_instr(t_vm *vm, t_proc *proc, t_op op)
{
	int	offset;

	offset = 5 + (3 * ft_abs32(proc->owner->id));
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->id + 1));
	wmove(vm->wins.stats_win, offset, 1);
	// wclrtoeol(vm->wins.stats_win);
	// clear_win_line(vm->wins.stats_win, vm, offset, 1);
	wprintw(vm->wins.stats_win, "Proc owner: %d / %s", (-1) - proc->owner->id,
		proc->owner->header.prog_name);
	wmove(vm->wins.stats_win, offset + 1, 1);
	// wclrtoeol(vm->wins.stats_win);
	wprintw(vm->wins.stats_win, "OP name: %s", op.str);
	wmove(vm->wins.stats_win, offset + 2, 1);
	// wclrtoeol(vm->wins.stats_win);
	wprintw(vm->wins.stats_win, "Delay: %u", proc->delay);
	wattroff(vm->wins.stats_win, COLOR_PAIR(proc->owner->id + 1));
	wrefresh(vm->wins.stats_win);
	wattron(vm->wins.stats_win,COLOR_PAIR(WHITEP_BLACK));
	box(vm->wins.stats_win, '|' , '-');
	wattroff(vm->wins.stats_win,COLOR_PAIR(WHITEP_BLACK));
}

int8_t	interpret_instr(t_vm *vm, t_proc *proc)
{
	t_op	op;

	proc->instr.nb_args = 0;
	ft_bzero(proc->instr.args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	op = get_op(vm->arena[proc->pc++].hex);
	proc->pc %= MEM_SIZE;
	if (op.str == 0)
		return (ERROR);
	proc->delay = op.cycle;

	proc->instr.fn = get_instr_fn(op.opcode);
	proc->instr.op = &op;
	proc->instr.instr_size = fill_args(vm, proc, op) + 1;
	proc->pc -= proc->instr.instr_size;
	if (vm->flags & (1 << VISUAL))
		print_player_instr(vm, proc, op);
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
	proc->pc %= MEM_SIZE;
	// check if instr wasn't zjmp
	return (SUCCESS);
}
