/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:02 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 10:16:06 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_sti(const t_instr_fn_args *args)
{
	uint8_t	reg;
	int		reg_val;
	int		addr;

	if (args->nb_args != args->op->nb_args)
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
	reg_val = args->proc->regs[reg - 1];
	addr = args->proc->pc;
	if (args->args[1].code == IND_CODE)
		addr += args->args[1].value.ind % IDX_MOD;
	else if (args->args[1].code == DIR_CODE)
		addr += args->args[1].value.dir % IDX_MOD;
	else
	{
		if (!is_valid_reg(args->args[1].value.reg))
		{
			args->proc->carry = 0;
			return ;
		}
		addr += args->proc->regs[args->args[1].value.reg - 1] % IDX_MOD;
	}
	if (args->args[2].code == DIR_CODE)
		addr += (args->args[2].value.dir % IDX_MOD);
	else if (args->args[2].code == REG_CODE)
	{
		if (!is_valid_reg(args->args[2].value.reg))
		{
			args->proc->carry = 0;
			return ;
		}
		addr += (args->proc->regs[args->args[2].value.reg - 1] % IDX_MOD);
	}
	else
	{
		args->proc->carry = 0;
		return ;
	}
	addr = addr_to_arena(addr);
	write_arena(args->vm->arena, reg_val, addr, 4, args->proc->owner->id + 1);
}
