/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 09:34:24 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int8_t    get_arg(int arg, int valid_arg, int dir_size)
{
    if (arg == REG_CODE && (valid_arg & T_REG))
        return (1);
    else if (arg == IND_CODE && (valid_arg & T_IND))
        return (IND_SIZE);
    else if (arg == DIR_CODE && (valid_arg & T_DIR))
        return (dir_size ? 2 : 4);
    else
        return (0);
}

static size_t    get_instr_size(t_op op, int octal)
{
    int i;
    int arg_size;
    int instr_size;

    i = 0;
    instr_size = 1;
    if (!op.octal)
        return ((op.dir_size ? 2 : 4));
    while (i < (int)op.nb_args && (arg_size = get_arg(octal >> ((3 - i) * 2) & 0b11, op.args[i], op.dir_size)))
    {
		instr_size += arg_size;
		i++;
	}
	if (!arg_size)
		return (1);
    return (instr_size);
}

static size_t	fill_arg(t_arena *mem, t_proc *proc, t_arg *arg, int dir_size)
{
	if (arg->code == REG_CODE)
	{
		if (!is_valid_reg(mem[proc->pc].hex))
			return (arg->size = 0);
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
		arg->value.dir = array_to_int_arena(mem + proc->pc, (dir_size ? 2 : 4));
		proc->pc += (dir_size ? 2 : 4);
		arg->size = (dir_size ? 2 : 4);
	}
	else
		return (arg->size = 0);
	proc->pc %= MEM_SIZE;
	proc->instr.nb_args++;
	return (arg->size);
}

static size_t	fill_args(t_vm *vm, t_proc *proc, t_op op, int *error)
{
	size_t	idx;
	int		octal;
	size_t	arg_size;
	size_t	tmp;

	octal = 0;
	arg_size = 0;
	if (op.octal)
	{
		arg_size++;
		octal = vm->arena[proc->pc++].hex;
		proc->pc %= MEM_SIZE;
	}
	idx = 0;
	while (idx < op.nb_args)
	{
		proc->instr.args[idx].code = octal ? octal >> ((3 - idx) * 2) & 0b11 :
			op.args[idx];
		tmp = fill_arg(vm->arena, proc, proc->instr.args + idx, op.dir_size);
		if (tmp == 0)
		{
			*error = 1;
			proc->pc -= arg_size;
			return (0);
		}
		arg_size += tmp;
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
	wprintw(vm->wins.stats_win, "Delay: %u", proc->instr.op.cycle);
	wattroff(vm->wins.stats_win, COLOR_PAIR(proc->owner->id + 1));
	wrefresh(vm->wins.stats_win);
}

int8_t			interpret_args(t_vm *vm, t_proc *proc)
{
	int		error;

	error = 0;
	if (!proc || !vm || proc->instr.op.opcode == 0)
		return (ERROR);
	proc->pc++;
	proc->pc %= MEM_SIZE;
	proc->pc -= fill_args(vm, proc, proc->instr.op, &error);
	proc->pc %= MEM_SIZE;
	if (error)
		return (ERROR);
	return (SUCCESS);
}

int8_t			interpret_instr(t_vm *vm, t_proc *proc)
{
	proc->instr.instr_size = 0;
	proc->instr.nb_args = 0;
	proc->delay = 0;
	proc->pc %= MEM_SIZE;
	proc->instr.op = get_op((int)vm->arena[proc->pc++].hex);
	proc->pc %= MEM_SIZE;
	if (proc->instr.op.opcode == 0)
		return (ERROR);
	proc->instr.instr_size = get_instr_size(proc->instr.op, vm->arena[proc->pc].hex);
	if (proc->instr.instr_size == 1)
	{
		if (proc->instr.op.opcode == 3)
			proc->instr.instr_size = 3;
		else
			proc->instr.instr_size = 2;
		proc->instr.op.opcode = -1;
		proc->pc--;
		proc->pc %= MEM_SIZE;
		proc->delay = proc->instr.op.cycle - 2;
		return (SUCCESS);
	}
	proc->pc--;
	proc->pc %= MEM_SIZE;
	proc->delay = proc->instr.op.cycle - 2;
	proc->instr.fn = get_instr_fn(proc->instr.op.opcode);
	if (vm->flags & (1 << VISUAL))
		print_player_instr(vm, proc, proc->instr.op);
	return (SUCCESS);
}
