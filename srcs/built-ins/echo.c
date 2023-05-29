/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 08:58:55 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/29 11:28:55 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

void	echo(char **cmd, t_executer *executer)
{
	int		cont;
	int		new_line;

	printf("En echo\n");
	printf("Output: %d\n", executer->dirs->output);
	cont = 1;
	new_line = 0;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", longer_str(cmd[1], "-n")) == 0)
	{
		//printf("Es -n\n");
		cont = 2;
		new_line = 1;
	}
	while (cmd[cont])
	{
		ft_putstr_fd(cmd[cont], executer->dirs->output);
		if (cmd[cont + 1])
			ft_putstr_fd(" ", executer->dirs->output);
		cont++;
	}
	if (new_line == 0)
		ft_putstr_fd("\n", executer->dirs->output);
	else
		ft_putstr_fd("%%", executer->dirs->output);
	executer->last_return = 0;
	printf("Hizo echo\n");
}
