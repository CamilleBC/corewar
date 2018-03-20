/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:12:21 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/20 15:28:05 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tok	*rm_tok(t_tok *token, t_tok *prev, t_tok *first, t_error *error)
{
	if (token->tok == TOK_NEWLINE && prev->tok != TOK_NEWLINE)
		error->line++;
	else if (prev)
	{
		prev->next = token->next;
		free(token);
		token = prev;
	}
	else
	{
		first->next = token->next;
		free(token);
		token = first->next;
	}
	return (token);
}

t_tok	*find_next_line(t_tok *token)
{
	t_tok	*prev;

	prev = token;
	token = token->next;
	while (token && token->tok != TOK_NEWLINE)
	{
		if (token->tok != TOK_USELESS)
			return (NULL);
		token = rm_tok(token, prev, token, NULL);
		token = token->next;
	}
	return (token);
}

int		check_arg(t_tok *token, t_tok *first, int args)
{
	if (token->tok == TOK_INDIR_LB || token->tok == TOK_DIR_LB)
		if (!find_label(token->data, first))
			return (0);
	if (token->tok == TOK_REG)
		if (*(int *)token->data < 0)
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
		if (token->tok == TOK_REG)
			return (1);
	return (0);
}

t_tok	*check_args(t_tok *token, t_tok *first)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(int *)token->data != get_ops()[i].opcode)
		i++;
	while ((size_t)j < get_ops()[i].nb_args)
	{
		token = token->next;
		if (!check_arg(token, first, get_ops()[i].args[j++]))
			return (NULL);
	}
	return (find_next_line(token));
}

int		verify_list(t_tok *first, t_error *error)
{
	t_tok	*prev;
	t_tok	*token;

	error->line = 1;
	prev = NULL;
	token = first->next;
	while (token)
	{
		if (token->tok == TOK_NAME || token->tok == TOK_COMMENT)
		{
			if (!(token = check_strline(token)))
				return (0);
		}
		else if (token->tok == TOK_OP)
		{
			if (!(token = check_args(token, first)) || !check_strline(token))
				return (0);
		}
		else if (token->tok == TOK_USELESS || token->tok == TOK_NEWLINE ||
				(token->tok == TOK_NEWLINE && prev->tok == TOK_NEWLINE))
			token = rm_tok(token, prev, first, error);
		prev = token;
		token = token->next;
	}
	return (1);
}
