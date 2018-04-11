/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:18:13 by briviere          #+#    #+#             */
/*   Updated: 2018/04/11 10:14:12 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_ld(t_vm *vm, t_proc *proc)
{
	uint8_t	reg;
	int16_t	addr;
	t_instr	instr;

	instr = proc->instr;
	if (instr.nb_args != 2 || instr.args[1].code != T_REG)
		return ;
	reg = instr.args[1].value.reg;
	if (!is_valid_reg(reg))
		return ;
	if (instr.args[0].code == DIR_CODE)
		proc->regs[reg - 1] = instr.args[0].value.dir;
	else if (instr.args[0].code == IND_CODE)
	{
		addr = proc->pc + ((int16_t)instr.args[0].value.ind % IDX_MOD) %
			MEM_SIZE;
		proc->regs[reg - 1] = read_arena(vm->arena, addr, REG_SIZE);
	}
	proc->carry = !proc->regs[reg - 1];
}
