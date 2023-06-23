/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:28:29 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 12:49:15 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static void	var_assign_cases(t_list *tokens, t_mshell *mshell)
{
	t_token	*token;
	t_list	*node;

	token = get_token(tokens->prev);
	node = get_node_by_key(mshell->data.env_lst, token->str);
	if (node)
	{
		set_env_value(&node,
			token->str, ft_strdup(get_token(tokens->next)->str));
	}
	else
	{
		ft_lstadd_back(&mshell->data.env_lst,
			ft_lstnew(set_key_value(ft_strdup(get_token
						(tokens->prev)->str), ft_strdup(get_token
						(tokens->next)->str), 1)));
	}
}

void	var_assignment(t_list *tokens, t_mshell *mshell)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == ASSIGN)
		{
			if (ft_isdigit(get_token(tokens->prev)->str[0]) == 0)
				var_assign_cases(tokens, mshell);
			else
			{
				ft_putstr_fd(get_token(tokens->prev)->str, 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
			}
			tokens = tokens->next->next;
		}	
		else
			tokens = tokens->next;
	}
	mshell->data.last_cmd = 0;
}

int	check_var_assignment(t_list **tokens, t_mshell *mshell)
{
	t_list	*curr;
	t_list	*cmd;

	curr = *tokens;
	cmd = curr;
	if (curr->next && (get_token(curr->next)->type != ASSIGN))
		return (0);
	while (curr)
	{
		if (get_token(curr)->type == ASSIGN)
		{
			if (!curr->next->next)
			{
				var_assignment(*tokens, mshell);
				mshell->data.last_cmd = 0;
				return (1);
			}
			cmd = curr->next->next;
		}
		curr = curr->next;
	}
	*tokens = cmd;
	return (0);
}
