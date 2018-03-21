/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:16:18 by briviere          #+#    #+#             */
/*   Updated: 2018/03/21 15:59:49 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_st(t_vm *vm, t_proc *proc)
{
	uint8_t		reg;
	uint64_t	val;
	t_arg		arg;
	int32_t		addr;

	if (proc->instr.nb_args != 2)
		return ;
	reg = proc->instr.args[0].value.reg;
	if (!is_valid_reg(reg))
		return ;
	val = proc->regs[reg - 1];
	arg = proc->instr.args[1];
	if (arg.code == IND_CODE)
	{
		addr = (proc->pc + (arg.value.ind % IDX_MOD)) % MEM_SIZE;
		write_arena(vm->arena, val, addr, 4, proc->owner->colour);
	}
	else if (arg.code == REG_CODE)
	{
		if (!is_valid_reg(arg.value.reg))
			return ;
		proc->regs[arg.value.reg - 1] = val;
	}
	proc->carry = !val;
}
