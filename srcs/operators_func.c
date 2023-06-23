/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:58:27 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/15 13:13:59 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	pipe_op(t_btree *root, t_mshell *mshell)
{
	execute_parser_tree(root->left, mshell);
	execute_parser_tree(root->right, mshell);
}

void	and_op(t_btree *root, t_mshell *mshell)
{
	execute_parser_tree(root->left, mshell);
	if (mshell->data.last_cmd == 0)
		execute_parser_tree(root->right, mshell);
}

void	or_op(t_btree *root, t_mshell *mshell)
{
	execute_parser_tree(root->left, mshell);
	if (mshell->data.last_cmd != 0)
		execute_parser_tree(root->right, mshell);
}

char	*here_doc_op(t_mshell *mshell)
{
	char	*name;
	int		fd;

	if (mshell->data.here_doc)
		name = ft_strdup((char *)mshell->data.here_doc->content);
	mshell->data.here_docs--;
	lst_delete_node(&mshell->data.here_doc, &free);
	return (name);
}
