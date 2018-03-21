/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 09:19:25 by briviere          #+#    #+#             */
/*   Updated: 2018/03/21 16:48:57 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	instr_live(t_vm *vm, t_proc *proc)
{
	size_t		i;
	uint32_t	id;
	uint32_t	id_player;

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
			break ;
		}
		++i;
	}
}
