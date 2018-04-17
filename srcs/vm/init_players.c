/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 09:41:36 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/17 15:32:09 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "visu.h"

static int8_t	read_prog(t_player *player, t_fds fd)
{
	if (read(fd.fd, &player->header, sizeof(t_header)) < 0)
		return (ERROR);
	player->header.magic = reverse_bits(player->header.magic);
	player->header.prog_size = reverse_bits(player->header.prog_size);
	if (player->header.magic != COREWAR_EXEC_MAGIC)
		return (ERROR);
	if (player->header.prog_size > CHAMP_MAX_SIZE)
		return (ERROR);
	if (read(fd.fd, &player->prog, CHAMP_MAX_SIZE) < 0)
		return (ERROR);
	return (SUCCESS);
}

static int8_t	init_player(t_player *player, t_vm *vm, size_t address,
					t_fds fd)
{
	size_t		i;
	static int	j;

	if (read_prog(player, fd) == ERROR)
		return (ERROR);
	i = 0;
	if (fd.id > 0)
		player->id = fd.id;
	else
		player->id = --j;
	while (i < player->header.prog_size)
	{
		vm->arena[address + i].hex = player->prog[i];
		vm->arena[address + i].colour = player->colour;
		i++;
	}
	return (SUCCESS);
}

static void		set_player_proc(t_vm *vm, t_proc *proc, size_t address,
					size_t i)
{
	proc->owner = vm->players[i];
	proc->pc = address;
	proc->regs[0] = vm->players[i]->id;
	vm->players[i]->nb_threads = 1;
	vm->players[i]->threads = ft_memalloc(sizeof(t_proc) * THREADS_ALLOC);
	vm->players[i]->threads[0] = proc;
	ft_deque_push_back(vm->procs, proc);
}

int8_t			init_players(t_vm *vm, t_fds *fds)
{
	size_t	i;
	size_t	address;
	long	div;
	t_proc	*proc;

	i = -1;
	div = 0;
	if (vm->nb_players)
		div = MEM_SIZE / vm->nb_players;
	address = 0;
	while (++i < vm->nb_players)
	{
		vm->players[i]->index = i;
		vm->players[i]->colour = COLOUR_OFFSET + i;
		if (init_player(vm->players[i], vm, address, fds[i]) == ERROR)
		{
			ft_print("invalid player %d\n", i + 1);
			return (ERROR);
		}
		if (!(proc = ft_memalloc(sizeof(t_proc))))
			return (ERROR);
		set_player_proc(vm, proc, address, i);
		address += div;
	}
	return (SUCCESS);
}
