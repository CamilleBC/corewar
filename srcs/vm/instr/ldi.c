/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:54 by briviere          #+#    #+#             */
/*   Updated: 2018/04/16 14:59:16 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** This functions works like ZAZ's VM. It means if you give ldi an indirect,
** it will go to the address, read the value and use that.
*/

static int16_t	return_arg_value(int code, t_arg_val arg_value,
					t_proc *proc, t_vm *vm)
{
	int16_t	addr;

	if (code == DIR_CODE)
		return ((int16_t)arg_value.dir);
	else if (code == REG_CODE)
		return (proc->regs[arg_value.reg - 1]);
	else if (code == IND_CODE)
	{
		addr = (proc->pc + arg_value.ind) % MEM_SIZE;
		return (read_arena((t_arena_args){vm->arena, addr, 4}));
	}
	else
		return (0);
}

void			instr_ldi(t_vm *vm, t_proc *proc)
{
	int16_t		addr;
	uint8_t		reg;
	int16_t		val1;
	int16_t		val2;
	t_instr		instr;

	instr = proc->instr;
	if (instr.nb_args != 3 || instr.args[2].code != T_REG)
		return ;
	reg = instr.args[2].value.reg - 1;
	val1 = return_arg_value(instr.args[0].code, instr.args[0].value, proc, vm);
	val2 = return_arg_value(instr.args[1].code, instr.args[1].value, proc, vm);
	addr = ((int16_t)(val1 + val2)) % IDX_MOD;
	proc->regs[reg] = read_arena((t_arena_args){vm->arena,
			(proc->pc + addr) % MEM_SIZE, REG_SIZE});
}
