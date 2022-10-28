#include "minishell.h"

void	ft_export(t_shell *shell)
{
	static int i = 0;
	if (i++ == 0)
		ft_fill(shell);
	ft_lstadd_back(&shell->asd, ft_lstnew(shell->str[1]));
	return;
}

void	ft_fill(t_shell *shell)
{
	int i = 0;
	t_list *dsa;

	shell->asd = malloc(sizeof(t_list *));
	while (g_environ[i] != NULL)
	{
		ft_lstadd_back(&shell->asd, ft_lstnew(g_environ[i]));
		i++;
	}
}
