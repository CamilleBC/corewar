/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:16:18 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 04:36:26 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_st(t_vm *vm, t_proc *proc)
{
	uint8_t		reg;
	t_arg		arg;
	uint32_t	addr;

	if (proc->instr.nb_args != 2)
		return ;
	if (proc->instr.args[0].code != REG_CODE || proc->instr.args[0].value.reg > REG_NUMBER)
		return ;
	reg = proc->instr.args[0].value.reg - 1;
	arg = proc->instr.args[1];
	if (arg.code == IND_CODE)
	{
		addr = (proc->pc + ((int16_t)arg.value.ind % IDX_MOD)) % MEM_SIZE;
		write_arena((t_arena_args){vm->arena, addr, 4}, proc->regs[reg],
				proc->owner->colour);
	}
	else if (arg.code == REG_CODE)
		proc->regs[arg.value.reg - 1] = proc->regs[reg];
}
