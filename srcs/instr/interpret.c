/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 16:29:49 by briviere         ###   ########.fr       */
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

static size_t fill_arg(uint8_t *mem, t_proc *proc, t_arg *arg, int dir_size)
{
	if (arg->code == REG_CODE)
	{
		arg->value.reg = mem[proc->pc++];
		arg->size = 1;
	}
	else if (arg->code == IND_CODE)
	{
		arg->value.ind = array_to_int(mem + proc->pc, IND_SIZE);
		//ft_memcpy((uint8_t *)&arg->value.ind, mem + proc->pc, IND_SIZE);
		proc->pc += IND_SIZE;
		arg->size = IND_SIZE;
	}
	else if (arg->code == DIR_CODE)
	{
		arg->value.dir = array_to_int(mem + proc->pc, dir_size);
		//ft_memcpy((uint8_t *)&arg->value.dir, mem + proc->pc, dir_size);
		proc->pc += dir_size;
		arg->size = dir_size;
	}
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
		octal = args->mem[args->proc->pc++];
	idx = 0;
	while (idx < op.nb_arg)
	{
		if (octal)
			args->args[idx].code = octal >> ((3 - idx) * 2) & 0b11;
		else
			args->args[idx].code = op.args[idx];
		arg_size += fill_arg(args->mem, args->proc, args->args + idx,
				(op.dir_size ? DIR_SIZE / 2 : DIR_SIZE));
		args->nb_args++;
		idx++;
	}
	return (arg_size);
}

int8_t	interpret_instr(uint8_t *mem, t_player *pl, t_proc *proc)
{
	t_instr_fn_args	args;
	t_op	op;
	t_instr	instr;
	size_t	len;

	args.mem = mem;
	args.pl = pl;
	args.proc = proc;
	args.nb_args = 0;
	ft_bzero(args.args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	op = get_op(mem[proc->pc++]);
	len = 1;
	instr = get_instr(op);
	if (op.str == 0)
		return (ERROR);
	len += fill_args(&args, op);
	args.proc->pc -= len;
	if (instr.fn)
		instr.fn(&args);
	args.proc->pc += len;
	return (SUCCESS);
}