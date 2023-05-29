/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:11:20 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:42:08 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cmd_args_num(t_list *cmd)
{
	int		num;
	t_token	*token;

	num = 0;
	while (cmd)
	{
		token = get_token(cmd);
		if (token->type == CMD || token->type == ASSIGN)
			num++;
		else if (token->type > 3 && token->type < 8)
			cmd = cmd->next;
		cmd = cmd->next;
	}
	return (num);
}

char	**cmd_matrix(t_list *tokens)
{
	char	**matrix;
	int		cont;
	t_token	*token;
	int		len;

	len = cmd_args_num(tokens);
	printf("Longitud de cmd matrix: %d\n", len);
	matrix = malloc(sizeof(char *) * len + 1);
	cont = 0;
	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == CMD || token->type == ASSIGN)
		{
			matrix[cont] = token->str;
			cont++;
		}
		else if (token->type > 3 && token->type < 8)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	matrix[cont] = NULL;
	return (matrix);
}
