/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 10:43:06 by briviere         ###   ########.fr       */
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

static void fill_arg(uint8_t *mem, t_proc *proc, t_arg *arg, int dir_size)
{
	if (arg->code == REG_CODE)
	{
		arg->value.reg = mem[proc->pc++];
		arg->size = 1;
	}
	else if (arg->code == IND_CODE)
	{
		ft_memcpy(arg->value.ind, mem + proc->pc, IND_SIZE);
		proc->pc += IND_SIZE;
		arg->size = IND_SIZE;
	}
	else if (arg->code == DIR_CODE)
	{
		ft_memcpy(arg->value.dir, mem + proc->pc, dir_size);
		proc->pc += dir_size;
		arg->size = dir_size;
	}
}

static void	fill_args(t_instr_fn_args *args, t_op op)
{
	int		idx;
	int		octal;

	octal = 0;
	if (op.octal)
		octal = args->mem[args->proc->pc++];
	idx = 0;
	while (idx < op.nb_arg)
	{
		if (octal)
			args->args[idx].code = octal >> ((3 - idx) * 2) & 0b11;
		else
			args->args[idx].code = op.args[idx];
		fill_arg(args->mem, args->proc, args->args + idx,
				(op.dir_size ? DIR_SIZE / 2 : DIR_SIZE));
		args->nb_args++;
		idx++;
	}
}

int8_t	interpret_instr(uint8_t *mem, t_player *pl, t_proc *proc)
{
	t_instr_fn_args	args;
	t_op	op;
	t_instr	instr;

	args.mem = mem;
	args.pl = pl;
	args.proc = proc;
	args.nb_args = 0;
	ft_bzero(args.args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	op = get_op(mem[proc->pc++]);
	instr = get_instr(op);
	if (op.str == 0)
		return (ERROR);
	fill_args(&args, op);
	if (instr.fn)
		instr.fn(&args);
	return (SUCCESS);
}
