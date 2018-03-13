/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 17:11:26 by briviere          #+#    #+#             */
/*   Updated: 2018/03/13 17:15:10 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"

typedef char	t_ind[IND_SIZE];
typedef char	t_dir[DIR_SIZE];
typedef char	t_reg[REG_SIZE];

typedef struct	s_proc {
	size_t	pc;
	int		carry;
	t_reg	regs[REG_NUMBER];
}				t_proc;

typedef struct	s_player {
	t_proc	*threads;
	size_t	nb_threads;
}				t_player;

#endif
