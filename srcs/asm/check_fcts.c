/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:12:21 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/04/11 16:46:14 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tok	*check_strline(t_tok *token, t_error *error)
{
	static int	header;
	int			count;

	if (token->tok != TOK_NAME && token->tok != TOK_COMMENT)
		return ((header != 3 ? NULL : token));
	count = 0;
	while (token->next->data && ((char *)(token->next->data))[count])
		if (((char *)(token->next->data))[count++] == '\n')
			error->line++;
	if (token->tok == TOK_NAME)
	{
		if (ft_strlen(token->next->data) > PROG_NAME_LENGTH ||
				!(token = find_next_line(token->next, error)))
			return (NULL);
		header += 2;
	}
	if (token->tok == TOK_COMMENT)
	{
		if (ft_strlen(token->next->data) > COMMENT_LENGTH ||
				!(token = find_next_line(token->next, error)))
			return (NULL);
		header += 1;
	}
	return (token);
}

int		find_label(char *label, t_tok *first)
{
	t_tok *token;

	token = first->next;
	while (token)
	{
		if (token->tok == TOK_LABEL && !ft_strcmp(token->data, label))
			return (1);
		token = token->next;
	}
	return (0);
}

int		is_label(char *line)
{
	int	count;

	count = 0;
	while (line[count] && line[count] != LABEL_CHAR)
		if (!ft_strchr(LABEL_CHARS, line[count++]))
			return (0);
	if (!line[count])
		return (0);
	return (1);
}

int		is_op(char *line)
{
	int	count;

	count = OP_COUNT - 2;
	while (count >= 0)
	{
		if (!ft_strncmp(get_ops()[count].str, line,
				ft_strlen(get_ops()[count].str)))
			return (count + 1);
		count--;
	}
	return (0);
}
