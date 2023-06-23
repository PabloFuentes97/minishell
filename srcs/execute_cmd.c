/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:13:22 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 15:51:16 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	search_cmd(t_mshell *mshell, t_list *tokens)
{
	char	**cmd;

	cmd = cmd_matrix(tokens);
	if (matrix_len(cmd) > 0)
	{
		if (ft_strncmp(cmd[0], "cd", longer_str(cmd[0], "cd")) == 0)
			cd(cmd, mshell);
		else if (ft_strncmp(cmd[0], "echo", longer_str(cmd[0], "echo")) == 0)
			echo(cmd, mshell);
		else if (ft_strncmp(cmd[0], "exit", longer_str(cmd[0], "exit")) == 0)
			b_exit(cmd, mshell);
		else if (ft_strncmp(cmd[0], "env", longer_str(cmd[0], "env")) == 0)
			env(cmd, mshell);
		else if (ft_strncmp(cmd[0], "export",
				longer_str(cmd[0], "export")) == 0)
			export(cmd, mshell);
		else if (ft_strncmp(cmd[0], "pwd", longer_str(cmd[0], "pwd")) == 0)
			pwd(cmd, mshell);
		else if (ft_strncmp(cmd[0], "unset", longer_str(cmd[0], "unset")) == 0)
			unset(cmd, &mshell->data.env_lst, mshell);
		else
			execute_cmd(cmd, mshell);
	}
	free(cmd);
	cmd = NULL;
}

void	child_execute(char **arg, t_mshell *mshell)
{
	char	*command_path;

	command_path = correct_path(mshell->data.paths, arg[0]);
	if (!command_path)
		exit(EXIT_FAILURE);
	if (mshell->data.input_file
		|| (mshell->data.op_lst
			&& get_dir(mshell->data.op_lst)->input == PIPE_READ))
	{
		dup2(mshell->data.input, STDIN_FILENO);
		close(mshell->data.prev_pipe);
	}
	dup2(mshell->data.output, STDOUT_FILENO);
	if (mshell->data.op_lst && get_dir(mshell->data.op_lst)->type == PIPE)
		close_pipes(mshell, 1);
	signals_child();
	if (execve(command_path, arg, env_lst_to_matrix(mshell->data.env_lst)) < 0)
	{
		free(command_path);
		exit(EXIT_FAILURE);
	}
}

void	execute_cmd(char **arg, t_mshell *mshell)
{
	int		pid;
	int		wstatus;

	pid = fork();
	if (pid == 0)
		child_execute(arg, mshell);
	else
		parent_wait_cmd(mshell, pid, wstatus);
}
