/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/02 10:28:59 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line(); // yeni satira gectigimizi belirtir
		//rl_replace_line("", 0); // eger komut satirina yazilan karakterler varsa ve ctrl-C yapilirsa yazilan karakterleri siler.
		rl_redisplay();
	}
}

void	ctrl_D(char *line)
{
	printf("exit\n");
	free(shell->line);
	exit(1);
}

int	routine(void)
{
	shell->line = readline(shell->name);
	if (!shell->line)
		ctrl_D(shell->line);
	add_history(shell->line);
	if (shell->line[0] == 0)
		return (0);
	return (1);
}

void	assigment(char **env)
{
	printf("|----------------|Minishell|-----------------|\n");
	shell = malloc(sizeof(t_shell));

	shell->environ = env;
	shell->ctrl = 0;

	get_name();
	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

}

void lexer(void)
{
	int cnt;
	while (*shell->line)
	{
		space_skip();
		if (shell->arg == NULL || ft_strcmp("|", ft_lstlast(shell->arg)->content))
		{
			cnt = cmnd_take();
			if (cnt > 0)
				cmnd_cut(cnt);
		}
		cnt = token_compr();
		if (cnt > 0)
			lexur(cnt);
		cnt = text_cmpr();
		if (cnt > 0)
			lexur(cnt);
	}
}

int	main(int argc, char **argv, char **env)
{
	assigment(env);
	while (1)
	{
		if (!routine())
		{
			free(shell->line);
			continue;
		}
		lexer();
		expander();
		executor();
		// t_list *iter;
		// iter = shell->arg;
		// while (iter != NULL)
		// {
		// 	printf("argsLAST:::::%s\n", iter->content);
		// 	iter = iter->next;
		// }
		//if (run_cmd())
		shell->arg = NULL;
		//free(shell->line);
	}
	return(1);
}
