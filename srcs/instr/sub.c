/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:56:47 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 09:07:49 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_sub(const t_instr_fn_args *args)
{
	uint32_t	res;
	uint8_t		regs[3];

	if (args->nb_args != 3)
	{
		args->proc->carry = 0;
		return ;
	}
	regs[0] = args->args[0].value.reg;
	regs[1] = args->args[1].value.reg;
	regs[2] = args->args[2].value.reg;
	if (!are_valid_regs(regs, 3))
	{
		args->proc->carry = 0;
		return ;
	}
	res = args->proc->regs[regs[0] - 1];
	res -= args->proc->regs[regs[1] - 1];
	args->proc->regs[regs[2] - 1] = res;
	args->proc->carry = 1;
}
