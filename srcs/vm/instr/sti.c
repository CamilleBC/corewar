/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:02 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 16:05:32 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_sti(t_vm *vm, t_proc *proc)
{
	uint8_t	reg;
	int		reg_val;
	int		addr;
	t_instr	instr;

	instr = proc->instr;
	if (instr.nb_args != 3)
	{
		proc->carry = 0;
		return ;
	}
	reg = instr.args[0].value.reg;
	if (!is_valid_reg(reg))
	{
		proc->carry = 0;
		return ;
	}
	reg_val = proc->regs[reg - 1];
	addr = proc->pc;
	if (instr.args[1].code == IND_CODE)
		addr += instr.args[1].value.ind % IDX_MOD;
	else if (instr.args[1].code == DIR_CODE)
		addr += instr.args[1].value.dir % IDX_MOD;
	else
	{
		if (!is_valid_reg(instr.args[1].value.reg))
		{
			proc->carry = 0;
			return ;
		}
		addr += proc->regs[instr.args[1].value.reg - 1] % IDX_MOD;
	}
	if (instr.args[2].code == DIR_CODE)
		addr += (instr.args[2].value.dir % IDX_MOD);
	else if (instr.args[2].code == REG_CODE)
	{
		if (!is_valid_reg(instr.args[2].value.reg))
		{
			proc->carry = 0;
			return ;
		}
		addr += (proc->regs[instr.args[2].value.reg - 1] % IDX_MOD);
	}
	else
	{
		proc->carry = 0;
		return ;
	}
	addr %= MEM_SIZE;
	write_arena(vm->arena, reg_val, addr, 4, proc->owner->id + 1);
}
