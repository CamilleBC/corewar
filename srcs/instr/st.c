/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:16:18 by briviere          #+#    #+#             */
/*   Updated: 2018/03/16 17:09:40 by briviere         ###   ########.fr       */
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
	reg = args->args[0].value.reg - 1;
	dprintf(2, "st: reading r%d\n", reg + 1);
	val = args->proc->regs[reg];
	arg = args->args[1];
	// FIXME:
	if (arg.code == IND_CODE)
	{
		dprintf(2, "st: writing at addr %ld\n", args->proc->pc + (arg.value.ind % IDX_MOD));
		write_arena(args->vm->arena, val, args->proc->pc + (arg.value.ind % IDX_MOD), 4);
	}
	else if (arg.code == REG_CODE)
		args->proc->regs[arg.value.reg - 1] = val;
}
