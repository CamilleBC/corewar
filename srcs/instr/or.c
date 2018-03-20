/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:24 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 12:56:13 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_or(t_vm *vm, t_proc *proc)
{
	//uint32_t	res;
	t_instr	instr;

	(void)vm;
	instr = proc->instr;
	if (instr.nb_args != 3)
	{
		proc->carry = 0;
		return ;
	}
	// TODO:
}
