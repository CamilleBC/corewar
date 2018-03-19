/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:11 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 13:57:36 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_fork(const t_instr_fn_args *args)
{
	t_proc	*proc;

	if (args->nb_args != 1)
		return ;
	proc = malloc(sizeof(t_proc));
	ft_memcpy(proc, args->proc, sizeof(t_proc));
	proc->pc += MEM_SIZE + args->args[0].value.dir % IDX_MOD;
	proc->pc = addr_to_arena(proc->pc);
	if (proc->owner->nb_threads % 10)
		proc->owner->threads = ft_realloc(proc->owner->threads,
				proc->owner->nb_threads, proc->owner->nb_threads + 10);
	proc->owner->threads[proc->owner->nb_threads++] = proc;
}
