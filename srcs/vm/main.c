/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/16 19:06:12 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>


void	test_interpret(t_vm vm)
{
	t_proc	*proc;

	proc = vm.procs->head->data;
	while (interpret_instr(&vm, vm.players[0], proc) == SUCCESS)
	{
		if (vm.flags & (1 << VISUAL))
		{
			print_arena(&vm);
			print_header(&vm);
			print_stats(&vm);
			mvwprintw(vm.wins.stats_win, 1, 1, "%d", proc->pc);
			mvwprintw(vm.wins.stats_win, 2, 1, "%d", vm.arena[proc->pc].hex);
			for (int i = 0; i < REG_NUMBER; i++)
			{
				mvwprintw(vm.wins.stats_win, 3 + i, 1, "r%d: %08x", i + 1, proc->regs[i]);
			}
			wrefresh(vm.wins.stats_win);
			//usleep(500000);
			sleep(1);
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
	dprintf(2, "lives: %ld\n", vm.players[0]->live);
	ft_print("lives: %d\n", vm.players[0]->live);
	for (int i = 1; i <= REG_NUMBER; i++)
	{
		dprintf(2, "r%d: ", i);
		dprintf(2, "%08x\n", ((t_proc *)vm.procs->head->data)->regs[i - 1]);
		fflush(stdout);
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
	// TODO: check errors
	while (++i < ac)
	{
		if (av[i][0] != '-')
			fds[i_fd++] = open(av[i], O_RDONLY);
	}
	vm.nb_players = i_fd;
	if (init_vm(&vm, fds) == ERROR)
		return (0);
	if (vm.flags & (1 << VISUAL))
		init_visu(&vm);
	//i = -1;
	//while (++i < vm.nb_players)
	//	ft_print("Player #%d: %s\n", i, vm.players[i]->header.prog_name);
	test_interpret(vm);
	// if (vm.flags & (1 << VISUAL))
	// {
	// 	print_arena(&vm);
		// print_header(&vm);
		// print_stats(&vm);
	// }
	while (1)
		;
	if (vm.flags & (1 << VISUAL))
		free_visu(vm.wins, vm.nb_players);
	return (0);
}
