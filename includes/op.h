/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:48:19 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/14 13:47:04 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

# define REG_NUMBER 16

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define MAX_ARGS_NUMBER 4
# define IDX_MOD (MEM_SIZE / 8)

# define COMMENT_CHAR	'#'
# define LABEL_CHAR		':'
# define DIRECT_CHAR	'%'
# define SEP_CHAR		','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING     ".name"
# define COMMENT_CMD_STRING ".comment"

#define T_REG                    1
#define T_DIR                    2
#define T_IND                    4

# define PROG_NAME_LENGTH        (128)
# define COMMENT_LENGTH            (2048)
# define COREWAR_EXEC_MAGIC        0xea83f3

typedef struct        header_s
{
	unsigned int        magic;
	char                prog_name[PROG_NAME_LENGTH + 1];
	unsigned int        prog_size;
	char                comment[COMMENT_LENGTH + 1];
}                    header_t;

typedef struct		s_op
{
	char	*str;
	int		nb_arg;
	int		args[MAX_ARGS_NUMBER];
	int		opcode;
	int		cycle;
	char	*description;
	int		carry;
	int		octal;
}					t_op;

t_op	*get_ops(void);

#endif