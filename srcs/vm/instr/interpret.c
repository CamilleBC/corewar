/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:33:20 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 09:04:22 by briviere         ###   ########.fr       */
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

static void fill_arg(uint8_t mem[MEM_SIZE], t_proc *proc, t_arg *arg, int dir_size)
{
	if (arg->code == REG_CODE)
	{
		// TODO: read reg with value
		ft_memcpy(arg->value.reg, mem + proc->pc, 1);
		proc->pc += 1;
	}
	else if (arg->code == IND_CODE)
	{
		ft_memcpy(arg->value.ind, mem + proc->pc, IND_SIZE);
		proc->pc += IND_SIZE;
	}
	else if (arg->code == DIR_CODE)
	{
		ft_memcpy(arg->value.dir, mem + proc->pc, dir_size);
		proc->pc += dir_size;
	}
	else
	{
		ft_memcpy(arg->value.ind, mem + proc->pc, IND_SIZE);
		proc->pc += 2;
	}
}

static void	fill_args(uint8_t mem[MEM_SIZE], t_proc *proc, t_arg args[MAX_ARGS_NUMBER],
		t_op op)
{
	int		idx;
	int		octal;

	octal = 0;
	if (op.octal)
		octal = mem[proc->pc++];
	idx = 0;
	while (idx < op.nb_arg)
	{
		if (octal)
			args[idx].code = octal >> ((3 - idx) * 2) & 0b11;
		else
			args[idx].code = op.args[idx];
		fill_arg(mem, proc, args + idx, (op.dir_size ? DIR_SIZE / 2 : DIR_SIZE));
		idx++;
	}
}

int8_t	interpret_instr(uint8_t mem[MEM_SIZE], t_player *pl, t_proc *proc)
{
	t_op	op;
	uint8_t	octal;
	t_arg	args[MAX_ARGS_NUMBER];

	ft_bzero(args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	op = get_op(mem[proc->pc++]);
	if (op.str == 0)
		return (ERROR);
	octal = 0;
	fill_args(mem, proc, args, op);
	printf("%s:\n", op.str);
	for (int i = 0; i < op.nb_arg; i++)
	{
		int len = 0;
		if (args[i].code == REG_CODE)
		{
			printf(" reg: ");
			len = REG_SIZE;
		}
		else if (args[i].code == DIR_CODE)
		{
			printf(" dir: ");
			len = DIR_SIZE;
		}
		else if (args[i].code == IND_CODE)
		{
			printf(" ind: ");
			len = IND_SIZE;
		}
		else
		{
			printf(" unk: ");
			len = 2;
		}
		for (int j = 0; j < len; j++)
		{
			if (j > 0)
				printf(" ");
			printf("%02x", args[i].value.reg[j]);
		}
		printf("\n");
		fflush(stdout);
	}
	return (SUCCESS);
}
