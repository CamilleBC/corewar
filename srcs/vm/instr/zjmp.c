/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:45 by briviere          #+#    #+#             */
/*   Updated: 2018/04/16 16:41:51 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_zjmp(t_vm *vm, t_proc *proc)
{
	t_instr	instr;

	(void)vm;
	instr = proc->instr;
	if (instr.nb_args != 1 || !proc->carry)
	{
		proc->pc += proc->instr.instr_size;
		proc->pc %= MEM_SIZE;
		return ;
	}
	proc->pc += (int16_t)instr.args[0].value.dir % IDX_MOD;
	proc->pc %= MEM_SIZE;
}
