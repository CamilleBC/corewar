/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/04/17 14:37:10 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_player_instr(t_vm *vm, t_proc *proc, t_op *op)
{
	int	offset;

	offset = 6 + (3 * ft_abs32(proc->owner->index));
	clear_win_line(vm->wins.stats_win, vm, offset, 1);
	wmove(vm->wins.stats_win, offset, 1);
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->colour));
	wprintw(vm->wins.stats_win, "Proc owner: %d / %s", proc->owner->id,
		proc->owner->header.prog_name);
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->colour));
	clear_win_line(vm->wins.stats_win, vm, offset + 1, 1);
	wmove(vm->wins.stats_win, offset + 1, 1);
	wprintw(vm->wins.stats_win, "OP name: %s", op->str);
	clear_win_line(vm->wins.stats_win, vm, offset + 2, 1);
	wmove(vm->wins.stats_win, offset + 2, 1);
	wattron(vm->wins.stats_win, COLOR_PAIR(proc->owner->colour));
	wprintw(vm->wins.stats_win, "Delay: %u", proc->instr.op->cycle);
	wattroff(vm->wins.stats_win, COLOR_PAIR(proc->owner->index + 1));
	wrefresh(vm->wins.stats_win);
}

static size_t	fill_arg(t_arena *mem, t_proc *proc, t_arg *arg, size_t idx)
{
	if (arg->code == REG_CODE && (proc->instr.op->args[idx] & T_REG))
	{
		if (!is_valid_reg(mem[proc->pc].hex))
			return (arg->size = 0);
		arg->value.reg = mem[proc->pc++].hex;
		arg->size = 1;
	}
	else if (arg->code == IND_CODE && (proc->instr.op->args[idx] & T_IND))
	{
		arg->value.dir = read_arena((t_arena_args){mem, proc->pc, IND_SIZE});
		proc->pc += IND_SIZE;
		arg->size = IND_SIZE;
	}
	else if (arg->code == DIR_CODE && (proc->instr.op->args[idx] & T_DIR))
	{
		arg->size = (proc->instr.op->dir_size ? DIR_SIZE / 2 : DIR_SIZE);
		arg->value.dir = read_arena((t_arena_args){mem, proc->pc, arg->size});
		proc->pc += arg->size;
	}
	else
		return (arg->size = 0);
	proc->pc %= MEM_SIZE;
	proc->instr.nb_args++;
	return (arg->size);
}

static size_t	fill_args(t_vm *vm, t_proc *proc, t_op *op, int *error)
{
	size_t	idx;
	int		octal;
	size_t	arg_size;
	size_t	tmp;

	octal = 0;
	arg_size = 0;
	if (op->octal)
	{
		octal = vm->arena[proc->pc++ + arg_size++].hex;
		if (octal == 0)
			return (*error = 1);
	}
	idx = 0;
	while (idx < op->nb_args)
	{
		proc->instr.args[idx].code = octal ? octal >> ((3 - idx) * 2) & 0b11 :
			op->args[idx];
		tmp = fill_arg(vm->arena, proc, proc->instr.args + idx, idx);
		if (tmp == 0)
			*error = 1;
		arg_size += tmp;
		idx++;
	}
	return (arg_size);
}

int8_t			interpret_args(t_vm *vm, t_proc *proc)
{
	int		error;

	error = 0;
	if (!proc || !vm || proc->instr.op == 0)
		return (ERROR);
	proc->pc++;
	proc->pc %= MEM_SIZE;
	proc->instr.instr_size = fill_args(vm, proc, proc->instr.op, &error) + 1;
	proc->pc += -proc->instr.instr_size + MEM_SIZE;
	proc->pc %= MEM_SIZE;
	if (error)
	{
		proc->pc++;
		jump_pc_error(vm, proc, proc->instr.op);
		proc->pc %= MEM_SIZE;
		return (ERROR);
	}
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
	proc->pc += -1 + MEM_SIZE;
	proc->pc %= MEM_SIZE;
	proc->delay = proc->instr.op->cycle - 2;
	proc->instr.fn = get_instr_fn(proc->instr.op->opcode);
	if (vm->flags & (1 << VISUAL))
		print_player_instr(vm, proc, proc->instr.op);
	return (SUCCESS);
}
