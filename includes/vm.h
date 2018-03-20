/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:58:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/20 16:01:18 by briviere         ###   ########.fr       */
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

# define THREADS_ALLOC 20

# define VERBOSE_PC		1
# define VERBOSE_WRITE	2
# define VERBOSE_READ	3

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

typedef struct	s_player t_player;
typedef struct	s_vm t_vm;
typedef struct	s_proc t_proc;
typedef void	t_instr_fn(t_vm *, t_proc *);

typedef struct	s_instr
{
	t_op		*op;
	t_instr_fn	*fn;
	t_arg		args[MAX_ARGS_NUMBER];
	size_t		nb_args;
	size_t		instr_size;
}				t_instr;


struct			s_proc
{
	uint8_t			carry;
	uint32_t		pc;
	struct s_instr	instr;
	uint32_t		delay;
	uint64_t		live;
	uint32_t		regs[REG_NUMBER];
	t_player		*owner;
};

struct			s_player
{
	t_header	header;
	uint8_t		prog[CHAMP_MAX_SIZE + 1];
	uint32_t	id;
	uint64_t	live;
	t_proc		**threads;
	size_t		nb_threads;
};

typedef struct	s_arena
{
	uint8_t	hex;
	int32_t	colour;
	int32_t	background;
	uint8_t	new_value;
}				t_arena;

struct			s_win;

struct			s_vm
{
	uint8_t			flags;
	t_arena			arena[MEM_SIZE];
	t_deque			*procs;
	t_player		**players;
	uint8_t			nb_players;
	uint64_t		dump;
	uint64_t		total_cycles;
	uint64_t		cycles_to_die;
	struct s_win	wins;
	uint8_t			verbose;
};

typedef struct	s_instr_def
{
	int			opcode;
	t_instr_fn	*fn;
}				t_instr_def;

uint32_t	array_to_int(uint8_t arr[4], size_t size);
uint32_t	array_to_int_arena(t_arena arena[4], size_t size);
void		int_to_array(uint8_t arr[4], uint32_t val, size_t size);
t_instr_fn	*get_instr_fn(int opcode);

void	instr_add(t_vm *vm, t_proc *proc);
void	instr_aff(t_vm *vm, t_proc *proc);
void	instr_and(t_vm *vm, t_proc *proc);
void	instr_fork(t_vm *vm, t_proc *proc);
void	instr_ld(t_vm *vm, t_proc *proc);
void	instr_ldi(t_vm *vm, t_proc *proc);
void	instr_lfork(t_vm *vm, t_proc *proc);
void	instr_live(t_vm *vm, t_proc *proc);
void	instr_lld(t_vm *vm, t_proc *proc);
void	instr_lldi(t_vm *vm, t_proc *proc);
void	instr_or(t_vm *vm, t_proc *proc);
void	instr_st(t_vm *vm, t_proc *proc);
void	instr_st(t_vm *vm, t_proc *proc);
void	instr_sti(t_vm *vm, t_proc *proc);
void	instr_sub(t_vm *vm, t_proc *proc);
void	instr_xor(t_vm *vm, t_proc *proc);
void	instr_zjmp(t_vm *vm, t_proc *proc);

int8_t	interpret_instr(t_vm *vm, t_proc *proc);

int8_t	init_vm(t_vm *vm, int *fds);
int8_t	init_players(t_vm *vm, int *fds);
int32_t	parse_args(t_vm *vm, int ac, char **av);
void	run_vm(t_vm *vm);

void		write_arena(t_arena *arena, uint32_t val, size_t idx, size_t len, int colour);
uint32_t	read_arena(t_arena *arena, size_t idx, size_t len);
int8_t		is_valid_reg(uint8_t reg);
int8_t		are_valid_regs(uint8_t *regs, size_t size);

/*
** Debug function for verbosity
*/

void		debug_print_arena(t_arena *arena, uint32_t pc, size_t len);
void		debug_print_pc(uint32_t pc);

#endif
