/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:36:00 by chaydont          #+#    #+#             */
/*   Updated: 2018/03/15 15:58:18 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include <fcntl.h>

# include <stdio.h>

# define TRUE 1
# define FALSE 0

# define PROG_NAME_LENGTH 128
# define COMMENT_LENGTH 2048

# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define COREWAR_EXEC_MAGIC 0x00EA83F3

# define TEST write(1, "test\n", 5);

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

typedef struct	s_op
{
	char	*str;
	int		opcode;
}				t_op;

typedef struct	s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}				t_header;

int				compile(t_tok *file);
void			ft_putint_fd(int n, int fd);
void			ft_putshort_fd(short n, int fd);
void			write_header(t_header header, int fd);
int				get_label_pos(t_tok *file, char *label);
t_header		get_header(t_tok *file);
int				get_op_length(t_tok *file);

#endif
