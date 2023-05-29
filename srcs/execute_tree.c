/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:11:24 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/28 10:19:14 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_parser_tree(t_btree *root, t_executer *executer)
{
	t_list	*tokens;
	t_token	*token;

	if (!root)
		return ;
	tokens = root->content;
	token = tokens->content;
	printf("Tipo de token: %d\n", token->type);
	if (token->type == OPEN_PAR)
		subshell(root, executer);
	else if (token->type == PIPE)
		pipe_op(root, executer);
	else if (token->type == AND)
		and_op(root, executer);
	else if (token->type == OR)
		or_op(root, executer);
	else
		cmd_op(&tokens, executer);
	root->content = (void *)tokens;
}

void	free_parser_tree(t_btree **root)
{
	t_list	*tokens;

	if (root)
	{
		if (*root)
		{
			if ((*root)->left)
				free_parser_tree(&(*root)->left);
			if ((*root)->right)
				free_parser_tree(&(*root)->right);
		}
		tokens = (t_list *)(*root)->content;
		if (tokens)
			ft_lstclear(&tokens, &free_token);
		free(*root);
		*root = NULL;
		root = NULL;
	}
}