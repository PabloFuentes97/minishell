#include "includes/minishell.h" 

int	main(int argc, char **argv, char **env)
{
	t_mshell	*mshell;

	if (argc != 1 || !argv)
		return (1);
	mshell = malloc(sizeof(mshell));
	init_mshell(mshell, env);
	return (0);
}

