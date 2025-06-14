/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:05:41 by hamzabillah       #+#    #+#             */
/*   Updated: 2025/06/15 15:17:54 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

t_token	*add_token(t_token **tokens,  char *value, int type)
{
    t_token	*new_token;
    t_token	*temp;

    if (!tokens || !value || !value[0])
        return (NULL);
    new_token = create_new_token(value, type);
    if (!new_token)
        return (NULL);
    if (!*tokens)
        *tokens = new_token;
    else
    {
        temp = *tokens;
        while (temp->next)
            temp = temp->next;
        temp->next = new_token;
        new_token->prev = temp;
    }
    return (new_token);
}

int	flush_buffer(char *buffer, size_t *index, t_token **tokens)
{
    t_token *res;

    if (*index > 0)
    {
        buffer[*index] = '\0';
        res = add_token(tokens, buffer, TOKEN_WORD);
        if (!res)
            return (0);
        *index = 0;
    }
    return (1);
}

int	handle_double_operator(const char *input, int *i, char *buf, size_t *j,
		int type)
{
	append_char(buf, j, input[*i]);
	append_char(buf, j, input[*i + 1]);
	*i += 2;
	return (type);
}

int	handle_single_operator(const char *input, int *i, char *buf, size_t *j,
		int type)
{
	char	op[2];

	op[0] = input[*i];
	op[1] = '\0';
	append_char(buf, j, input[*i]);
	(*i)++;
	flush_buffer(buf, j, NULL);
	add_token(NULL, op, type);
	return (type);
}
