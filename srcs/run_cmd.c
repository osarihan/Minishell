#include "minishell.h"

void	get_name()
{
	shell->name = getenv("USER");
	shell->name = ft_strjoin(shell->name, "\033[0;32m@minishell -> \033[0m");
}

char *to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

int	run_cmd()
{
	char	*content;

	content = ft_strdup(shell->arg->content);
	// if (!ft_strcmp(content, "CD"))
	// 	content = to_lower(content);
	if (ft_strcmp(content, "cd"))
		ft_cd();
	if (ft_strcmp(content, "export"))
		ft_export();
	else if (ft_strcmp(content, "unset"))
		ft_unset();
	else if (ft_strcmp(content, "echo"))
		ft_echo();
	else if (ft_strcmp(content, "pwd") || \
					ft_strcmp(content, "PWD"))
		ft_pwd();
	else if (ft_strcmp(content, "env"))
		ft_env();
	else if (ft_strcmp(content, "exit"))
		exit(0);
	else if (other_cmnds(list_to_2D()))
		return (1);
	else
		return (0);
	return (1);
}
