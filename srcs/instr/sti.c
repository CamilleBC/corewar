/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:02 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 09:27:19 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_sti(const t_instr_fn_args *args)
{
	uint8_t	reg;
	int		reg_val;
	int		addr;

	if (args->nb_args != 3)
	{
		args->proc->carry = 0;
		return ;
	}
	reg = args->args[0].value.reg - 1;
	reg_val = args->proc->regs[reg];
	if (args->args[1].code == IND_CODE)
		addr = args->proc->pc + (args->args[1].value.ind % IDX_MOD);
	else if (args->args[1].code == DIR_CODE)
		addr = array_to_int_arena(args->vm->arena + addr_to_arena(args->args[1].value.dir), 2);
	else
	{
		if (!is_valid_reg(args->args[1].value.reg))
		{
			args->proc->carry = 0;
			return ;
		}
		addr = args->proc->pc + (args->proc->regs[args->args[1].value.reg - 1] % IDX_MOD);
	}
	if (args->args[2].code == IND_CODE)
		addr += (args->args[2].value.ind % IDX_MOD);
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
	write_arena(args->vm->arena, reg_val, addr, 4);
}
