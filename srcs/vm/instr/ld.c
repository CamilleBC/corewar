/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:18:13 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 04:51:59 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_ld(t_vm *vm, t_proc *proc)
{
	uint8_t	reg;
	int16_t	addr;
	t_instr	instr;

	instr = proc->instr;
	reg = instr.args[1].value.reg - 1;
	if (instr.args[0].code == DIR_CODE)
		proc->regs[reg] = instr.args[0].value.dir;
	else if (instr.args[0].code == IND_CODE)
	{
		addr = (proc->pc + ((int16_t)instr.args[0].value.ind % IDX_MOD)) %
			MEM_SIZE;
		proc->regs[reg] =
			read_arena((t_arena_args){vm->arena, addr, REG_SIZE});
	}
	proc->carry = !proc->regs[reg];
}
