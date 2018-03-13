/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:58:20 by cbaillat          #+#    #+#             */
/*   Updated: 2018/03/13 19:30:29 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdint.h>
# include "op.h"

/*
** VM arena defines
*/

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10
# define MEM_SIZE (4*1024)

/*
** VM champions defines
*/

# define CHAMP_MAX_SIZE (MEM_SIZE / 6)
# define MAX_PLAYERS 4

typedef struct	s_reg
{
	uint8_t	value[REG_SIZE];
}				t_reg;

typedef struct	s_process
{
	uint8_t		carry;
	uint64_t	pc;
	t_reg		registers[REG_NUMBER];
}				t_process;

#endif
