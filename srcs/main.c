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

int	routine(void)
{
	shell->line = readline(shell->name);
	if (!shell->line)
		ctrl_D(shell->line);
	//get_name();
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

	get_name();

	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

	shell->ctrl = 0;
	shell->len = 0;//for quote malloc
}

int	is_cmd(char	*str)
{
	char	**path;
	int	i;

	i = 0;
	path = ft_split(ft_strdup(getenv("PATH")),':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i],"/");
		path[i] = ft_strjoin(path[i], str);
		if(access(path[i], F_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

void lexer()
{
	t_list *arg;
	t_list *iter = NULL;
	int	i = 0;
	int j;
	shell->cmd = malloc(sizeof(t_list));
	shell->arg = malloc(sizeof(t_list));
	shell->token = malloc(sizeof(t_list));
	shell->cmd = NULL;
	shell->arg = NULL;
	shell->token = NULL;
	while (shell->str[i] != NULL && shell->str[i][0] != '|')
	{
		if (is_cmd(shell->str[i]))
			ft_lstadd_back(&shell->cmd, ft_lstnew(shell->str[i]));
		else
		{
			ft_lstadd_back(&shell->arg, ft_lstnew(shell->str[i]));
			if (i == 1)
				iter = shell->arg;
			shell->arg->index = i;
			shell->arg = shell->arg->next;
		}
		i++;
	}
	shell->arg = iter;
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
		if (!quote_check(shell->line))
			continue;
		shell->str = ft_split_mod(shell->line, ' ');//D_QUOTE MOD
		lexer();
		if (shell->d_quote > 0 || shell->s_quote > 0)
		{
			expand_fquote();
			//printf("linem lan:%s\n", shell->line);
		}
		expand();
		if (pipe_counter())
		{
			pipe_status();
			continue;
		}
		else if (check_cmnd(i))
		{
			//sleep(1);
			free(shell->arg);
			free(shell->cmd);
			continue;
		}
		free(shell->line);
	}
	return(1);
}
