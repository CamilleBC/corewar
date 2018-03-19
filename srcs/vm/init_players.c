/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 09:41:36 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/19 10:23:56 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int8_t	read_prog(t_player *player, int fd)
{
	if (read(fd, &player->header, sizeof(t_header)) < 0)
		return (ERROR);
	player->header.magic = reverse_bits(player->header.magic);
	player->header.prog_size = reverse_bits(player->header.prog_size);
	if (read(fd, &player->prog, CHAMP_MAX_SIZE) < 0)
		return (ERROR);
	return (SUCCESS);
}

static int8_t	init_player(t_player *player, t_vm *vm, size_t address, int fd)
{
	size_t	i;

	if (read_prog(player, fd) == ERROR)
		return (ERROR);
	i = 0;
	while (i < player->header.prog_size)
	{
		vm->arena[address + i].hex = player->prog[i];
		vm->arena[address + i].colour = player->id + 1;
		i++;
	}
	return (SUCCESS);
}

int8_t			init_players(t_vm *vm, int *fds)
{
	size_t	i;
	size_t	address;
	long	div;

	i = 0;
	div = 0;
	if (vm->nb_players)
		div = MEM_SIZE / vm->nb_players;
	address = 0;
	while (i < vm->nb_players)
	{
		vm->players[i]->id = i;
		init_player(vm->players[i], vm, address, fds[i]);
		ft_deque_push_back(vm->procs, ft_memalloc(sizeof(t_proc)));
		i++;
		address += div;
	}
	return (SUCCESS);
}
