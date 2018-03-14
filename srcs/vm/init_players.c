/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 09:41:36 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/14 16:23:58 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int8_t	init_player(t_player *player, t_vm *vm, size_t address)
{
	size_t	i;

	i = 0;
	while (i < player->instr_size)
	{
		vm->arena[address + i].hex = player->instr[i];
		vm->arena[address + i].colour = player->id;
	}
	return (SUCCESS);
}

int8_t			init_arena_players(t_vm *vm)
{
	size_t	i;
	size_t	address;
	double	div;

	i = 0;
	while (i < vm->nb_players)
	{
		div = ft_round(MEM_SIZE / vm->nb_players);
		address = (MEM_SIZE - (div * (i + 1))) < 0 ?
			0 : MEM_SIZE - (div * (i + 1));
		ft_print("address: %u\n", address);
		init_player(vm->players[i], vm, address);
		i++;
	}
	return (SUCCESS);
}
