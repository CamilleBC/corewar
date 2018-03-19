/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:36:00 by chaydont          #+#    #+#             */
/*   Updated: 2018/03/19 17:41:03 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include "lexer.h"

int				compile(t_tok *file);
int				verify_list(t_tok *first, t_error *error);
void			ft_putint_fd(int n, int fd);
void			ft_putshort_fd(short n, int fd);
int				get_label_pos(t_tok *file, char *label);
t_header		get_header(t_tok *file);
int				get_op_length(t_tok *file);
t_tok			*push_token(t_tok *token);
t_tok_type		get_token(char *line);
int				get_data(char *line, t_tok_type tok, void **data);
int				find_label(char *label, t_tok *first);
t_tok			*check_strline(t_tok *token);
t_tok			*find_next_line(t_tok *token);
int				is_label(char *line);
int				is_op(char *line);
t_tok			*check_file(char *file, t_error *error);
void			*super_free(t_tok *token, char *line, int fd);
void			write_header(t_header header, int fd);

#endif
