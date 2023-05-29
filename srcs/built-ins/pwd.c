/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 09:15:50 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 11:29:14 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

void	pwd(t_executer *executer)
{
	char	*pwd_str;

	pwd_str = NULL;
	pwd_str = getcwd(pwd_str, 10000000);
	if (pwd_str)
	{
		ft_putstr_fd(pwd_str, executer->dirs->output);
		write(executer->dirs->output, "\n", 1);
		executer->last_return = 0;
	}
	else
		executer->last_return = 1;
	free(pwd_str);
}
