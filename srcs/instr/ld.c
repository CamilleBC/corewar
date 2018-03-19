/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:18:13 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 09:17:18 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_ld(const t_instr_fn_args *args)
{
	uint8_t	reg;
	int		addr;

	if (args->nb_args != 2 || args->args[1].code != T_REG)
	{
		args->proc->carry = 0;
		return ;
	}
	reg = args->args[1].value.reg;
	if (!is_valid_reg(reg))
	{
		args->proc->carry = 0;
		return ;
	}
	if (args->args[0].code == DIR_CODE)
		args->proc->regs[reg - 1] = args->args[0].value.dir;
	else if (args->args[0].code == IND_CODE)
	{
		addr = addr_to_arena(args->proc->pc + args->args[0].value.ind);
		args->proc->regs[reg - 1] = array_to_int_arena(args->vm->arena + addr,
				REG_SIZE);
	}
	else
	{
		args->proc->carry = 0;
		return ;
	}
	args->proc->carry = 1;
}
