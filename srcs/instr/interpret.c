/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 12:19:50 by cbaillat         ###   ########.fr       */
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

static t_instr	get_instr(t_op op)
{
	size_t	idx;
	t_instr	*instrs;

	idx = 0;
	instrs = get_instrs();
	while (idx < OP_COUNT)
	{
		if (instrs[idx].op && instrs[idx].op->opcode == op.opcode)
			return (instrs[idx]);
		idx++;
	}
	return (instrs[idx - 1]);
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
		if (dir_size == (DIR_SIZE / 2))
			arg->value.dir = (int16_t)arg->value.dir;
		proc->pc += dir_size;
		arg->size = dir_size;
	}
	proc->pc = addr_to_arena(proc->pc);
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

int8_t	interpret_instr(t_vm *vm, t_proc *proc)
{
	t_instr_fn_args	args;
	t_op	op;
	t_instr	instr;
	size_t	len;

	proc->instr.nb_args = 0;
	ft_bzero(proc->instr.args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	op = get_op(vm->arena[proc->pc++].hex);
	proc->pc = addr_to_arena(proc->pc);
	instr = get_instr(op);
	if (op.str == 0)
		return (ERROR);
	proc->instr.op = &op;
	proc->instr.instr_size = fill_args(vm, proc, op) + 1;
	proc->pc -= len;
	if (vm->verbose >= VERBOSE_PC && !(vm->flags & (1 << VISUAL)))
	{
		ft_putchar('(');
		debug_print_pc(proc->pc);
		ft_putstr(" -> ");
		debug_print_pc(proc->pc + len);
		ft_putchar(')');
		debug_print_arena(vm->arena, proc->pc, len);
		ft_putchar('\n');
	}
	args.proc->pc = addr_to_arena(args.proc->pc);
	if (instr.fn)
		instr.fn(&args);
	// check if instr wasn't zjmp
	if (instr.op->opcode != 9)
	{
		args.proc->pc += len;
		args.proc->pc = addr_to_arena(args.proc->pc);
	}
	return (SUCCESS);
}
