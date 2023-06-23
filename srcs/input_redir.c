/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:02 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/21 13:07:11 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static char	*get_here_doc_file(char	**here_doc, t_mshell *mshell)
{
	if (here_doc)
	{
		unlink(*here_doc);
		free(*here_doc);
	}
	if (mshell->data.here_doc)
		*here_doc = ft_strdup((char *)mshell->data.here_doc->content);
	mshell->data.here_docs--;
	lst_delete_node(&mshell->data.here_doc, &free);
	return (*here_doc);
}

static int	cmd_input_cases(t_list *tokens, char **input,
							char **here_doc, t_mshell *mshell)
{
	t_token	*token;

	token = tokens->content;
	if (input)
		close(mshell->data.input);
	if (token->type == REDIR_INPUT)
		*input = get_file_name(tokens->next);
	else if (token->type == HERE_DOC)
	{
		*here_doc = get_here_doc_file(here_doc, mshell);
		*input = *here_doc;
	}
	mshell->data.input = ft_open(*input, 0);
	if (mshell->data.input < 0)
		return (0);
	mshell->data.input_file = *input;
	return (1);
}

int	get_cmd_input(t_list *tokens, t_mshell *mshell)
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
			if (cmd_input_cases(tokens, &input_file,
					&here_doc_file, mshell) == 0)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
