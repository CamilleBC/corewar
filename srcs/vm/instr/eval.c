/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:52:51 by briviere          #+#    #+#             */
/*   Updated: 2018/04/16 16:53:03 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static size_t	size_arg_error(int code, int dir_size)
{
	if (code == REG_CODE)
		return (1);
	if (code == DIR_CODE)
	{
		if (dir_size)
			return (DIR_SIZE / 2);
		else
			return (DIR_SIZE);
	}
	if (code == IND_CODE)
		return (IND_SIZE);
	return (0);
}

void			jump_pc_error(t_vm *vm, t_proc *proc, t_op *op)
{
	size_t	idx;
	int		octal;
	int		code;

	octal = 0;
	if (op->octal)
	{
		octal = vm->arena[proc->pc++].hex;
		if (octal == 0)
			return ;
	}
	idx = 0;
	while (idx < op->nb_args)
	{
		code = octal ? octal >> ((3 - idx) * 2) & 0b11 :
			op->args[idx];
		proc->pc += size_arg_error(code, op->dir_size);
		idx++;
	}
}
