/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/28 16:09:16 by osarihan         ###   ########.fr       */
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

	//get_name();
	shell->name = "31>";
	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

	//shell->arg = malloc(sizeof(t_list));
	shell->ctrl = 0;
	shell->len = 0;//for quote malloc
}

void lexer(void)
{
	int cnt;
	while (*shell->line)
	{
		space_skip();
		if (shell->arg == NULL || ft_strcmp("|", ft_lstlast(shell->arg)->content))
		{
			printf("aa\n");
			cnt = cmnd_take();
			lexur(cnt);
			printf("lstlasdf::.%s\n", ft_lstlast(shell->arg)->content);
			continue;
		}
		cnt = token_compr();
		if (cnt > 0)
			lexur(cnt);
		cnt = text_cmpr();
		if (cnt > 0)
			lexur(cnt);
	}
	while (shell->arg != NULL)
	{
		printf("args:::::%s\n", shell->arg->content);
		shell->arg = shell->arg->next;
	}
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	int i = 0;

	assigment(env);
	while (1)
	{
		if (!routine())
		{
			free(shell->line);
			continue;
		}
		//printf("%s\n")
		lexer();
	}
	return(1);
}
