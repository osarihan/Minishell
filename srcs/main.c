/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/30 14:42:31 by oozcan           ###   ########.fr       */
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
	free(line);
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	char *line;
	char *name = NULL;
	int i = 0;

	shell = malloc(sizeof(t_shell *));
	shell->environ = env;
	printf("|----------------|Minishell|-----------------|\n");
	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

	name = get_name(name);
	shell->ctrl = 0;
	while (1)
	{
		line = readline(name);
		if (!line)
			ctrl_D(line);
		name = get_name(name);
		add_history(line);
		if (line[0] == 0)
			continue;
		shell->str = ft_split(line, ' ');
		shell->str_pipe = ft_split(line, '|');
		pipe_counter();
		if (shell->pipe > 0)
		{
			shell_pipe_dup2();
			sleep(1);
			continue;
		}
		else if (check_cmnd(i))
		{
			sleep(1);
			continue;
		}
		free(line);
	}
	return(1);
}
