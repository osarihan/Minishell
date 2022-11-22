/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/01 15:23:58 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line(); // yeni satira gectigimizi belirtir
		rl_replace_line("", 0); // eger komut satirina yazilan karakterler varsa ve ctrl-C yapilirsa yazilan karakterleri siler.
		rl_redisplay();
	}
}

void	ctrl_D(char *line)
{
	printf("exit\n");
	free(shell->line);
	exit(1);
}

int	routine(char	**env)
{
	shell->line = readline(shell->name);
	shell->environ = env;
	if (!shell->line)
		ctrl_D(shell->line);
	get_name();
	add_history(shell->line);
	if (shell->line[0] == 0)
		return (0);
	return (1);
}

void	assigment()
{
	printf("|----------------|Minishell|-----------------|\n");
	shell = malloc(sizeof(t_shell));

	get_name();

	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

	shell->ctrl = 0;
	shell->len = 0;//for quote malloc
	//shell->temp = NULL;
}

int	main(int argc, char **argv, char **env)
{
	int i = 0;

	assigment();
	while (1)
	{
		if (!routine(env))
			continue;
		if (!quote_check(shell->line))
			continue;
		shell->str = ft_split_mod(shell->line, ' ');//D_QUOTE MOD
		if (shell->d_quote > 0 || shell->s_quote > 0)
			shell->line = pars_fquote();
		// else
		// 	shell->line = pars();
		if (pipe_counter())
		{
			pipe_status();
			continue;
		}
		else if (check_cmnd(i))
			continue;
		free(shell->line);
	}
	return(1);
}
