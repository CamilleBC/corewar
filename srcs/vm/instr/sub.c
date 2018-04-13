/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:56:47 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 00:56:45 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_sub(t_vm *vm, t_proc *proc)
{
	uint32_t	res;
	uint8_t		regs[3];
	t_instr		instr;

	(void)vm;
	instr = proc->instr;
	if (instr.nb_args != 3 || instr.args[0].code != REG_CODE || instr.args[1].code != REG_CODE || instr.args[2].code != REG_CODE || instr.args[0].value.reg > REG_NUMBER || instr.args[1].value.reg > REG_NUMBER || instr.args[2].value.reg > REG_NUMBER)
		return ;
	regs[0] = instr.args[0].value.reg - 1;
	regs[1] = instr.args[1].value.reg - 1;
	regs[2] = instr.args[2].value.reg - 1;
	res = proc->regs[regs[0]];
	res -= proc->regs[regs[1]];
	proc->regs[regs[2]] = res;
	proc->carry = !proc->regs[regs[2]];
}
