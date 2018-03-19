/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/19 15:11:00 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>


void	test_interpret(t_vm vm)
{
	t_proc	*proc;

	while ((proc = ft_deque_pop_front(vm.procs)))
	{
		//dprintf(2, "pc: %ld\n", proc->pc);
		//dprintf(2, "player %d\n", proc->owner->id);
		//for (int i = 1; i <= REG_NUMBER; i++)
		//{
		//	dprintf(2, "r%d: ", i);
		//	dprintf(2, "%08x\n", proc->regs[i - 1]);
		//	fflush(stdout);
		//}
		//dprintf(2, "\n");
		interpret_instr(&vm, proc);
		ft_deque_push_back(vm.procs, proc);
		if (vm.flags & (1 << VISUAL))
		{
			print_arena(&vm);
			print_header(&vm);
			print_stats(&vm);
			usleep(50000);
			//sleep(1);
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
	int32_t	i;
	size_t	i_fd;
	int		*fds;
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	parse_args(&vm, ac, av);
	if (!(fds = ft_memalloc(sizeof(int) * ac)))
		return (-1);
	i = 0;
	i_fd = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
		{
			if ((fds[i_fd++] = open(av[i], O_RDONLY)) < 0)
			{
				ft_putendl_fd("invalid file", 2);
				return (1);
			}
		}
	}
	vm.nb_players = i_fd;
	if (init_vm(&vm, fds) == ERROR)
		return (0);
	if (vm.flags & (1 << VISUAL))
		init_visu(&vm);
	test_interpret(vm);
	while (1)
		;
	if (vm.flags & (1 << VISUAL))
		free_visu(vm.wins, vm.nb_players);
	return (0);
}
