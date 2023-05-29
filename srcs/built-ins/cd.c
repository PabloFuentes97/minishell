/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:30:24 by pfuentes          #+#    #+#             */
/*   Updated: 2023/05/28 08:54:22 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

char	*ft_strjoin_variadic(int n, ...)
{
	va_list	lst;
	int		cont;
	char	*joined;
	char	*to_join;

	va_start(lst, n);
	cont = 0;
	joined = va_arg(lst, char *);
	while (cont < n)
	{
		to_join = va_arg(lst, char *);
		joined = aux_join(joined, to_join);
		free(to_join);
		cont++;
	}
	va_end(lst);
	return (joined);
}

static int	rev_str_pos(char *str, char c)
{
	int	pos;

	pos = ft_strlen(str);
	while (pos > 0)
	{
		if (str[pos] == c)
			return (pos);
		pos--;
	}
	return (0);
}

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
	else
		type = 3;
	free(curr);
	return (type);
}

static char	*get_path_cd(char *cd, t_executer *executer)
{
	char	*org;
	char	*to_move;
	char	*curr;
	int		type;

	type = path_type_cd(cd);
	printf("Tipo de cd: %d\n", type);
	curr = NULL;
	curr = getcwd(curr, PATH_MAX);
	if (type == 0)
		to_move = ft_strdup(get_env_value(executer->env.env_lst, "HOME"));
	else if (type == 1)
		to_move = ft_strdup(cd);
	else if (type == 2)
		to_move = ft_substr(curr, 0, rev_str_pos(curr, '/'));
	else if (type == 3)
	{
		org = ft_strdup(cd);
		to_move = ft_strjoin_variadic(2, curr, ft_strdup("/"), org);
	}
	if (type < 3)
		free(curr);
	return (to_move);
}

static int	move_path_cd(char *path, char *arg, t_executer *executer)
{
	if (chdir(path) == 0)
	{
		set_env_value(&executer->env.env_lst, "OLDPWD",
			ft_strdup(get_env_value(executer->env.env_lst, "PWD")));
		set_env_value(&executer->env.env_lst, "PWD", ft_strdup(path));
		executer->last_return = 0;
		return (1);
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		if (arg)
			ft_putstr_fd(arg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		executer->last_return = 1;
		errno = 1;
		return (0);
	}
}

void	cd(char **cmd, t_executer *executer)
{
	char	*path;
	int		i;
	int		success;

	i = 1;
	while (i == 1 || cmd[i])
	{
		path = get_path_cd(cmd[i], executer);
		success = move_path_cd(path, cmd[i], executer);
		free(path);
		if (success == 0 || !cmd[1])
			return ;
		i++;
	}
}
