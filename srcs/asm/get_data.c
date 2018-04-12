/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgunzbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 11:00:49 by tgunzbur          #+#    #+#             */
/*   Updated: 2018/04/12 14:17:48 by tgunzbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tok		*push_token(t_tok *prev)
{
	t_tok	*new;

	if (prev == NULL)
	{
		if (!(prev = (t_tok *)malloc(sizeof(t_tok))))
			return (NULL);
		prev->tok = TOK_UNDEFINED;
		prev->data = NULL;
		prev->next = NULL;
		return (prev);
	}
	if (!(new = (t_tok *)malloc(sizeof(t_tok))))
		return (NULL);
	new->tok = TOK_UNDEFINED;
	new->data = NULL;
	new->next = NULL;
	prev->next = new;
	return (new);
}

t_tok_type	get_token(char *line)
{
	if (!ft_strncmp(NAME_CMD, line, ft_strlen(NAME_CMD)) &&
	(ft_isspace(line[ft_strlen(NAME_CMD)]) || line[ft_strlen(NAME_CMD)] == '"'))
		return (TOK_NAME);
	if (!ft_strncmp(COMMENT_CMD, line, ft_strlen(COMMENT_CMD))
		&& (ft_isspace(line[ft_strlen(COMMENT_CMD)])
		|| line[ft_strlen(COMMENT_CMD)] == '"'))
		return (TOK_COMMENT);
	if (!line[0] || line[0] == COMMENT_CHAR || ft_isspace(line[0]))
		return (TOK_USELESS);
	if (line[0] == DIRECT_CHAR &&
		(ft_isdigit(line[1]) || (line[1] == '-' && ft_isdigit(line[2]))))
		return (TOK_DIR_NB);
	if (line[0] == DIRECT_CHAR && line[1] == LABEL_CHAR)
		return (TOK_DIR_LB);
	if (ft_isdigit(line[0]) || (line[0] == '-' && ft_isdigit(line[1])))
		return (TOK_INDIR_NB);
	if (line[0] == LABEL_CHAR)
		return (TOK_INDIR_LB);
	if (line[0] == '"')
		return (TOK_STR);
	if (is_label(line))
		return (TOK_LABEL);
	if (line[0] == 'r' && ft_isdigit(line[1]))
		return (TOK_REG);
	return (is_op(line) ? TOK_OP : TOK_UNDEFINED);
}

int			*create_int(int i)
{
	int		*nb;

	if (!(nb = (int *)malloc(sizeof(int))))
		return (NULL);
	*nb = i;
	return (nb);
}

char		*first_word(char *line, char c, t_error *error)
{
	int		count;
	char	*str;

	count = 0;
	if ((ft_strchr(line, '"') && c == '"') || c == LABEL_CHAR)
	{
		while (line[count] && line[count] != c)
			count++;
		if (!(str = (char *)ft_memalloc(sizeof(char) * (count + 1))))
			return (NULL);
		if (!(str = ft_strncpy(str, line, count)))
			return (NULL);
		return (str);
	}
	if (c == '"')
		return (copy_str(line, error));
	while (line[count] && line[count] != SEP_CHAR &&
			!ft_isspace(line[count]) && line[count] != COMMENT_CHAR)
		count++;
	if (!(str = (char *)ft_memalloc(sizeof(char) * (count + 1))))
		return (NULL);
	if (!(str = ft_strncpy(str, line, count)))
		return (NULL);
	return (str);
}

int			get_data(char *line, t_tok_type tok, void **data, t_error *error)
{
	if (tok == TOK_DIR_NB || tok == TOK_REG)
		*data = create_int(ft_atoi(&line[1]));
	else if (tok == TOK_INDIR_NB)
		*data = create_int(ft_atoi(line));
	else if (tok == TOK_OP)
		*data = create_int(is_op(line));
	else if (tok == TOK_DIR_LB)
		*data = first_word(&line[2], SEP_CHAR, error);
	else if (tok == TOK_INDIR_LB)
		*data = first_word(&line[1], SEP_CHAR, error);
	else if (tok == TOK_LABEL)
		*data = first_word(line, LABEL_CHAR, error);
	else if (tok == TOK_STR)
		*data = first_word(&line[1], '"', error);
	else
		return (1);
	if (!(*data))
		return (0);
	return (1);
}
