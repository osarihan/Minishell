#include "minishell.h"

int	pipe_counter(void)
{
	int i;
	int j;

	shell->pipe = 0;
	i = 0;
	j = 0;
	while (shell->str[i])
	{
		j = 0;
		while (shell->str[i][j])
		{
			if (shell->str[i][j] == '|')
				shell->pipe++;
			j++;
		}
		i++;
	}
	return (shell->pipe);
}

void	pipe_status(void)
{
	shell->str_pipe = ft_split(shell->line, '|');
	shell_pipe_dup2();
}
