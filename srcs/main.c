/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/30 15:04:58 by osarihan         ###   ########.fr       */
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
			cnt = cmnd_take();
			lexur(cnt);
			continue;
		}
		cnt = token_compr();
		
		if (cnt > 0)
			lexur(cnt);
		cnt = text_cmpr();
		if (cnt > 0)
			lexur(cnt);
	}
	t_list *iter;
	iter = shell->arg;
	while (iter != NULL)
	{
		printf("ilk hali: %s\n", iter->content);
		iter = iter->next;
	}
	printf("---------------------------------\n");
	return;
}

static int ft_lstfinder(char *str, int i)
{
	t_list *iter;

	iter = shell->arg;
	while (!ft_strcmp(str, iter->content))
	{
		iter = iter->next;
		i++;
	}
	i--;
	return (i);
		
}

int	main(int argc, char **argv, char **env)
{
	int i = 0;
	int a = 1;
	assigment(env);

	while (1)
	{
		if (!routine())
		{
			free(shell->line);
			continue;
		}
		lexer();
		a = ft_lstfinder("<<", a);
		printf("aa\n");
		printf("%d\n", a);
		if (a > 0)
			here_doc(a);

		t_list *iter;

		iter = shell->arg;
		while (iter != NULL)
		{
			printf("args:::::%s\n", iter->content);
			iter = iter->next;
		}
		shell->arg = NULL;
	}
	return(1);
}
