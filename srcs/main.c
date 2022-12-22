/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/22 15:57:17 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_d(void)
{
	printf("\b\bexit\n");
	free(g_shell->line);
	exit(1);
}

int	routine(void)
{
	g_shell->line = readline(g_shell->name);
	if (!g_shell->line)
		ctrl_d();
	add_history(g_shell->line);
	if (g_shell->line[0] == 0)
		return (0);
	if (!q_check(g_shell->line))
		return (0);
	return (1);
}

void	assigment(char **env)
{
	printf("|----------------|Minishell|-----------------|\n");
	g_shell = malloc(sizeof(t_shell));
	g_shell->environ = env;
	g_shell->cd = 0;
	ft_fill();
	g_shell->ctrl = 0;
	g_shell->saved_stdout = dup(1);
	g_shell->saved_stdin = dup(0);
	g_shell->dl_red = 0;
	g_shell->dr_red = 0;
	g_shell->r_red = 0;
	g_shell->l_red = 0;
	g_shell->heredoc_quit = 0;
	get_name();
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc __attribute((unused)), char **argv __attribute((unused)) \
	, char **env)
{
	assigment(env);
	while (true)
	{
		if (!routine())
		{
			free(g_shell->line);
			continue ;
		}
		if (!lexer())
			continue ;
		expander();
		executor();
		lst_free();
	}
	return (1);
}
