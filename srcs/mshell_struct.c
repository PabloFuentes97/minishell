/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:51:35 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/09 13:13:57 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

void	set_data(t_data *data, char **env)
{
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
	data->input = data->stdin;
	data->output = data->stdout;
	data->paths = path_matrix(env);
	data->tokens_dict = create_tokens_dict();
	data->env_matrix = env;
	data->env_lst = set_env_list(env);
	data->here_docs = 0;
	data->here_doc_success = 1;
	data->input_file = NULL;
	data->output_file = NULL;
	data->here_doc = NULL;
	data->prev_pipe = -1;
	data->op_lst = NULL;
	data->pids_lst = NULL;
	data->last_cmd = 0;
	data->last_err = 0;
}

void	reset_data(t_data *data)
{
	data->input = data->stdin;
	dup2(data->stdin, STDIN_FILENO);
	data->output = data->stdout;
	dup2(data->stdout, STDOUT_FILENO);
	data->here_docs = 0;
	data->here_doc_success = 1;
	data->last_cmd = 0;
	data->here_doc = NULL;
	data->input_file = NULL;
	data->output_file = NULL;
	ft_lstclear(&data->op_lst, &free);
	data->op_lst = NULL;
	ft_lstclear(&data->pids_lst, &free);
	data->pids_lst = NULL;
	data->prev_pipe = -1;
}

void	set_mshell(t_mshell *mshell, char **env)
{
	set_data(&mshell->data, env);
	mshell->line = NULL;
	mshell->tokens = NULL;
	mshell->parse_tree = NULL;
}

void	reset_mshell(t_mshell *mshell)
{
	reset_data(&mshell->data);
	free(mshell->line);
	mshell->line = NULL;
	mshell->tokens = NULL;
	free_parser_tree(&mshell->parse_tree);
	mshell->parse_tree = NULL;
}
