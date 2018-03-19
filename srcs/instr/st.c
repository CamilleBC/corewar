/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:16:18 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 09:14:51 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_st(const t_instr_fn_args *args)
{
	uint8_t		reg;
	uint64_t	val;
	t_arg		arg;
	int32_t		addr;

	if (args == 0 || args->nb_args != 2)
	{
		args->proc->carry = 0;
		return ;
	}
	reg = args->args[0].value.reg;
	if (!is_valid_reg(reg))
	{
		args->proc->carry = 0;
		return ;
	}
	val = args->proc->regs[reg - 1];
	arg = args->args[1];
	if (arg.code == IND_CODE)
	{
		addr = addr_to_arena(args->proc->pc + (arg.value.ind % IDX_MOD));
		write_arena(args->vm->arena, val, addr, 4);
	}
	else if (arg.code == REG_CODE)
	{
		if (!is_valid_reg(arg.value.reg))
		{
			args->proc->carry = 0;
			return ;
		}
		args->proc->regs[arg.value.reg - 1] = val;
	}
	args->proc->carry = 1;
}
