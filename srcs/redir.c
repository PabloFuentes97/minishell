/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:02 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/20 12:48:14 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	*get_file_name(t_list *tokens)
{
	t_token	*token;

	token = get_token(tokens);
	if (token->type == QUOTE || token->type == D_QUOTE)
		return (get_token(tokens->next)->str);
	return (token->str);
}

void	and_or_redir(t_mshell *mshell, t_dir *dir)
{
	mshell->data.input = dir->input;
	mshell->data.output = dir->output;
}

int	set_redirections(t_list *tokens, t_mshell *mshell)
{
	t_dir	*dir;

	if (mshell->data.op_lst)
	{
		dir = get_dir(mshell->data.op_lst);
		if (dir->type == PIPE)
			new_pipes(mshell);
		else if (dir->type == AND)
			and_or_redir(mshell, dir);
	}
	if (get_cmd_input(tokens, mshell) == 0)
		return (0);
	if (!mshell->data.input_file
		&& (mshell->data.op_lst
			&& get_dir(mshell->data.op_lst)->input == PIPE_READ))
		mshell->data.input = mshell->data.prev_pipe;
	mshell->data.output_file = get_cmd_output(tokens, mshell);
	return (1);
}
