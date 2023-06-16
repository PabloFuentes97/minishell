/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/07 12:58:13 by pfuentes         ###   ########.fr       */
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
		perror("No encontró el PATH\n");
		exit(EXIT_FAILURE);
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
		command_path = ft_strjoin(path, command);
		free(path);
		if (access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);
		cont++;
	}
	perror(command);
	return (NULL);
}
