/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:50:30 by briviere          #+#    #+#             */
/*   Updated: 2018/04/16 15:43:01 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_hex(unsigned char hex)
{
	unsigned char	decade;

	decade = hex / 16;
	hex %= 16;
	if (decade >= 10)
		ft_putchar(decade - 10 + 'a');
	else
		ft_putchar(decade + '0');
	if (hex >= 10)
		ft_putchar(hex - 10 + 'a');
	else
		ft_putchar(hex + '0');
}

static void	debug_print_pc(uint32_t pc)
{
	ft_putstr("0x");
	print_hex((pc >> 8) & 0xff);
	print_hex(pc & 0xff);
}

static void	debug_print_arena(const t_arena arena[MEM_SIZE], uint32_t pc,
		size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		print_hex(arena[pc].hex);
		i++;
		if (i < len)
			ft_putchar(' ');
		pc = (pc + 1) % MEM_SIZE;
	}
}

void		debug_print_proc(const t_vm *vm, const t_proc *proc)
{
	if (vm->verbose && !(vm->flags & (1 << VISUAL)))
	{
		ft_putchar('(');
		debug_print_pc(proc->pc);
		ft_putstr(" -> ");
		debug_print_pc(proc->pc + proc->instr.instr_size);
		ft_putchar(')');
		ft_putchar(' ');
		debug_print_arena(vm->arena, proc->pc, proc->instr.instr_size);
		ft_putchar('\n');
	}
}

void		debug_print_regs(const t_proc *proc)
{
	size_t	reg;

	reg = 0;
	while (reg < REG_NUMBER)
	{
		ft_putchar('r');
		if (reg < 9)
			ft_putchar(' ');
		ft_putnbr(reg + 1);
		ft_putstr(": 0x");
		print_hex(proc->regs[reg] >> 24 & 0xff);
		print_hex(proc->regs[reg] >> 16 & 0xff);
		print_hex(proc->regs[reg] >> 8 & 0xff);
		print_hex(proc->regs[reg] & 0xff);
		ft_putchar('\n');
		reg++;
	}
	dprintf(2, "\n");
}
