/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:56:30 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/03/16 12:59:03 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	debug(t_tok *first)
{
	t_tok *token;

	token = first->next;
	while (token)
	{
		if (token->tok == TOK_NAME)
			ft_print("NAME");
		if (token->tok == TOK_COMMENT)
			ft_print("COMMENT");
		if (token->tok == TOK_STR)
			ft_print("STR");
		if (token->tok == TOK_LABEL)
			ft_print("LABEL");
		if (token->tok == TOK_OP)
			ft_print("OP (%s)", get_ops()[(*(int *)token->data) - 1].str);
		if (token->tok == TOK_INDIR_LB)
			ft_print("IND_LABEL");
		if (token->tok == TOK_DIR_LB)
			ft_print("DIR LABEL");
		if (token->tok == TOK_INDIR_NB)
			ft_print("IND LABEL");
		if (token->tok == TOK_DIR_NB)
			ft_print("DIR NB");
		if (token->tok == TOK_REG)
			ft_print("REG");
		if (token->tok == TOK_USELESS || token->tok == TOK_UNDEFINED)
			ft_print("MISTAKE");
		if (token->tok == TOK_INDIR_LB || token->tok == TOK_DIR_LB || token->tok == TOK_LABEL || token->tok == TOK_STR)
			ft_print(" : %s", token->data);
		else if (token->tok == TOK_OP || token->tok == TOK_INDIR_NB || token->tok == TOK_DIR_NB || token->tok == TOK_REG)
			ft_print(": %d", *(int *)token->data);
		else if (token->tok == TOK_NEWLINE)
			ft_print("\n");
		if (token->next && token->next->tok != TOK_NEWLINE && token->tok != TOK_NEWLINE)
			ft_print(", ");
		token = token->next;
	}
}
