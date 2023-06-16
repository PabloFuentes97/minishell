/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:17:08 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/12 09:36:34 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 
#include "../../libft/libft.h"

static int	flag_type(char **cmd)
{
	int	type;

	type = 0;
	if (!cmd[1])
		return (-1);
	if (ft_strncmp(cmd[1], "-n", longer_str(cmd[1], "-n")) == 0)
		type = 1;
	return (type);
}

void	echo(char **cmd, t_mshell *mshell)
{
	int	cont;
	int	type;

	cont = 1;
	while (cmd[cont])
	{
		if (ft_strncmp(cmd[cont], "-", 1) == 0)
			cont++;
		else
		{
			ft_putstr_fd(cmd[cont], mshell->data.output);
			if (cmd[cont + 1])
				ft_putstr_fd(" ", mshell->data.output);
			cont++;
		}
	}
	type = flag_type(cmd);
	if (type == 0)
		ft_putstr_fd("\n", mshell->data.output);
	mshell->data.last_cmd = 0;
}
