/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:36:00 by chaydont          #+#    #+#             */
/*   Updated: 2018/03/15 16:55:30 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include "lexer.h"

int				compile(t_tok *file);
void			ft_putint_fd(int n, int fd);
void			ft_putshort_fd(short n, int fd);
int				get_label_pos(t_tok *file, char *label);
t_header		get_header(t_tok *file);
int				get_op_length(t_tok *file);

#endif
