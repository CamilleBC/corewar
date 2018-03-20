/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:24 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 12:18:53 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_or(const t_instr_fn_args *args)
{
	uint8_t		reg_dst;
	uint32_t	val;

	if (args->nb_args != args->op->nb_args)
	{
		proc->carry = 0;
		return ;
	}
	reg_dst = args->args[2].value.reg;
	if (!is_valid_reg(reg_dst))
	{
		args->proc->carry = 0;
		return ;
	}
	if (args->args[0].code == DIR_CODE || args->args[0].code == IND_CODE)
		val = args->args[0].value.dir;
	else
	{
		if (!is_valid_reg(args->args[0].value.reg))
		{
			args->proc->carry = 0;
			return ;
		}
		val = args->proc->regs[args->args[0].value.reg - 1];
	}
	if (args->args[1].code == DIR_CODE || args->args[1].code == IND_CODE)
		val |= args->args[1].value.dir;
	else
	{
		if (!is_valid_reg(args->args[1].value.reg))
		{
			args->proc->carry = 0;
			return ;
		}
		val |= args->proc->regs[args->args[1].value.reg - 1];
	}
	args->proc->regs[reg_dst - 1] = val;
	args->proc->carry = 1;
}
