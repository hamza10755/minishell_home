/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzabillah <hamzabillah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:05:41 by hamzabillah       #+#    #+#             */
/*   Updated: 2025/06/15 01:05:41 by hamzabillah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_operator(const char *input, int *i, char *buffer, size_t *j,
        t_token **tokens)
{
    char	current;
    char	next;
    t_token	*res;
    t_token *prev;

    current = input[*i];
    next = input[*i + 1];

    if (!flush_buffer(buffer, j, tokens))
		return (0);

    if (tokens && *tokens) {
        prev = *tokens;
        while (prev->next)
            prev = prev->next;
        if (current == '|' && prev->type == TOKEN_PIPE) {
            ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
            return (0);
        }
        if ((current == '>' || current == '<') && 
            (prev->type == TOKEN_REDIR || prev->type == TOKEN_APPEND || prev->type == TOKEN_HEREDOC)) {
            ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
            if (current == '>' && next == '>')
                ft_putstr_fd(">>'\n", 2);
            else
                ft_putstr_fd(">'\n", 2);
            return (0);
        }
    }

    if (current == '|')
    {
        (*i)++;
        if (!tokens)
            return (TOKEN_PIPE);
        res = add_token(tokens, "|", TOKEN_PIPE);
        if (!res)
            return (0);
        return (TOKEN_PIPE);
    }
    else if (current == '<' && next == '<')
    {
        (*i) += 2;
        if (!tokens)
            return (TOKEN_HEREDOC);
        res = add_token(tokens, "<<", TOKEN_HEREDOC);
        if (!res)
            return (0);
        return (TOKEN_HEREDOC);
    }
    else if (current == '>' && next == '>')
    {
        (*i) += 2;
        if (!tokens)
            return (TOKEN_APPEND);
        res = add_token(tokens, ">>", TOKEN_APPEND);
        if (!res)
            return (0);
        return (TOKEN_APPEND);
    }
    else if (current == ';')
    {
        (*i)++;
        if (!tokens)
            return (TOKEN_SEMICOLON);
        res = add_token(tokens, ";", TOKEN_SEMICOLON);
        if (!res)
            return (0);
        return (TOKEN_SEMICOLON);
    }
    else if (current == '>' || current == '<')
    {
        char op[2];
        op[0] = current;
        op[1] = '\0';
        (*i)++;
        if (!tokens)
            return (TOKEN_REDIR);
        res = add_token(tokens, op, TOKEN_REDIR);
        if (!res)
            return (0);
        return (TOKEN_REDIR);
    }
    return (0);
}

int	process_quote_content(const char *input, int *i, char *buffer, size_t *j,
		char quote_char)
{
	(*i)++;
	append_char(buffer, j, quote_char);
	while (input[*i] && input[*i] != quote_char)
	{
		append_char(buffer, j, input[*i]);
		(*i)++;
	}
	if (input[*i] == quote_char)
	{
		append_char(buffer, j, quote_char);
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_quotes(const char *input, int *i, char *buffer, size_t *j)
{
	char	quote_char;
	int		start_pos;

	quote_char = input[*i];
	start_pos = *i;
	if (!process_quote_content(input, i, buffer, j, quote_char))
	{
		*i = start_pos;
		return (0);
	}
	return (1);
}

int	handle_whitespace(int *i, char *buffer, size_t *j, t_token **tokens,
        int *in_word)
{
    if (*in_word)
    {
        if (!flush_buffer(buffer, j, tokens))
            return (0);
        *in_word = 0;
    }
    (*i)++;
    return (1);
}

t_token	*handle_operator_in_word(char *buffer, size_t *j, t_token **tokens,
		int *in_word)
{
	if (*in_word)
	{
		flush_buffer(buffer, j, tokens);
		*in_word = 0;
	}
	return (*tokens);
}
