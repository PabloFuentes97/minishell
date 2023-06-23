/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lst_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:08:23 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 10:08:29 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static void	and_or_dir(t_mshell *mshell, int type)
{
	if (type == OR)
		ft_lstadd_back(&mshell->data.op_lst,
			ft_lstnew(new_dir(mshell->data.stdin,
					mshell->data.stdout, OR)));
	else if (type == AND)
		ft_lstadd_back(&mshell->data.op_lst,
			ft_lstnew(new_dir(mshell->data.stdin,
					mshell->data.stdout, AND)));
}

void	op_add_or_and(t_btree *root, t_mshell *mshell, int type)
{
	if (root->up && get_dir(root->up->content)->type != PIPE
		&& (get_token(root->left->content)->type <= CMD
			|| get_token(root->left->content)->type >= HERE_DOC))
		and_or_dir(mshell, type);
	else if (!root->up && (get_token(root->left->content)->type <= CMD
			|| get_token(root->left->content)->type >= HERE_DOC))
		and_or_dir(mshell, type);
	else
		op_lst(root->left, mshell);
	if (get_token(root->right->content)->type <= CMD
		|| get_token(root->right->content)->type >= HERE_DOC)
		and_or_dir(mshell, type);
	else
		op_lst(root->right, mshell);
}
