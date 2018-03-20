/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:53 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 10:04:42 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_aff(const t_instr_fn_args *args)
{
	uint8_t		reg;
	uint8_t		val;

	if (args->vm->flags & (1 << VISUAL) || args->op->nb_args != args->nb_args)
		return ;
	if (args->args[0].code != args->op->args[0])
		return ;
	reg = args->args[0].value.reg;
	if (!is_valid_reg(reg))
		return ;
	val = args->proc->regs[reg - 1] % 256;
	write(1, &val, 1);
}
