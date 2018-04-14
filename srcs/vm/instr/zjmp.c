/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:45 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 05:29:28 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_zjmp(t_vm *vm, t_proc *proc)
{
	t_instr	instr;

	(void)vm;
	instr = proc->instr;
	if (!proc->carry)
		return ;
	proc->pc += (int16_t)instr.args[0].value.dir % IDX_MOD;
	proc->pc %= MEM_SIZE;
	proc->pc -= (proc->instr.instr_size + 1);
}
