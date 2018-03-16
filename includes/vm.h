/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:58:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/16 10:10:43 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <errno.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"
# include "op.h"
# include "visu.h"

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
	uint32_t	dir;
	uint16_t	ind;
	uint8_t		reg;
	uint8_t		arr[4];
}				t_arg_val;

typedef struct	s_arg
{
	t_arg_val	value;
	int			code;
	size_t		size;
}				t_arg;

typedef struct	s_proc
{
	uint8_t		alive;
	uint8_t		carry;
	size_t		pc;
	uint32_t	regs[REG_NUMBER];
}				t_proc;

typedef struct	s_player
{
	t_header	header;
	uint8_t		prog[CHAMP_MAX_SIZE + 1];
	uint32_t	id;
	uint64_t	live;
	t_proc		*threads;
	size_t		nb_threads;
}				t_player;

typedef struct	s_arena
{
	uint8_t	hex;
	int32_t	colour;
	uint8_t	new_value;
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
	WINDOW		*arena_win;
	WINDOW		*header_win;
	WINDOW		*stats_win;
}				t_vm;

typedef struct	s_instr_fn_args
{
	uint8_t		*mem;
	t_player	*pl;
	t_proc		*proc;
	t_arg		args[MAX_ARGS_NUMBER];
	size_t		nb_args;
}				t_instr_fn_args;

// TODO: single struct for instr_fn
typedef void	t_instr_fn(const t_instr_fn_args *);

typedef struct	s_instr
{
	t_op		*op;
	t_instr_fn	*fn;
}				t_instr;

uint32_t	array_to_int(uint8_t arr[4], size_t size);
t_instr	*get_instrs(void);

void	instr_live(const t_instr_fn_args *args);
void	instr_ld(const t_instr_fn_args *args);
void	instr_st(const t_instr_fn_args *args);

int8_t	interpret_instr(uint8_t *mem, t_player *pl, t_proc *proc);

int8_t	init_vm(t_vm *vm, int *fds);
int8_t	init_players(t_vm *vm, int *fds);
int32_t	parse_args(t_vm *vm, int ac, char **av);

#endif
