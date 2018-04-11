/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/04/11 15:38:26 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


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

static size_t	fill_args(t_vm *vm, t_proc *proc, t_op *op)
{
	size_t	idx;
	int		octal;
	size_t	arg_size;

	octal = 0;
	arg_size = 0;
	if (op->octal)
	{
		arg_size++;
		octal = vm->arena[proc->pc++].hex;
	}
	idx = 0;
	while (idx < op->nb_args)
	{
		if (octal)
			proc->instr.args[idx].code = octal >> ((3 - idx) * 2) & 0b11;
		else
			proc->instr.args[idx].code = op->args[idx];
		arg_size += fill_arg(vm->arena, proc, proc->instr.args + idx,
				(op->dir_size ? DIR_SIZE / 2 : DIR_SIZE));
		proc->instr.nb_args++;
		idx++;
	}
	return (arg_size);
}

static size_t	eval_size_arg(const int code, int dir_size, size_t *pc)
{
	size_t	arg_size;

	arg_size = 0;
	if (code == REG_CODE)
	{
		*pc += 1;
		arg_size = 1;
	}
	else if (code == IND_CODE)
	{
		*pc += IND_SIZE;
		arg_size = IND_SIZE;
	}
	else if (code == DIR_CODE)
	{
		*pc += dir_size;
		arg_size = dir_size;
	}
	*pc %= MEM_SIZE;
	return (arg_size);

}

static size_t	eval_size_args(const t_vm *vm, t_op *op, size_t pc)
{
	
	size_t	idx;
	int		octal;
	size_t	arg_size;

	octal = 0;
	arg_size = 0;
	if (op->octal)
	{
		arg_size++;
		octal = vm->arena[pc++].hex;
	}
	idx = 0;
	while (idx < op->nb_args)
	{
		if (octal)
			arg_size += eval_size_arg(octal >> ((3 - idx) * 2) & 0b11,
					(op->dir_size ? DIR_SIZE / 2 : DIR_SIZE), &pc);
		else
			arg_size += eval_size_arg(op->args[idx],
					(op->dir_size ? DIR_SIZE / 2 : DIR_SIZE), &pc);
		idx++;
	}
	return (arg_size);
}

void			print_player_instr(t_vm *vm, t_proc *proc, t_op *op)
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
	wprintw(vm->wins.stats_win, "OP name: %s", op->str);
	clear_win_line(vm->wins.stats_win, vm, offset + 2, 1);
	wmove(vm->wins.stats_win, offset + 2, 1);
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->colour));
	wprintw(vm->wins.stats_win, "Delay: %u", proc->instr.op->cycle);
	wattroff(vm->wins.stats_win, COLOR_PAIR(proc->owner->id + 1));
	wrefresh(vm->wins.stats_win);
}

int8_t			interpret_args(t_vm *vm, t_proc *proc)
{
	if (!proc || !vm || proc->instr.op == 0)
		return (ERROR);
	proc->pc++;
	proc->pc %= MEM_SIZE;
	fill_args(vm, proc, proc->instr.op);
	proc->pc -= proc->instr.instr_size;
	proc->pc %= MEM_SIZE;
	return (SUCCESS);
}

int8_t			interpret_instr(t_vm *vm, t_proc *proc)
{
	proc->instr.nb_args = 0;
	proc->delay = 0;
	proc->pc %= MEM_SIZE;
	proc->instr.op = get_op(vm->arena[proc->pc++].hex);
	proc->pc %= MEM_SIZE;
	proc->instr.instr_size = 0;
	if (proc->instr.op == 0 || proc->instr.op->str == 0)
		return (ERROR);
	proc->delay = proc->instr.op->cycle - 2;
	proc->instr.fn = get_instr_fn(proc->instr.op->opcode);
	proc->instr.instr_size += eval_size_args(vm, proc->instr.op, proc->pc--) + 1;
	proc->pc %= MEM_SIZE;
	if (vm->flags & (1 << VISUAL))
		print_player_instr(vm, proc, proc->instr.op);
	return (SUCCESS);
}
