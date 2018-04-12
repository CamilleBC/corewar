/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:49:53 by cbaillat          #+#    #+#             */
/*   Updated: 2018/04/12 16:13:52 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		print_screen(t_vm *vm, uint32_t delay)
{
	print_arena(vm);
	print_header(vm);
	print_stats(vm);
	usleep(delay);
}

uint32_t		manage_delay(uint8_t run, int cycles)
{
	if (run == 1)
		return (20000);
	else if (cycles <= 1)
		return (0);
	else if (cycles <= 10)
		return (250000);
	else if (cycles <= 100)
		return (50000);
	else if (cycles <= 500)
		return (20000);
	else if (cycles <= 1000)
		return (10000);
	else
		return (500);
}

static int8_t	main_vm_loop(t_vm *vm, uint32_t *delay, int *cycles,
		uint8_t run)
{
	if (run || *cycles)
	{
		vm->total_cycles += 1;
		if (vm->flags & (1 << DUMP))
			vm->dump -= 1;
		if (!(vm->total_cycles % vm->cycles_to_die))
			entropy(vm);
		if (loop_procs(vm) == ERROR)
			return (0);
		if (vm->flags & (1 << VISUAL))
		{
			*delay = manage_delay(run, *cycles);
			print_screen(vm, *delay);
		}
		if (*cycles)
			*cycles -= 1;
	}
	return (1);
}

void			run_vm(t_vm *vm)
{
	uint8_t		run;
	int			cycles;
	uint32_t	delay;

	run = 0;
	cycles = 0;
	delay = 0;
	refresh();
	if (vm->flags & (1 << VISUAL))
		print_screen(vm, delay);
	while (vm->cycles_to_die > 0 && vm->dump && vm->procs->head)
	{
		if (!main_vm_loop(vm, &delay, &cycles, run))
			break ;
		if (vm->flags & (1 << VISUAL))
			cycles = manage_user_input(&run, cycles);
		else
			cycles = 1;
	}
}
