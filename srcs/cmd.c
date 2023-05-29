/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:47:29 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 09:44:46 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void	cmd_op(t_list **tokens, t_executer *executer)
{
	t_list	*curr;

	check_dollar_expansion(tokens, executer);
	curr = *tokens;
	if (check_var_assignment(&curr, executer) == 0)
	{
		executer->cmd = cmd_matrix(curr);
		//if (!executer->cmd)
		//	printf("No hizo bien matriz\n");
		set_redirections(*tokens, executer);
		search_cmd(executer);
	}
	reset_dirs(executer);
	printf("Reseteó dirs\n");
}
