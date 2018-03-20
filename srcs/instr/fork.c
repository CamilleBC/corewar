/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:11 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 12:33:09 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_fork(t_vm *vm, t_proc *proc)
{
	t_proc	*proc_f;
	t_instr	instr;

	if (args->nb_args != args->op->nb_args)
		return ;
	proc_f = malloc(sizeof(t_proc));
	ft_memcpy(proc_f, proc, sizeof(t_proc));
	proc_f->pc = addr_to_arena(proc_f->pc + instr.args[0].value.dir % IDX_MOD);
	if (!(proc_f->owner->nb_threads % THREADS_ALLOC))
		proc_f->owner->threads = ft_realloc(proc_f->owner->threads,
				proc_f->owner->nb_threads, proc_f->owner->nb_threads + THREADS_ALLOC);
	proc_f->owner->threads[proc_f->owner->nb_threads++] = proc_f;
	ft_deque_push_front(vm->procs, proc_f);
}
