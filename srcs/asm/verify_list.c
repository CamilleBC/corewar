/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:12:21 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/15 11:13:33 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "op.h"

t_tok	*rm_tok(t_tok *token, t_tok *prev, t_tok **first)
{
	if (prev)
	{
		prev->next = token->next;
		free(token);
		token = prev;
	}
	else
	{
		first = &token->next;
		free(token);
		token = *first;
	}
	return (token);
}

t_tok	*find_next_line(t_tok *token)
{
	t_tok	*prev;

	prev = token;
	token = token->next;
	while (token->next && token->tok != TOK_NEWLINE)
	{
		if (token->tok != TOK_USELESS)
			return (NULL);
		token = rm_tok(token, prev, &token);
		token = token->next;
	}
	return (token);
}

t_tok	*check_name_comment(t_tok *token)
{
	static int	header;

	if (token->tok != TOK_NAME && token->tok != TOK_COMMENT)
		return ((header != 3 ? NULL : token));
	if (token->tok == TOK_NAME)
		if (ft_strlen(token->next->data) > PROG_NAME_LENGTH ||
				!(token = find_next_line(token->next)))
			return (NULL);
	if (token->tok == TOK_COMMENT)
		if (ft_strlen(token->next->data) > COMMENT_LENGTH ||
				!(token = find_next_line(token->next)))
			return (NULL);
	return (token);
}

int		find_label(char *label, t_tok **first)
{
	t_tok *token;

	token = *first;
	while (token != NULL)
	{
		if (token->tok == TOK_LABEL && !ft_strcmp(token->data, label))
			return (1);
		token = token->next;
	}
	return (0);
}

int		check_arg(t_tok *token, t_tok **first, int args)
{
	if (token->tok == TOK_INDIR_LB || token->tok == TOK_DIR_LB)
		if (!find_label(token->data, first))
			return (0);
	if (token->tok == TOK_REG)
		if (*(int *)token->data > REG_NUMBER)
			return (0);
	if (args >= T_IND)
	{
		if (token->tok == TOK_INDIR_NB || token->tok == TOK_INDIR_LB)
			return (1);
		args -= T_IND;
	}
	if (args >= T_DIR)
	{
		if (token->tok == TOK_DIR_NB || token->tok == TOK_DIR_LB)
			return (1);
		args -= T_DIR;
	}
	if (args >= T_REG)
	{
		if (token->tok == TOK_REG)
			return (1);
	}
	return (0);
}

t_tok	*check_args(t_tok *token, t_tok **first)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(int *)token->data != get_ops()[i].opcode)
		i++;
	while (j < get_ops()[i].nb_arg)
	{
		token = token->next;
		if (!check_arg(token, first, get_ops()[i].args[j++]))
			return (NULL);
	}
	return (find_next_line(token));
}

int		verify_list(t_tok **first)
{
	t_tok	*prev;
	t_tok	*token;

	prev = NULL;
	token = *first;
	while (token != NULL)
	{
		ft_putstr("QQQQQQQQQQQQQ\n");
		if (token->tok == TOK_NAME || token->tok == TOK_COMMENT)
			if (!(token = check_name_comment(token)))
				return (0);
		if (token->tok == TOK_OP)
			if (!(token = check_args(token, first)) ||
					!check_name_comment(token))
				return (0);
		if (token->tok == TOK_USELESS ||
				(token->tok == TOK_NEWLINE && prev->tok == TOK_NEWLINE))
			token = rm_tok(token, prev, first);
		prev = token;
		token = token->next;
	}
	ft_putstr("CACA\n");
	return (1);
}
