/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:02 by briviere          #+#    #+#             */
/*   Updated: 2018/04/16 19:10:51 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int8_t	read_val(t_vm *vm, t_proc *proc, const t_arg *arg,
		int32_t *res)
{
	if (arg->code == DIR_CODE)
		*res = arg->value.dir;
	else if (arg->code == IND_CODE)
		*res = read_arena((t_arena_args){vm->arena,
				(proc->pc + arg->value.ind) % MEM_SIZE, 2});
	else if (arg->code == REG_CODE)
		*res = proc->regs[arg->value.reg - 1];
	else
		return (ERROR);
	return (SUCCESS);
}

static int8_t	read_val2(t_proc *proc, const t_arg *arg, int32_t *res)
{
	if (arg->code == DIR_CODE)
		*res += arg->value.dir;
	else if (arg->code == REG_CODE)
		*res += proc->regs[arg->value.reg - 1];
	else
		return (ERROR);
	return (SUCCESS);
}

void			instr_sti(t_vm *vm, t_proc *proc)
{
	uint32_t	reg_val;
	int32_t		addr;
	t_instr		instr;

	instr = proc->instr;
	if (instr.nb_args != 3)
		return ;
	reg_val = proc->regs[instr.args[0].value.reg - 1];
	if (read_val(vm, proc, instr.args + 1, &addr) == ERROR)
		return ;
	if (read_val2(proc, instr.args + 2, &addr) == ERROR)
		return ;
	if (addr < 32768)
		addr = (proc->pc + (addr % IDX_MOD)) % MEM_SIZE;
	else
		addr = (proc->pc + ((addr - 65536) % -IDX_MOD)) % MEM_SIZE;
	write_arena((t_arena_args){vm->arena, addr, 4}, reg_val,
			proc->owner->colour);
}
