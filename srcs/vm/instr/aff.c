/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:53 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 00:55:52 by tgunzbur         ###   ########.fr       */
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
	if (instr.args[0].code != T_REG || instr.args[0].value.reg > REG_NUMBER)
		return ;
	reg = instr.args[0].value.reg - 1;
	val = proc->regs[reg] % 256;
	if ((!(vm->flags & (1 << VISUAL))) && (!(vm->flags & (1 << DUMP))))
		write(1, &val, 1);
}
