/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/27 18:17:05 by oozcan           ###   ########.fr       */
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

// tt_list	*list_in(t_shell *shell, tt_list *list)
// {
// 	tt_list *tmp;
// 	int	i = 0;

// 	tmp = list;
// 	while (shell->str[i] != NULL)
// 	{
// 		list->data = shell->str[i];
// 		list = list->next;
// 		list = malloc(sizeof(tt_list));
// 		i++;
// 	}
// 	list->data = NULL;
// 	return (tmp);
// }

int	main(int argc, char **argv, char **env)
{
	//tt_list *list;
	t_shell	*shell;
	char *asd;
	char *name = NULL;
	int i = 0;

	printf("|----------------|Minishell|-----------------|\n");

	shell = malloc(sizeof(t_shell *));

	signal(SIGINT, sighandler); // ctrl-C
	signal(SIGQUIT, SIG_IGN); // ctrl-\ //

	name = get_name(name);
	while (1)
	{
		asd = readline(name);
		if (!asd) // ctrl-D
		{
			printf("exit\n");
			free(asd);
			exit(1);
		}
		name = get_name(name);
		add_history(asd);
		if (asd[0] == 0)
			continue;
		shell->str = ft_split(asd, ' ');
		shell->str_pipe = ft_split(asd, '|');
		pipe_counter(shell);
		if (shell->pipe > 0)
		{
			shell_pipe_dup2(shell);
			sleep(1);
			continue;
		}
		else
		{
			if (check_cmnd(shell, i))
			{
				continue;
			}
			else
				printf("%s: command not found.\n", asd);
		}
		free(asd);
	}
	return(1);
}
