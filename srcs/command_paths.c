/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:03:09 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/28 11:05:49 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include "../libft/libft.h"

void	free_matrix(void **matrix)
{
	int	cont;

	cont = 0;
	if (matrix)
	{
		while (matrix[cont])
		{
			free(matrix[cont]);
			cont++;
		}
		free(matrix);
	}
	matrix = NULL;
}

char	**path_matrix(char **envp)
{
	int		cont;
	char	**path;

	cont = 0;
	while (envp[cont] && ft_strnstr(envp[cont], "PATH=",
			ft_strlen(envp[cont])) == 0)
		cont++;
	if (envp[cont] == NULL)
		exit(1);
	path = ft_split(ft_strnstr(envp[cont], "PATH=",
				ft_strlen(envp[cont])), ':');
	return (path);
}

char	*correct_path(char **paths, char *command)
{
	int		cont;
	char	*command_path;

	cont = 0;
	if (access(command, X_OK) == 0)
		return (command);
	while (paths[cont])
	{
		command_path = aux_join(aux_join(paths[cont], ft_strdup("/")), command);
		if (access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);
		cont++;
	}
	perror("command not found\n");
	return (NULL);
}
