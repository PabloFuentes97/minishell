/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:49:47 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:16:30 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	execute_parser_tree(t_btree *root, t_mshell *mshell)
{
	t_list	*tokens;
	t_token	*token;

	if (root)
	{
		tokens = root->content;
		token = tokens->content;
		if (token->type == PIPE)
			pipe_op(root, mshell);
		else if (token->type == AND)
			and_op(root, mshell);
		else if (token->type == OR)
			or_op(root, mshell);
		else
			cmd_op(&tokens, mshell);
		root->content = (void *)tokens;
	}
}

void	free_parser_tree(t_btree **root)
{
	t_list	*tokens;

	if (!root || !*root)
		return ;
	if ((*root)->left)
		free_parser_tree(&(*root)->left);
	if ((*root)->right)
		free_parser_tree(&(*root)->right);
	tokens = (t_list *)(*root)->content;
	if (tokens)
		ft_lstclear(&tokens, &free_token);
	free(*root);
	*root = NULL;
	root = NULL;
}
