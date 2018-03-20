/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:16:18 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 10:15:32 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_st(t_vm *vm, t_proc *proc)
{
	uint8_t		reg;
	uint64_t	val;
	t_arg		arg;
	int32_t		addr;

	if (args == 0 || args->nb_args != args->op->nb_args)
	{
		proc->carry = 0;
		return ;
	}
	reg = proc->instr.args[0].value.reg;
	if (!is_valid_reg(reg))
	{
		proc->carry = 0;
		return ;
	}
	val = proc->regs[reg - 1];
	arg = proc->instr.args[1];
	if (arg.code == IND_CODE)
	{
		addr = addr_to_arena(proc->pc + (arg.value.ind % IDX_MOD));
		write_arena(vm->arena, val, addr, 4, proc->owner->id + 1);
	}
	else if (arg.code == REG_CODE)
	{
		if (!is_valid_reg(arg.value.reg))
		{
			proc->carry = 0;
			return ;
		}
		proc->regs[arg.value.reg - 1] = val;
	}
	proc->carry = 1;
}
