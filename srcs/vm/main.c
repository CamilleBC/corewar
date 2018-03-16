/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:50:22 by briviere          #+#    #+#             */
/*   Updated: 2018/03/16 12:38:25 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>


void	test_interpret(t_vm vm)
{
	while (interpret_instr(vm.players[0]->prog, vm.players[0], vm.procs->head->data) == SUCCESS)
	{
		print_arena(&vm);
		print_header(&vm);
		print_stats(&vm);
		usleep(50000);
	}
	ft_print("lives: %d\n", vm.players[0]->live);
	for (int i = 1; i <= REG_NUMBER; i++)
	{
		printf("r%d: ", i);
		printf("%08x ", ((t_proc *)vm.procs->head->data)->regs[i - 1]);
		printf("\n");
		fflush(stdout);
	}
}

int		main(int ac, char **av)
{
	int32_t	i;
	int		*fds;
	t_vm	vm;

	ft_bzero(&vm, sizeof(t_vm));
	parse_args(&vm, ac, av);
	if (!(fds = ft_memalloc(sizeof(int) * ac)))
		return (-1);
	i = 0;
	// TODO: check errors
	while (++i < ac)
		fds[i - 1] = open(av[i], O_RDONLY);
	vm.nb_players = ac - 1;
	if (init_vm(&vm, fds) == ERROR)
		return (0);
	if (vm.flags & (1 << VISUAL))
		init_visu(&vm);
	i = -1;
	while (++i < vm.nb_players)
		ft_print("Player #%d: %s\n", i, vm.players[i]->header.prog_name);
	test_interpret(vm);
	free_visu(&vm);
	return (0);
}
