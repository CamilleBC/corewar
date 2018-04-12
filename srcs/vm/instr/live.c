/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 09:19:25 by briviere          #+#    #+#             */
/*   Updated: 2018/04/12 14:08:16 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_live(t_vm *vm, t_proc *proc)
{
	size_t		i;
	int32_t		id;
	int32_t		id_player;

	proc->live++;
	if (proc->instr.nb_args != 1)
		return ;
	id = proc->instr.args[0].value.dir;
	i = 0;
	while (i < vm->nb_players)
	{
		id_player = -vm->players[i]->id - 1;
		if (id == id_player)
		{
			vm->players[i]->live++;
			vm->players[i]->live_in_period++;
			vm->last_live_id = id;
			break ;
		}
		++i;
	}
}
