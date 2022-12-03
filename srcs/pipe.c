#include "minishell.h"

void	pipe_counter()
{
	t_list	*iter;

	iter = shell->arg;
	shell->pipe = 0;
	while (iter != NULL)
	{
		if (ft_strcmp(iter->content, "|"))
			shell->pipe++;
		iter = iter->next;
	}
}

// int	pars_size(t_list *list)
// {
// 	int	len;

// 	len = 0;
// 	while (list != NULL && !ft_strcmp(list->content, "|"))
// 	{
// 		len += ft_strlen(list->content);
// 		list = list->next;
// 	}
// 	return (len);
// }

void	run_cmd_with_pipe()
{
	pipe_counter();
	pipe_f();
}
