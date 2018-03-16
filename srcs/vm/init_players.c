/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 09:41:36 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/16 09:35:43 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
static uint64_t	reverse_bits(uint64_t val)
{
	uint64_t	res;

	res = 0;
	while (val)
	{
		res <<= 8;
		res |= val & 0xff;
		val >>= 8;
	}
	return (res);
}

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
		vm->arena[address + i].colour = player->id;
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
	div = MEM_SIZE / vm->nb_players;
	address = 0;
	while (i < vm->nb_players)
	{
		ft_print("address: %u\n", address);
		vm->players[i]->id = i;
		init_player(vm->players[i], vm, address, fds[i]);
		ft_deque_push_back(vm->procs, ft_memalloc(sizeof(t_proc)));
		i++;
		address += div;
	}
	return (SUCCESS);
}
