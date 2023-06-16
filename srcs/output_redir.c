/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:15:02 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/15 13:59:25 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

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
			output = get_file_name(tokens->next);
			printf("Output es: %s\n", output);
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
