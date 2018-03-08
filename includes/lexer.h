/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:45:26 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/08 11:59:28 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"

typedef enum	e_tok_type
{
	TOK_USELESS,
	TOK_NAME,
	TOK_COMMENT,
	TOK_LABEL,
	TOK_OP,
	TOK_STR,
	TOK_INDIR_NB,
	TOK_INDIR_LB,
	TOK_DIR_NB,
	TOK_DIR_LB,
	TOK_REG,
	TOK_NEWLINE,
	TOK_UNDEFINED
}				t_tok_type;

typedef struct	s_tok
{
	t_tok_type		tok;
	void			*data;
	struct s_tok	*next;
}				t_tok;

int		verify_list(t_tok **first);
