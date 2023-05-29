/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:28:29 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:28:33 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	var_assignment(t_list *tokens, t_executer *executer)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == ASSIGN)
		{
			if (ft_isdigit(get_token(tokens->prev)->str[0]) == 0)
			{
				ft_lstadd_back(&executer->env->env_lst,
					ft_lstnew(set_key_value(ft_strdup(get_token
								(tokens->prev)->str), ft_strdup(get_token
								(tokens->next)->str), 1)));
			}
			tokens = tokens->next->next;
		}	
		else
			tokens = tokens->next;
	}
	executer->last_return = 0;
}

int	check_var_assignment(t_list **tokens, t_executer *executer)
{
	t_token	*token;
	t_list	*curr;
	t_list	*cmd;

	curr = *tokens;
	cmd = curr;
	if (curr->next && (get_token(curr->next)->type != ASSIGN))
		return (0);
	printf("Recorrer lista para asignar\n");
	while (curr)
	{
		token = get_token(curr);
		if (token->type == ASSIGN)
		{
			if (!curr->next->next)
			{
				var_assignment(*tokens, executer);
				printf("Llegó al final, no hay comando\n");
				return (1);
			}
			cmd = curr->next->next;
		}
		curr = curr->next;
	}
	*tokens = cmd;
	printf("No asigna variables\n");
	return (0);
}
