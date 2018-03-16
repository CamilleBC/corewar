/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:12:21 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/16 12:57:57 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tok	*check_name_comment(t_tok *token)
{
	static int	header;

	if (token->tok != TOK_NAME && token->tok != TOK_COMMENT)
		return ((header != 3 ? NULL : token));
	if (token->tok == TOK_NAME)
	{
		if (ft_strlen(token->next->data) > PROG_NAME_LENGTH ||
				!(token = find_next_line(token->next)))
			return (NULL);
		header += 2;
	}
	if (token->tok == TOK_COMMENT)
	{
		if (ft_strlen(token->next->data) > COMMENT_LENGTH ||
				!(token = find_next_line(token->next)))
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
	while (line[count] && !ft_isspace(line[count]))
		count++;
	if (line[count - 1] == LABEL_CHAR)
		return (1);
	return (0);
}

int		is_op(char *line)
{
	int	count;

	count = 0;
	while (get_ops()[count].str != NULL)
	{
		if (!ft_strncmp(get_ops()[count].str, line,
			ft_strlen(get_ops()[count].str)) &&
			ft_isspace(line[ft_strlen(get_ops()[count].str)]))
			return (count + 1);
		count++;
	}
	return (0);
}
