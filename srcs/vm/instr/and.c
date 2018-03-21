/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:15 by briviere          #+#    #+#             */
/*   Updated: 2018/03/21 15:55:30 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_and(t_vm *vm, t_proc *proc)
{
	uint8_t		reg_dst;
	uint32_t	val;
	t_instr		instr;

	(void)vm;
	instr = proc->instr;
	if (instr.nb_args != 3)
		return ;
	reg_dst = instr.args[2].value.reg;
	if (!is_valid_reg(reg_dst))
		return ;
	if (instr.args[0].code == DIR_CODE)
		val = instr.args[0].value.dir;
	else if (instr.args[0].code == IND_CODE)
		val = read_arena(vm->arena, (proc->pc + instr.args[0].value.dir) % MEM_SIZE, 4);
	else
	{
		if (!is_valid_reg(instr.args[0].value.reg))
			return ;
		val = proc->regs[instr.args[0].value.reg - 1];
	}
	if (instr.args[1].code == DIR_CODE)
		val &= instr.args[1].value.dir;
	else if (instr.args[1].code == IND_CODE)
		val &= read_arena(vm->arena, (proc->pc + instr.args[1].value.ind) % MEM_SIZE, 4);
	else
	{
		if (!is_valid_reg(instr.args[1].value.reg))
			return ;
		val &= proc->regs[instr.args[1].value.reg - 1];
	}
	proc->regs[reg_dst - 1] = val;
	proc->carry = !val;
}
