#include "minishell.h"

int	pars_size(t_list *list)
{
	int	len;

	len = 0;
	while (list != NULL && !ft_strcmp(list->content, "|"))
	{
		len += ft_strlen(list->content);
		list = list->next;
	}
	return (len);
}

void	pars_pipe()
{
	t_list	*iter;
	char	*tmp;
	int	i;

	i = 0;
	iter = shell->arg;
	while (iter != NULL)
	{
		if (i++ != 0)
			iter = iter->next;
		tmp = ft_calloc(pars_size(iter), sizeof(char *));
		while (iter != NULL && !ft_strcmp(iter->content, "|"))
		{
			tmp = ft_strjoin(tmp, iter->content);
			tmp = ft_strjoin(tmp, " ");
			iter = iter->next;
		}
		ft_lstadd_back(&shell->pipe_arg, ft_lstnew(ft_strdup(tmp)));
		free(tmp);
	}
	while (shell->pipe_arg != NULL)
	{
		printf("shell->pipe_arg:%s\n", shell->pipe_arg->content);
		shell->pipe_arg = shell->pipe_arg->next;
	}
	//free(tmp);
}

void	run_cmd_with_pipe()
{
	pars_pipe();
}
