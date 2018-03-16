/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:16:18 by briviere          #+#    #+#             */
/*   Updated: 2018/03/16 12:31:16 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_st(const t_instr_fn_args *args)
{
	uint8_t		reg;
	uint64_t	val;
	t_arg		arg;

	if (args == 0 || args->nb_args != 2)
		return ;
	reg = args->args[0].value.reg;
	val = args->proc->regs[reg];
	arg = args->args[1];
	if (arg.code == T_IND)
		args->mem[args->proc->pc + (arg.value.ind % IDX_MOD)] = val;
	else
		args->proc->regs[arg.value.reg] = val;
}
