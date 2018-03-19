/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:00:30 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/19 15:28:48 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int8_t	init_vm(t_vm *vm, int *fds)
{
	int64_t	i;

	if (!(vm->procs = ft_deque_create()))
		return (ERROR);
	if (!(vm->players = ft_memalloc(sizeof(t_player*) * vm->nb_players)))
		return (ERROR);
	i = -1;
	while (++i < vm->nb_players)
		if (!(vm->players[i] = ft_memalloc(sizeof(t_player) * vm->nb_players)))
			return (ERROR);
	i = -1;
	while (++i < MEM_SIZE)
		vm->arena[i].colour = WHITE_BLACK;
	if (init_players(vm, fds) == ERROR)
		return (ERROR);
	vm->dump = 1;
	return (SUCCESS);
}
