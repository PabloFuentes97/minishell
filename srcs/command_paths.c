/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/22 11:14:55 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

char	**path_matrix(char **envp)
{
	int		cont;
	char	**path;

	cont = 0;
	while (envp[cont] && ft_strnstr(envp[cont], "PATH=",
			ft_strlen(envp[cont])) == 0)
		cont++;
	if (envp[cont] == NULL)
	{
		ft_putstr_fd("PATH not found\n", 2);
		return (NULL);
	}
	path = ft_split(ft_strnstr(envp[cont], "PATH=",
				ft_strlen(envp[cont])), ':');
	return (path);
}

char	*correct_path(char **paths, char *command)
{
	int		cont;
	char	*command_path;
	char	*bar;
	char	*path;

	cont = 0;
	if (access(command, X_OK) == 0)
		return (command);
	bar = ft_strdup("/");
	while (paths[cont])
	{
		path = ft_strjoin(paths[cont], bar);
		command_path = aux_join(path, command);
		if (access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);
		cont++;
	}
	free(bar);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}
