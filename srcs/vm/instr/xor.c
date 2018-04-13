/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <tgunzbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:33 by briviere          #+#    #+#             */
/*   Updated: 2018/04/14 01:12:06 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static uint32_t	read_val(t_vm *vm, t_proc *proc, const t_arg *arg)
{
	uint32_t	val;

	if (arg->code == DIR_CODE)
		val = arg->value.dir;
	else if (arg->code == IND_CODE)
		val = read_arena((t_arena_args){vm->arena,
				(proc->pc + arg->value.ind) % MEM_SIZE, 4});
	else if (arg->code == REG_CODE)
		val = proc->regs[arg->value.reg - 1];
	else
		return (0);
	return (val);
}

void			instr_xor(t_vm *vm, t_proc *proc)
{
	uint8_t		reg_dst;
	uint32_t	val;
	t_instr		instr;

	instr = proc->instr;
	if (instr.nb_args != 3)
		return ;
	if (instr.args[2].code != REG_CODE || instr.args[2].value.reg > REG_NUMBER)
		return ;
	reg_dst = instr.args[2].value.reg - 1;
	val = read_val(vm, proc, instr.args + 0);
	val ^= read_val(vm, proc, instr.args + 1);
	proc->regs[reg_dst] = val;
	proc->carry = !proc->regs[reg_dst];
}
