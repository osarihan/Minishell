/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/28 15:14:59 by oozcan           ###   ########.fr       */
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

// int	op(t_shell *shell)
// {
// 	int	i = 0;
// 	int	j = 0;
// 	int	id;
// 	while (shell->str[i + 1])
// 		i++;
// 	while(i > 0)
// 	{
// 		if (ft_strcmp(shell->str[i], shell->op[shell->i_op - 1]))
// 		{
// 			shell->id = fork();
// 			if (shell->id == 0)
// 			{
// 				//printf("i am child process\n");
// 				return (i + 1);
// 			}
// 			wait(NULL);
// 			j++;
// 		}
// 		i--;
// 	}
// 	return (0);
// }

void	ctrl_D(char *line)
{
	printf("exit\n");
	free(line);
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char *line;
	char *name = NULL;
	int i = 0;

	shell = malloc(sizeof(t_shell *));
	shell->temp = env;
	printf("|----------------|Minishell|-----------------|\n");

	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

	//init_env();
	name = get_name(name);
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
		ft_export(shell);
		pipe_counter(shell);
		if (shell->pipe > 0)
		{
			shell_pipe_dup2(shell);
			sleep(1);
			continue;
		}
		else if (check_cmnd(shell, i))
			continue;
		free(line);
	}
	return(1);
}
