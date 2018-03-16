/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:56:47 by briviere          #+#    #+#             */
/*   Updated: 2018/03/16 17:27:41 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_sub(const t_instr_fn_args *args)
{
	uint32_t	res;

	if (args->nb_args != 3)
		return ;
	res = args->proc->regs[args->args[0].value.reg - 1];
	res -= args->proc->regs[args->args[1].value.reg - 1];
	args->proc->regs[args->args[2].value.reg - 1] = res;
	args->proc->carry = 1;
}
