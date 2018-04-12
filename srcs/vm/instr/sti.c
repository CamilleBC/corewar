/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:02 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 13:03:40 by briviere         ###   ########.fr       */
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
				(proc->pc + (int16_t)arg->value.ind) % MEM_SIZE, 4});
	else
	{
		if (!is_valid_reg(arg->value.reg))
			return (0);
		val = proc->regs[arg->value.reg - 1];
	}
	return (val);
}

static int16_t	read_val2(t_proc *proc, const t_arg *arg)
{
	if (arg->code == DIR_CODE)
		return ((int16_t)arg->value.dir % IDX_MOD);
	else if (arg->code == REG_CODE)
	{
		if (!is_valid_reg(arg->value.reg))
			return (0);
		return ((int16_t)(proc->regs[arg->value.reg - 1]));
	}
	else
		return (0);
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
	addr += read_val2(proc, instr.args + 2);
	addr = (proc->pc + ((int16_t)addr % IDX_MOD)) % MEM_SIZE;
	write_arena((t_arena_args){vm->arena, addr, 4}, reg_val,
			proc->owner->colour);
}
