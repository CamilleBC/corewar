/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:11 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 10:13:47 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_fork(const t_instr_fn_args *args)
{
	t_proc	*proc;

	if (args->nb_args != args->op->nb_args)
		return ;
	proc = malloc(sizeof(t_proc));
	ft_memcpy(proc, args->proc, sizeof(t_proc));
	proc->pc = addr_to_arena(proc->pc + args->args[0].value.dir % IDX_MOD);
	if (proc->owner->nb_threads % THREADS_ALLOC)
		proc->owner->threads = ft_realloc(proc->owner->threads,
				proc->owner->nb_threads, proc->owner->nb_threads + THREADS_ALLOC);
	proc->owner->threads[proc->owner->nb_threads++] = proc;
	ft_deque_push_front(args->vm->procs, proc);
}
