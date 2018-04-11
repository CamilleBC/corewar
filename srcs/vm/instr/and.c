/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:15 by briviere          #+#    #+#             */
/*   Updated: 2018/04/11 10:21:54 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static uint32_t	read_val(t_vm *vm, t_proc *proc, const t_arg *arg)
{
	uint32_t	val;

	if (arg->code == DIR_CODE)
		val = arg->value.dir;
	else if (arg->code == IND_CODE)
		val = read_arena(vm->arena, (proc->pc + arg->value.ind) % MEM_SIZE, 4);
	else
	{
		if (!is_valid_reg(arg->value.reg))
			return (0);
		val = proc->regs[arg->value.reg - 1];
	}
	return (val);
}

void			instr_and(t_vm *vm, t_proc *proc)
{
	uint8_t		reg_dst;
	uint32_t	val;
	t_instr		instr;

	instr = proc->instr;
	if (instr.nb_args != 3)
		return ;
	reg_dst = instr.args[2].value.reg;
	if (!is_valid_reg(reg_dst))
		return ;
	val = read_val(vm, proc, instr.args + 0);
	val &= read_val(vm, proc, instr.args + 1);
	proc->regs[reg_dst - 1] = val;
	proc->carry = !val;
}
