/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:53 by briviere          #+#    #+#             */
/*   Updated: 2018/04/10 14:48:50 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_aff(t_vm *vm, t_proc *proc)
{
	uint8_t		reg;
	uint8_t		val;
	t_instr		instr;

	instr = proc->instr;
	if (vm->flags & (1 << VISUAL) || instr.nb_args != 1)
		return ;
	if (instr.args[0].code != instr.op->args[0])
		return ;
	reg = instr.args[0].value.reg;
	if (!is_valid_reg(reg))
		return ;
	val = proc->regs[reg - 1] % 256;
	write(1, &val, 1);
}
