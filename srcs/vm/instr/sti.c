/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:02 by briviere          #+#    #+#             */
/*   Updated: 2018/04/11 10:22:43 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static uint32_t	read_val(t_vm *vm, t_proc *proc, const t_arg *arg)
{
	uint32_t	val;

	if (arg->code == DIR_CODE)
		val = arg->value.dir;
	else if (arg->code == IND_CODE)
		val = read_arena(vm->arena, (proc->pc + arg->value.ind) % MEM_SIZE, 4);
	else
	{
		if (!is_valid_reg(arg->value.reg))
			return (0);
		val = proc->regs[arg->value.reg - 1];
	}
	return (val);
}

void			instr_sti(t_vm *vm, t_proc *proc)
{
	uint8_t	reg;
	int		reg_val;
	int16_t	addr;
	t_instr	instr;

	instr = proc->instr;
	if (instr.nb_args != 3)
		return ;
	reg = instr.args[0].value.reg;
	if (!is_valid_reg(reg))
		return ;
	reg_val = proc->regs[reg - 1];
	addr = read_val(vm, proc, instr.args + 1);
	if (instr.args[2].code == DIR_CODE)
		addr += (int16_t)instr.args[2].value.dir % IDX_MOD;
	else if (instr.args[2].code == REG_CODE)
	{
		if (!is_valid_reg(instr.args[2].value.reg))
			return ;
		addr += (int16_t)(proc->regs[instr.args[2].value.reg - 1]);
	}
	else
		return ;
	addr = (proc->pc + ((int16_t)addr % IDX_MOD)) % MEM_SIZE;
	write_arena(vm->arena, reg_val, addr, 4, proc->owner->colour);
}
