/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:18:13 by briviere          #+#    #+#             */
/*   Updated: 2018/03/15 11:20:35 by briviere         ###   ########.fr       */
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
	ft_memcpy(args->proc->regs[reg].value, args->args[0].value.max,
			args->args[0].size);
}
