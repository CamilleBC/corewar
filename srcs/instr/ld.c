/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:18:13 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 16:22:53 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_ld(const t_instr_fn_args *args)
{
	uint8_t	reg;

	if (args->nb_args != 2)
		return ;
	if (args->args[1].code != T_REG)
		return ;
	reg = args->args[1].value.reg - 1;
	if (args->args[0].code == DIR_CODE)
		args->proc->regs[reg] = args->args[0].value.dir;
	else
		args->proc->regs[reg] = array_to_int(args->mem + args->proc->pc +
				args->args[0].value.ind, REG_SIZE);
}
