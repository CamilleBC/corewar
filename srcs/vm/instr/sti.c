/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:02 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 17:20:01 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int8_t	read_val(t_vm *vm, t_proc *proc, const t_arg *arg, int16_t *res)
{
	uint16_t	val;

	if (arg->code == DIR_CODE)
		val = arg->value.dir;
	else if (arg->code == IND_CODE)
		val = read_arena((t_arena_args){vm->arena,
				(proc->pc + arg->value.ind) % MEM_SIZE, 4});
	else if (arg->code == REG_CODE)
		val = proc->regs[arg->value.reg - 1];
	else
		return (ERROR);
	*res = val;
	return (SUCCESS);
}

static int8_t	read_val2(t_proc *proc, const t_arg *arg, int16_t *res)
{

	if (arg->code == DIR_CODE)
		*res += arg->value.dir % IDX_MOD;
	else if (arg->code == REG_CODE)
		*res += proc->regs[arg->value.reg - 1];
	else
		return (ERROR);
	return (SUCCESS);
}

void			instr_sti(t_vm *vm, t_proc *proc)
{
	uint32_t	reg_val;
	int16_t		addr;
	t_instr		instr;

	instr = proc->instr;
	if (instr.nb_args != 3)
		return ;
	reg_val = proc->regs[instr.args[0].value.reg - 1];
	if (read_val(vm, proc, instr.args + 1, &addr) == ERROR)
		return ;
	if (read_val2(proc, instr.args + 2, &addr) == ERROR)
		return ;
	addr = (proc->pc + (addr % IDX_MOD)) % MEM_SIZE;
	dprintf(2, "cycle: %llu\n", vm->total_cycles);
	debug_print_regs(proc);
	write_arena((t_arena_args){vm->arena, addr, 4}, reg_val,
			proc->owner->colour);
}
