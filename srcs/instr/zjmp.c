/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:57:45 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 11:35:04 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_zjmp(const t_instr_fn_args *args)
{
	if (args->nb_args != 1 || !args->proc->carry)
		return ;
	args->proc->pc += MEM_SIZE + args->args[0].value.dir;
	args->proc->pc = addr_to_arena(args->proc->pc);
}
