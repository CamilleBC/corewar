/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 15:50:57 by briviere         ###   ########.fr       */
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

static size_t	fill_args(t_instr_fn_args *args, t_op op)
{
	int		idx;
	int		octal;
	size_t	arg_size;

	octal = 0;
	arg_size = 0;
	if (op.octal)
	{
		arg_size++;
		octal = args->vm->arena[args->proc->pc++].hex;
	}
	idx = 0;
	while (idx < op.nb_arg)
	{
		if (octal)
			args->args[idx].code = octal >> ((3 - idx) * 2) & 0b11;
		else
			args->args[idx].code = op.args[idx];
		arg_size += fill_arg(args->vm->arena, args->proc, args->args + idx,
				(op.dir_size ? DIR_SIZE / 2 : DIR_SIZE));
		args->nb_args++;
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

	args.vm = vm;
	args.proc = proc;
	args.nb_args = 0;
	ft_bzero(args.args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	op = get_op(vm->arena[proc->pc++].hex);
	args.proc->pc = addr_to_arena(args.proc->pc);
	instr = get_instr(op);
	if (op.str == 0)
		return (ERROR);
	len = fill_args(&args, op) + 1;
	args.proc->pc -= len;
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
