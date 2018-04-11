/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/04/11 12:08:45 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_op		get_op(int opcode)
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

static size_t	fill_arg(t_arena *mem, t_proc *proc, t_arg *arg, int dir_size)
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

void			print_player_instr(t_vm *vm, t_proc *proc, t_op op)
{
	int	offset;

	offset = 6 + (3 * ft_abs32(proc->owner->id));
	clear_win_line(vm->wins.stats_win, vm, offset, 1);
	wmove(vm->wins.stats_win, offset, 1);
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->colour));
	wprintw(vm->wins.stats_win, "Proc owner: %d / %s", (-1) - proc->owner->id,
		proc->owner->header.prog_name);
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->colour));
	clear_win_line(vm->wins.stats_win, vm, offset + 1, 1);
	wmove(vm->wins.stats_win, offset + 1, 1);
	wprintw(vm->wins.stats_win, "OP name: %s", op.str);
	clear_win_line(vm->wins.stats_win, vm, offset + 2, 1);
	wmove(vm->wins.stats_win, offset + 2, 1);
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->colour));
	wprintw(vm->wins.stats_win, "Delay: %u", proc->instr.op->cycle);
	wattroff(vm->wins.stats_win, COLOR_PAIR(proc->owner->id + 1));
	wrefresh(vm->wins.stats_win);
}

int8_t			interpret_instr(t_vm *vm, t_proc *proc)
{
	t_op	op;

	proc->instr.nb_args = 0;
	ft_bzero(proc->instr.args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	op = get_op(vm->arena[proc->pc++].hex);
	proc->pc %= MEM_SIZE;
	if (op.str == 0)
		return (ERROR);
	proc->delay = op.cycle - 2;
	proc->instr.fn = get_instr_fn(op.opcode);
	proc->instr.op = &op;
	proc->instr.instr_size = fill_args(vm, proc, op) + 1;
	proc->pc -= proc->instr.instr_size;
	if (vm->flags & (1 << VISUAL))
		print_player_instr(vm, proc, op);
	proc->pc %= MEM_SIZE;
	return (SUCCESS);
}
