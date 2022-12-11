#include "minishell.h"

int	pipe_status()
{
	t_list	*iter;

	iter = shell->arg;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->content, "|"))
		{
			if (iter->next == NULL)
			{
				ft_putstr_fd("Error: A few arguments after pipe\n", STDERR_FILENO);
				return (-1);
			}
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

void	executor()
{
	int	status;

	if (!heredoc_check())
	{
		status = pipe_status();
		if (status)
			run_cmd_with_pipe();
		if (!status)
			run_cmd(shell->arg);
		else
			return ;
	}
	// else
	// 	heredoc();
}
