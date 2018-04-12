/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 12:08:30 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 12:08:41 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

size_t			eval_size_args(const t_vm *vm, t_op *op, size_t pc)
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
