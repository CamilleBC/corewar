/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/04/17 15:28:33 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>

static t_player	*get_player_by_id(int64_t id, t_vm vm)
{
	int64_t	i;

	i = -1;
	while (++i < vm.nb_players)
		if (vm.players[i]->id == id)
			return (vm.players[i]);
	return (NULL);
}

static void		free_vm(t_vm vm)
{
	int64_t	i;

	i = -1;
	if (vm.procs)
		ft_deque_delete_data(vm.procs);
	if (vm.players)
		while (++i < vm.nb_players)
		{
			free(vm.players[i]->threads);
			free(vm.players[i]);
		}
	free(vm.players);
}

static void		print_result(t_vm vm)
{
	t_player	*winner;

	if (vm.procs->head == 0 || vm.cycles_to_die <= 0)
	{
		winner = get_player_by_id(vm.last_live_id, vm);
		if (winner)
		{
			ft_putendl(winner->header.comment);
			ft_print("le joueur %d(%s) a gagne\n", vm.last_live_id,
				winner->header.prog_name);
		}
	}
	else if (vm.flags & (1 << DUMP) && vm.dump == 0)
		dump_arena(vm.arena);
}

static int		print_usage(void)
{
	ft_print("./corewar [options] [-n X] player [-n X] player...\n");
	ft_print("options:\n");
	ft_print("	-nc | --ncurses -> displays a visual\n");
	ft_print("	-d | --dump nb->");
	ft_print(" dumps the vm state after nb cycles (int32)\n");
	ft_print("	-v | --verbose -> dumps additional information\n");
	return (0);
}

int				main(int ac, char **av)
{
	t_fds	*fds;
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = 1;
	if (ac == 1)
		return (print_usage());
	if (!(fds = parse_args(&vm, ac, av)))
		return (-1);
	if (init_vm(&vm, fds) == ERROR)
	{
		free_vm(vm);
		return (0);
	}
	free(fds);
	if (vm.flags & (1 << VISUAL))
		init_visu(&vm);
	run_vm(&vm);
	if (vm.flags & (1 << VISUAL))
		free_visu(vm.wins, vm.nb_players);
	print_result(vm);
	free_vm(vm);
	return (0);
}
