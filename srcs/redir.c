/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:02 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:36:54 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	get_cmd_input(t_list *tokens, t_executer *executer)
{
	t_token	*token;

	while (tokens)
	{
		token = get_token(tokens);
		if (token->type == REDIR_INPUT)
		{
			if (executer->dirs->input_file)
				close(executer->dirs->input);
			executer->dirs->input_file = get_token(tokens->next)->str;
			executer->dirs->input
				= open(executer->dirs->input_file, O_RDONLY, 0666);
		}
		else if (token->type == HERE_DOC)
			here_doc_dir(executer->dirs);
		tokens = tokens->next;
	}
}

static void	set_output(int type, t_executer *executer)
{
	if (executer->dirs->output_file)
	{
		if (type == 0)
			executer->dirs->output = open(executer->dirs->output_file,
					O_CREAT | O_TRUNC | O_WRONLY, 0666);
		else if (type == 1)
			executer->dirs->output = open(executer->dirs->output_file,
					O_CREAT | O_APPEND | O_WRONLY, 0666);
	}
}

void	get_cmd_output(t_list *tokens, t_executer *executer)
{
	t_token	*token;
	char	*output;
	int		type;

	output = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == REDIR_OUTPUT_TRUNC
			|| token->type == REDIR_OUTPUT_APPEND)
		{
			if (executer->dirs->output_file)
				close(executer->dirs->output);
			executer->dirs->output_file = get_token(tokens->next)->str;
			if (token->type == REDIR_OUTPUT_TRUNC)
				type = 0;
			else
				type = 1;
			set_output(type, executer);
		}
		tokens = tokens->next;
	}
}

void	set_redirections(t_list *tokens, t_executer *executer)
{
	if (executer->ops->op_lst && get_dir(executer->ops->op_lst)->type == PIPE)
		new_pipe(executer);
	get_cmd_input(tokens, executer);
	get_cmd_output(tokens, executer);
}

