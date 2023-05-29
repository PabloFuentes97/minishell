#include "../includes/minishell.h" 
#include "../libft/libft.h"

void	signal_handler_child(int signal)
{
	printf("Valor numérico de señal: %d\n", signal);
	if (signal == SIGINT)
	{
		printf("Interceptó SIGINT o CTRL + C\n");
		exit(1);
	}
	else if (signal == SIGTSTP)
	{
		printf("Interceptó SIGSTP o CTRL + Z\n");
		exit(1);
	}
	else if (signal == SIGQUIT)
	{
		printf("Interceptó SIGQUIT o CTRL + BARRA \n");
		exit(1);
	}
}

void	ctrl_c_signal(void)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_4_signal_parent(void)
{
	return ;
}

void	ctrl_4_signal_child(void)
{
	printf("Quit: 3\n");
	b_exit(errno);
}

void	signal_handler_parent(int signal)
{
	printf("Valor numérico de señal: %d\n", signal);
	if (signal == SIGINT)
	{
		printf("Interceptó SIGINT o CTRL + C\n");
		ctrl_c_signal();
	}
}

void	signals_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler_parent;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	signals_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler_child;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
