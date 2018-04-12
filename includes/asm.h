/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:36:00 by chaydont          #+#    #+#             */
/*   Updated: 2018/04/11 18:37:36 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

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
int				get_data(char *line, t_tok_type tok,
							void **data, t_error *error);
int				find_label(char *label, t_tok *first);
t_tok			*check_strline(t_tok *token, t_error *error);
t_tok			*find_next_line(t_tok *token, t_error *error);
int				is_label(char *line);
int				is_op(char *line);
t_tok			*check_file(char *file, t_error *error);
void			*super_free(t_tok *token, char *line, int fd);
void			write_header(t_header header, int fd);
char			*copy_str(char *line, t_error *error);
int				no_code(t_tok *first_tok);

#endif
