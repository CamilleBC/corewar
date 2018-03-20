/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:56:47 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 12:55:31 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_sub(t_vm *vm, t_proc *proc)
{
	uint32_t	res;
	uint8_t		regs[3];
	t_instr		instr;

	(void)vm;
	if (instr.nb_args != 3)
	{
		proc->carry = 0;
		return ;
	}
	regs[0] = instr.args[0].value.reg;
	regs[1] = instr.args[1].value.reg;
	regs[2] = instr.args[2].value.reg;
	if (!are_valid_regs(regs, 3))
	{
		proc->carry = 0;
		return ;
	}
	res = proc->regs[regs[0] - 1];
	res -= proc->regs[regs[1] - 1];
	proc->regs[regs[2] - 1] = res;
	proc->carry = 1;
}
