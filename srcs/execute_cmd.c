/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:13:22 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 11:21:29 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_return(t_executer *executer, int status)
{
	int	statuscode;

	printf("Entro en cmd return\n");
	if (WIFEXITED(status))
	{
		statuscode = WEXITSTATUS(status);
		printf("Código de salida: %d\n", statuscode);
		if (statuscode != 0)
		{
			errno = statuscode;
			printf("Ejecutó con algún error\n");
		}
		executer->last_return = statuscode;
	}
}

void	reset_dirs(t_executer *executer)
{
	executer->dirs->input = executer->dirs->stdin;
	executer->dirs->output = executer->dirs->stdout;
	dup2(executer->dirs->stdin, STDIN_FILENO);
	dup2(executer->dirs->stdout, STDOUT_FILENO);
	if (executer->ops->op_lst)
	{
		printf("Estoy en lista de operaciones\n");
		if (get_dir(executer->ops->op_lst)->type == PIPE)
		{
			printf("Estoy en una pipe, cerrarla\n");
			close_pipe(executer);
		}
		if (get_dir(executer->ops->op_lst)->type == PIPE
			&& ((executer->ops->op_lst->next
					&& get_dir(executer->ops->op_lst->next)->type != PIPE)
				|| !executer->ops->op_lst->next))
			waitpid_pids(executer);
		
		remove_head(&executer->ops->op_lst);
	}
	if (executer->dirs->input_file)
	{
		close(executer->dirs->input);
		if (executer->dirs->here_doc_num > 0)
		{
			unlink(executer->dirs->input_file);
			free(executer->dirs->input_file);
			executer->dirs->here_doc_num--;
		}
		executer->dirs->input_file = NULL;
	}
	if (executer->dirs->output_file)
	{
		close(executer->dirs->output);
		executer->dirs->output_file = NULL;
	}
	executer->dirs->input = executer->dirs->stdin;
	executer->dirs->output = executer->dirs->stdout;
}

void	print_str_matrix(char **matrix)
{
	int	i;

	i = 0;
	printf("Imprimir matriz\n");
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void	search_cmd(t_executer *executer)
{
	char	**cmd;

	cmd = executer->cmd;
	printf("En search_cmd\n");
	print_str_matrix(cmd);
	if (ft_strncmp(cmd[0], "cd", longer_str(cmd[0], "cd")) == 0)
		cd(cmd, executer);
	else if (ft_strncmp(cmd[0], "echo", longer_str(cmd[0], "echo")) == 0)
		echo(cmd, executer);
	else if (ft_strncmp(cmd[0], "exit", longer_str(cmd[0], "exit")) == 0)
		b_exit(errno);
	else if (ft_strncmp(cmd[0], "export", longer_str(cmd[0], "export")) == 0)
		export(cmd, executer);
	else if (ft_strncmp(cmd[0], "pwd", longer_str(cmd[0], "pwd")) == 0)
		pwd(executer);
	else if (ft_strncmp(cmd[0], "unset", longer_str(cmd[0], "unset")) == 0)
		unset(cmd, executer);
	else
		execute_cmd(cmd, executer);
	free(cmd);
	executer->cmd = NULL;
}

void	parent_wait_cmd(t_executer *executer, int pid)
{
	int		wstatus;

	if (get_dir(executer->ops->op_lst)->type == PIPE)
		ft_lstadd_back(&executer->ops->pids_lst, ft_lstnew(int_ptr(pid)));
	else
	{
		waitpid(pid, &wstatus, 0);
		cmd_return(executer, wstatus);
	}
}

void	child_execute(char **arg, t_executer *executer)
{
	char	*cmd_path;

	cmd_path = correct_path(executer->paths, arg[0]);
	if (!cmd_path)
		exit(EXIT_FAILURE);
	printf("Fd de output: %d\n", executer->dirs->output);
	system("lsof -c minishell");
	if (dup2(executer->dirs->output, STDOUT_FILENO) < 0)
		printf("Error de dup2 al redirigir output\n");
	if (get_dir(executer->ops->op_lst)->type == PIPE)
	{
		perror("En el hijo, op_lst tiene pipe\n");
		close_pipe(executer);
	}
	if (execve(cmd_path, arg, NULL) < 0)
	{
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}

void	execute_cmd(char **arg, t_executer *executer)
{
	int		pid;

	printf("Fd de input: %d\n", executer->dirs->input);
	if (dup2(executer->dirs->input, STDIN_FILENO) < 0)
		printf("Error de dup2 al redirigir input\n");
	pid = fork();
	if (pid == 0)
		child_execute(arg, executer);
	else
		parent_wait_cmd(executer, pid);
}
