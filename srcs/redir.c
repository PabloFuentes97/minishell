/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:02 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:10:19 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	*get_cmd_input(t_list *tokens, t_mshell *mshell)
{
	t_token	*token;
	char	*input_file;
	char	*here_doc_file;

	input_file = NULL;
	here_doc_file = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == REDIR_INPUT || token->type == HERE_DOC)
		{
			if (input_file)
				close(mshell->data.input);
			if (token->type == REDIR_INPUT)
				input_file = ((t_token *)(tokens->next->content))->str;
			else if (token->type == HERE_DOC)
			{
				here_doc_file = get_here_doc_file(here_doc_file, mshell);
				input_file = here_doc_file;
			}
			mshell->data.input = open(input_file, O_RDONLY, 0666);
		}
		tokens = tokens->next;
	}
	return (input_file);
}

void	set_output(char *output, int type, t_mshell *mshell)
{
	if (output)
	{
		if (type == 0)
			mshell->data.output = open(output,
					O_CREAT | O_TRUNC | O_WRONLY, 0666);
		else if (type == 1)
			mshell->data.output = open(output,
					O_CREAT | O_APPEND | O_WRONLY, 0666);
	}
}

char	*get_cmd_output(t_list *tokens, t_mshell *mshell)
{
	t_token	*token;
	char	*output;
	int		out_type;

	output = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == REDIR_OUTPUT_TRUNC
			|| token->type == REDIR_OUTPUT_APPEND)
		{
			if (output)
				close(mshell->data.output);
			output = ((t_token *)(tokens->next->content))->str;
			if (token->type == REDIR_OUTPUT_TRUNC)
				out_type = 0;
			else
				out_type = 1;
			set_output(output, out_type, mshell);
		}
		tokens = tokens->next;
	}
	return (output);
}

void	and_or_redir(t_mshell *mshell, t_dir *dir)
{
	mshell->data.input = dir->input;
	mshell->data.output = dir->output;
}

void	set_redirections(t_list *tokens, t_mshell *mshell)
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
	mshell->data.input_file = get_cmd_input(tokens, mshell);
	if (!mshell->data.input_file
		&& (mshell->data.op_lst
			&& get_dir(mshell->data.op_lst)->input == PIPE_READ))
		mshell->data.input = mshell->data.prev_pipe;
	mshell->data.output_file = get_cmd_output(tokens, mshell);
}
