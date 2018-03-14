/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:58:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/14 17:08:27 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <errno.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"
# include "op.h"

/*
** VM flags
*/

# define DUMP		(uint8_t)0
# define VISUAL		(uint8_t)1

/*
** VM arena defines
*/

# define CYCLE_TO_DIE	1536
# define CYCLE_DELTA	50
# define NBR_LIVE 		21
# define MAX_CHECKS		10
# define MEM_SIZE		(4*1024)

/*
** VM champions defines
*/

# define CHAMP_MAX_SIZE	(MEM_SIZE / 6)
# define MAX_PLAYERS	4

typedef union	u_arg_val
{
	uint8_t	dir[DIR_SIZE];
	uint8_t	ind[IND_SIZE];
	uint8_t	reg[REG_SIZE];
}				t_arg_val;

typedef struct	s_arg
{
	t_arg_val	value;
	int			code;
}				t_arg;

typedef struct	s_dir
{
	uint8_t	value[DIR_SIZE];
}				t_dir;

typedef struct	s_ind
{
	uint8_t	value[IND_SIZE];
}				t_ind;

typedef struct	s_reg
{
	uint8_t	value[REG_SIZE];
}				t_reg;

typedef struct	s_proc
{
	uint8_t		alive;
	uint8_t		carry;
	size_t		pc;
	t_reg		regs[REG_NUMBER];
}				t_proc;

typedef struct	s_player
{
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	uint8_t		instr[CHAMP_MAX_SIZE + 1];
	size_t		instr_size;
	uint32_t	id;
	uint64_t	live;
	t_proc		*threads;
	size_t		nb_threads;
}				t_player;

typedef struct	s_arena
{
	uint8_t	hex;
	int32_t	colour;
}				t_arena;

typedef struct	s_vm
{
	uint8_t		flags;
	t_arena		arena[MEM_SIZE];
	t_deque		*procs;
	t_player	**players;
	uint8_t		nb_players;
	uint64_t	dump;
	uint64_t	total_cycles;
	uint64_t	cycles_to_die;
}				t_vm;

int8_t	init_vm(t_vm *vm);
int8_t	init_arena_players(t_vm *vm);
int32_t	parse_args(t_vm *vm, int ac, char **av);

int8_t	interpret_instr(uint8_t mem[MEM_SIZE], t_player *pl, t_proc *proc);

#endif
