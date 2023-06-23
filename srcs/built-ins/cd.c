/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:30:24 by pfuentes          #+#    #+#             */
/*   Updated: 2023/06/21 13:58:29 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

static int	path_type_cd(char *cd)
{
	char	*curr;
	int		type;

	curr = NULL;
	curr = getcwd(curr, PATH_MAX);
	if (!cd || chdir(curr) < 0)
		type = 0;
	else if (cd[0] == '/')
		type = 1;
	else if (ft_strncmp(cd, "..", longer_str(cd, "..")) == 0)
		type = 2;
	else if (ft_strncmp(cd, "-", longer_str(cd, "-")) == 0)
		type = 3;
	else
		type = 4;
	free(curr);
	return (type);
}

static char	*get_path_type4(char *cd, char *curr)
{
	char	*org;
	char	*to_move;

	org = ft_strdup(cd);
	to_move = aux_join(curr, "/");
	to_move = aux_join(to_move, org);
	free(org);
	return (to_move);
}

static char	*get_path_cd(char *cd, char *curr, t_mshell *mshell)
{
	char	*org;
	char	*to_move;
	int		type;

	type = path_type_cd(cd);
	if (type == 0)
	{
		if (get_env_value(mshell->data.env_lst, "HOME"))
			to_move = ft_strdup(get_env_value(mshell->data.env_lst, "HOME"));
	}
	else if (type == 1)
		to_move = ft_strdup(cd);
	else if (type == 2)
		to_move = ft_substr(curr, 0, rev_str_pos(curr, '/'));
	else if (type == 3)
	{
		if (get_env_value(mshell->data.env_lst, "OLDPWD"))
			to_move = ft_strdup(get_env_value(mshell->data.env_lst, "OLDPWD"));
	}
	else
		to_move = get_path_type4(cd, curr);
	if (type < 4)
		free(curr);
	return (to_move);
}

static int	move_path_cd(char *path, char *arg, t_mshell *mshell)
{
	char	*pwd;

	if (path && chdir(path) == 0)
	{
		pwd = get_env_value(mshell->data.env_lst, "PWD");
		if (pwd)
			set_env_value(&mshell->data.env_lst, "OLDPWD",
				ft_strdup(pwd));
		set_env_value(&mshell->data.env_lst, "PWD", ft_strdup(path));
		mshell->data.last_cmd = 0;
		return (1);
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		if (arg)
			ft_putstr_fd(arg, 2);
		write(2, "\n", 2);
		mshell->data.last_cmd = 1;
		mshell->data.last_err = 1;
		return (0);
	}
}

void	cd(char **cmd, t_mshell *mshell)
{
	char	*path;
	int		i;
	int		success;
	char	*curr;

	i = 1;
	while (i == 1 || cmd[i])
	{
		curr = NULL;
		curr = getcwd(curr, PATH_MAX);
		path = get_path_cd(cmd[i], curr, mshell);
		success = move_path_cd(path, cmd[i], mshell);
		free(path);
		if (success == 0 || !cmd[1])
			return ;
		i++;
	}
}
