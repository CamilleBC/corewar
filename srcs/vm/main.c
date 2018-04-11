/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/04/11 18:08:14 by cbaillat         ###   ########.fr       */
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
		if (-vm.players[i]->id - 1 == id)
			return (vm.players[i]);
	return (NULL);
}

static void		free_vm(t_vm vm)
{
	int64_t	i;

	i = 0;
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

int				main(int ac, char **av)
{
	int			*fds;
	t_vm		vm;
	t_player	*winner;

	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = 1;
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
	winner = get_player_by_id(vm.last_live_id, vm);
	ft_print("le joueur %d(%s) a gagne\n", vm.last_live_id, winner->header.prog_name);
	free_vm(vm);
	return (0);
}
