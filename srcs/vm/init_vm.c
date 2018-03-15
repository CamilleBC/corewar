/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:00:30 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/15 13:24:23 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vm	*init_vm(void)
{
	size_t	i;
	t_vm *vm;

	if (!(vm = ft_memalloc(sizeof(*vm))))
		return (NULL);
	vm->nb_players = 2;
	if (!(vm->players = ft_memalloc(sizeof(t_player*) * vm->nb_players)))
		return (NULL);
	i = 0;
	while (i < vm->nb_players)
		if (!(vm->players[i++] = ft_memalloc(sizeof(t_player) * vm->nb_players)))
			return (NULL); // free all player when returning
	vm->players[0]->name[0] = 'B';
	vm->players[0]->name[1] = 'O';
	vm->players[0]->name[2] = 'B';
	vm->players[0]->name[3] = 0;
	vm->players[0]->instr[0] = 0x01;
	vm->players[0]->instr[1] = 0x02;
	vm->players[0]->instr[2] = 0x03;
	vm->players[0]->instr[3] = 0x04;
	vm->players[0]->instr_size = 4;
	vm->players[0]->colour = 0;
	vm->players[1]->name[0] = 'J';
	vm->players[1]->name[1] = 'A';
	vm->players[1]->name[2] = 'Y';
	vm->players[0]->name[3] = 0;
	vm->players[1]->instr[0] = 0x10;
	vm->players[1]->instr[1] = 0x20;
	vm->players[1]->instr[2] = 0x30;
	vm->players[1]->instr[3] = 0x40;
	vm->players[1]->instr_size = 4;
	vm->players[1]->colour = 1;
	vm->dump = 0;
	vm->flags = 0;
	return (vm);
}
