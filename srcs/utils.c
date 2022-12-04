#include "minishell.h"

void	reset_stdout()
{
	dup2(shell->saved_stdout, STDOUT_FILENO);
	close(shell->saved_stdout);
}

void	get_name()
{
	shell->name = getenv("USER");
	shell->name = ft_strjoin(shell->name, "\033[0;32m@minishell -> \033[0m");
}

void	to_lower(t_list *list, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			cmd[i] += 32;
		i++;
	}
	list->content = ft_strdup(cmd);
	free(cmd);
}
