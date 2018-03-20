/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:58:11 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 16:05:48 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_fork(t_vm *vm, t_proc *proc)
{
	t_proc	*proc_f;
	t_instr	instr;

	instr = proc->instr;
	if (instr.nb_args != 1)
		return ;
	proc_f = malloc(sizeof(t_proc));
	ft_memcpy(proc_f, proc, sizeof(t_proc));
	proc_f->pc = (proc_f->pc + instr.args[0].value.dir % IDX_MOD) % MEM_SIZE;
	if (!(proc_f->owner->nb_threads % THREADS_ALLOC))
		proc_f->owner->threads = ft_realloc(proc_f->owner->threads,
				proc_f->owner->nb_threads, proc_f->owner->nb_threads + THREADS_ALLOC);
	proc_f->owner->threads[proc_f->owner->nb_threads++] = proc_f;
	ft_deque_push_front(vm->procs, proc_f);
}
