/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:16:18 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 13:03:21 by briviere         ###   ########.fr       */
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
	if (proc->instr.args[0].code != REG_CODE)
		return ;
	reg = proc->instr.args[0].value.reg;
	if (!is_valid_reg(reg))
		return ;
	arg = proc->instr.args[1];
	if (arg.code == IND_CODE)
	{
		addr = (proc->pc + ((int16_t)arg.value.ind % IDX_MOD)) % MEM_SIZE;
		write_arena((t_arena_args){vm->arena, addr, 4}, proc->regs[reg - 1],
				proc->owner->colour);
	}
	else if (arg.code == REG_CODE)
	{
		if (!is_valid_reg(arg.value.reg))
			return ;
		proc->regs[arg.value.reg - 1] = proc->regs[reg - 1];
	}
}
