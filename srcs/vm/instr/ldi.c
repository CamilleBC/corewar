/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:54 by briviere          #+#    #+#             */
/*   Updated: 2018/03/21 09:39:18 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** This functions works like ZAZ's VM. It means if you give ldi an indirect,
** it will go to the address, read the value and use that.
*/

static int64_t	return_arg_value(int code, t_arg_val arg_value,
					t_proc *proc, t_vm *vm)
{
	int		addr;
	uint8_t	reg;

	if (code == DIR_CODE)
		return ((uint32_t)arg_value.dir);
	else if (code == REG_CODE)
	{
		reg = arg_value.reg;
		if (!is_valid_reg(reg))
		{
			proc->carry = 0;
			return (ERROR);
		}
		return (proc->regs[reg - 1]);
	}
	else if (code == IND_CODE)
	{
		addr = (proc->pc + arg_value.ind) % MEM_SIZE;
		return (array_to_int_arena(vm->arena + addr, REG_SIZE));
	}
	else
	{
		proc->carry = 0;
		return (ERROR);
	}
}

void	instr_ldi(t_vm *vm, t_proc *proc)
{
	int			addr;
	uint8_t		reg;
	int64_t		val1;
	int64_t		val2;
	t_instr	instr;

	instr = proc->instr;
	if (instr.nb_args != 3 || instr.args[3].code != T_REG)
	{
		proc->carry = 0;
		return ;
	}
	reg = instr.args[2].value.reg;
	if (!is_valid_reg(reg))
	{
		proc->carry = 0;
		return ;
	}
	val1 = return_arg_value(instr.args[0].code, instr.args[0].value, proc, vm);
	val2 = return_arg_value(instr.args[1].code, instr.args[1].value, proc, vm);
	if (val1 == ERROR || val2 == ERROR)
	{
		proc->carry = 0;
		return ;
	}
	addr = ((int)(val1 + val2)) % IDX_MOD;
	proc->regs[reg - 1] = array_to_int_arena(vm->arena + addr, REG_SIZE);
	proc->carry = 1;
}
