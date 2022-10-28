#include "minishell.h"

void	ft_export(t_shell *shell)
{
	t_list *temp;
	static int i = 0;
	if (i++ == 0)
		ft_fill(shell);
	temp = ft_lstnew(shell->str[1]);
	ft_lstadd_back(&shell->asd, temp);
	printf("%s\n", ft_lstlast(shell->asd)->content);
	return;
}

void	ft_fill(t_shell *shell)
{
	int i = 0;
	t_list *dsa;
	t_list *temp;

	shell->asd = malloc(sizeof(t_list *));
	while (g_environ[i] != NULL)
	{
		temp = ft_lstnew(g_environ[i]);
		ft_lstadd_back(&shell->asd, temp);
		i++;
	}
}
