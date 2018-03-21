/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/21 15:20:42 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	int		*fds;
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	vm.dump = 1;
	if (!(fds = parse_args(&vm, ac, av)))
		return (-1);
	if (init_vm(&vm, fds) == ERROR)
		return (0);
	if (vm.flags & (1 << VISUAL))
		init_visu(&vm);
	run_vm(&vm);
	if (vm.flags & (1 << VISUAL))
		free_visu(vm.wins, vm.nb_players);
	return (0);
}
