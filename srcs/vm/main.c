/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/16 13:27:48 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>


void	test_interpret(t_vm vm)
{
	while (interpret_instr(vm.players[0]->prog, vm.players[0], vm.procs->head->data) == SUCCESS)
		;
}

int		main(int ac, char **av)
{
	int32_t	i;
	int		*fds;
	t_vm	vm;

	parse_args(&vm, ac, av);
	if (!(fds = ft_memalloc(sizeof(int) * ac)))
		return (-1);
	i = 0;
	// TODO: check errors
	while (++i < ac)
		fds[i - 1] = open(av[i], O_RDONLY);
	vm.nb_players = ac - 1;
	init_vm(&vm, fds);
	i = -1;
	while (++i < vm.nb_players)
		ft_print("Player #%d: %s\n", i, vm.players[i]->header.prog_name);
	test_interpret(vm);
	return (0);
}
