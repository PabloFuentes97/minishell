/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:39:42 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/21 13:02:00 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static void	reset_pipes(t_mshell *mshell)
{
	if (mshell->data.op_lst)
	{
		if (get_dir(mshell->data.op_lst)->input == PIPE_READ)
			close(mshell->data.prev_pipe);
		if (get_dir(mshell->data.op_lst)->output == PIPE_WRITE
			&& !mshell->data.output_file)
			mshell->data.prev_pipe = mshell->data.pipes[0];
		if (get_dir(mshell->data.op_lst)->type == PIPE)
			close_pipes(mshell, 0);
		lst_delete_node(&mshell->data.op_lst, &free);
		if (!mshell->data.op_lst || get_dir(mshell->data.op_lst)->type != PIPE)
			waitpid_pids(mshell);
	}
	else if (!mshell->data.op_lst && mshell->data.prev_pipe != -1)
		close(mshell->data.prev_pipe);
}

static void	reset_dirs(t_mshell *mshell)
{
	if (mshell->data.input_file)
	{
		close(mshell->data.input);
		if (mshell->data.here_docs >= 0)
		{
			unlink(mshell->data.input_file);
			free(mshell->data.input_file);
		}
		mshell->data.input_file = NULL;
	}
	if (mshell->data.output_file)
	{
		close(mshell->data.output);
		mshell->data.output_file = NULL;
	}
}

void	after_execute_cmd(t_mshell *mshell)
{
	reset_pipes(mshell);
	reset_dirs(mshell);
}
