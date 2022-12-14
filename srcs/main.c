/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/14 13:09:25 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line(); // yeni satira gectigimizi belirtir
		//rl_replace_line("", 0); // eger komut satirina yazilan karakterler varsa ve ctrl-C yapilirsa yazilan karakterleri siler.
		rl_redisplay();
	}
}

void	ctrl_D(char *line)
{
	printf("\b\bexit\n");
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
	shell->saved_stdout = dup(1);
	shell->saved_stdin = dup(0);
	shell->dl_red = 0;
	shell->dr_red = 0;
	shell->r_red = 0;
	shell->l_red = 0;
	get_name();
	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

}

int	lexer(void)
{
	int cnt;
	char *tmp;

	tmp = shell->line;
	while (*shell->line)
	{
		space_skip();
		if (shell->arg == NULL || ft_strcmp("|", ft_lstlast(shell->arg)->content))
		{
			cnt = cmnd_take();
			if (cnt == -1)
				return (0);
			else if (cnt > 0)
			{
				cmnd_cut(cnt);
				continue;
			}
		}
		cnt = token_compr();
		if (cnt > 0)
			lexur(cnt);
		else if (cnt == -1)
			return(0);
		cnt = text_cmpr();
		if (cnt > 0)
			lexur(cnt);
	}
	free(tmp);
	return (1);
}

void lst_free(void)
{
	t_list	*iter;


	while (shell->arg != NULL)
	{
		iter = shell->arg;
		free(shell->arg->content);
		shell->arg = shell->arg->next;
		free(iter);
	}
}

// void lst_free(void)
// {
// 	while (shell->arg != NULL)
// 	{
// 		free(shell->arg->content);
// 		free(shell->arg);
// 		shell->arg = shell->arg->next;
// 	}
// }


int	main(int argc, char **argv, char **env)
{
	assigment(env);
	while (true)
	{
		if (!routine())
		{
			free(shell->line);
			continue;
		}
		if (!lexer())
			continue;
		expander();
		t_list *iter;
		iter = shell->arg;
		while (iter != NULL)
		{
			//printf("argsLAST:::::%s\n", iter->content);
			iter = iter->next;
		}
		//system("leaks minishell");
		executor();
		lst_free();
	}
	return(1);
}
