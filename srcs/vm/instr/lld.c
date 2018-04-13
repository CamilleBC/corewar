/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:21 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 01:06:36 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_lld(t_vm *vm, t_proc *proc)
{
	uint8_t	reg;
	int16_t	addr;
	t_instr	instr;

	instr = proc->instr;
	if (instr.nb_args != 2)
		return ;
	if (instr.args[1].code != REG_CODE || instr.args[1].value.reg > REG_NUMBER)
		return ;
	reg = instr.args[1].value.reg - 1;
	if (instr.args[0].code == DIR_CODE)
		proc->regs[reg] = instr.args[0].value.dir;
	else if (instr.args[0].code == IND_CODE)
	{
		addr = (proc->pc + instr.args[0].value.ind) % MEM_SIZE;
		proc->regs[reg] = read_arena((t_arena_args){vm->arena, addr, 2});
	}
	else
		return ;
	proc->carry = !proc->regs[reg];
}
