/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:12:49 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:27:13 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	valid_num_par(t_list *tokens)
{
	int		open;
	int		close;
	t_token	*token;

	open = 0;
	close = 0;
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == OPEN_PAR)
			open++;
		else if (token->type == CLOSE_PAR)
			close++;
		tokens = tokens->next;
	}
	if (open == close)
		return (1);
	printf("Syntax error: invalid number of parenthesis\n");
	return (0);
}

int	valid_num_quotes(t_list *tokens)
{
	int		quotes;
	int		type;

	quotes = 0;
	while (tokens)
	{
		if (get_token(tokens)->type == D_QUOTE
			|| get_token(tokens)->type == QUOTE)
		{
			quotes++;
			type = get_token(tokens)->type;
			tokens = tokens->next;
			while (tokens && get_token(tokens)->type != type)
				tokens = tokens->next;
			if (tokens)
				quotes++;
			else
				break ;
		}
			tokens = tokens->next;
	}
	if (quotes % 2 == 0)
		return (1);
	printf("Syntax error: invalid number of quotes\n");
	return (0);
}

int	valid_redirections(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type >= HERE_DOC
			&& token->type <= REDIR_OUTPUT_TRUNC)
		{
			if (!tokens->next)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (0);
			}	
			if (get_token(tokens->next)->type >= HERE_DOC
				&& get_token(tokens->next)->type <= REDIR_OUTPUT_TRUNC)
			{
				printf("Syntax error near unexpected token `%s'\n",
					get_token(tokens->next)->str);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
