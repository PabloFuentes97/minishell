/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lst_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:07:56 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 10:08:33 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static void	add_pipe(t_btree *root, t_mshell *mshell, int type)
{
	t_token	*down;
	t_dir	*pipe;

	if (type == 0)
		down = get_token(root->left->content);
	else
		down = get_token(root->right->content);
	if (down->type != PIPE)
	{
		pipe = new_dir(0, 1, PIPE);
		ft_lstadd_back(&mshell->data.op_lst, ft_lstnew(pipe));
	}
}

void	op_add_pipes(t_btree *root, t_mshell *mshell)
{
	add_pipe(root, mshell, 0);
	op_lst(root->left, mshell);
	add_pipe(root, mshell, 1);
	op_lst(root->right, mshell);
}
