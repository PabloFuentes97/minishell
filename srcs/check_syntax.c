/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:12:49 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:25:57 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	valid_op_pos(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type >= OR && token->type <= PIPE)
		{
			if (!tokens->prev || !tokens->next)
			{
				printf("Syntax error near unexpected token `%s'\n",
					get_token(tokens)->str);
				return (0);
			}
			if (get_token(tokens->next)->type >= OR
				&& get_token(tokens->next)->type <= PIPE)
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

int	valid_par_pos(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == CMD
			|| (token->type >= HERE_DOC && token->type <= REDIR_OUTPUT_TRUNC)
			|| token->type == CLOSE_PAR)
		{
			if (tokens->next && get_token(tokens->next)->type == OPEN_PAR)
			{
				printf("Syntax error near unexpected token `('\n");
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

int	valid_assignment(t_list *tokens)
{
	while (tokens)
	{
		if (get_token(tokens)->type == ASSIGN)
		{
			if (!tokens->prev)
			{
				printf("Sintax error: invalid assignment\n");
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
