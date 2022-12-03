#include "minishell.h"

void	run_cmd(t_list *list)
{
	if (!ft_strcmp(list->content, "CD"))
		to_lower(list, list->content);
	if (ft_strcmp(list->content, "cd"))
		ft_cd(list);
	else if (ft_strcmp(list->content, "export"))
		ft_export(list);
	else if (ft_strcmp(list->content, "unset"))
		ft_unset(list);
	else if (ft_strcmp(list->content, "echo"))
		ft_echo(list);
	else if (ft_strcmp(list->content, "pwd") || \
					ft_strcmp(list->content, "PWD"))
		ft_pwd();
	else if (ft_strcmp(list->content, "env"))
		ft_env();
	else if (ft_strcmp(list->content, "exit"))
		ft_exit(list);
	else
		other_cmnds(list_to_2D(list));
}
