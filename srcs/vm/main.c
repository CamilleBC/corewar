/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/20 17:57:29 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>

void	test_interpret(t_vm vm)
{
	t_proc	*proc;
	size_t	i;
	size_t	len;

	while (1)
	{
		i = 0;
		len = vm.procs->size;
		while (i++ < len)
		{
			proc = ft_deque_pop_back(vm.procs);
			interpret_instr(&vm, proc);
			ft_deque_push_front(vm.procs, proc);
		}
		if (vm.flags & (1 << VISUAL))
		{
			print_arena(&vm);
			print_header(&vm);
			print_stats(&vm);
			usleep(1000);
			// sleep(1);
		}
	}
	if (vm.flags & (1 << VISUAL))
		while (1)
		{
			print_arena(&vm);
			print_header(&vm);
			print_stats(&vm);
			sleep(1);
		}
}

int		main(int ac, char **av)
{
	int		*fds;
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	if (!(fds = parse_args(&vm, ac, av)))
		return (-1);
	if (init_vm(&vm, fds) == ERROR)
		return (0);
	if (vm.flags & (1 << VISUAL))
		init_visu(&vm);
	// test_interpret(vm);
	run_vm(&vm);
	while (1)
		;
	if (vm.flags & (1 << VISUAL))
		free_visu(vm.wins, vm.nb_players);
	return (0);
}
