#include "minishell.h"

void	ft_unset(t_shell *shell)
{
	ft_lstremover(shell);
}

void	ft_lstremover(t_shell *shell)
{
	int i = ft_strlen(shell->str[1]);
	char *tmp;
	char *tmp2;
	t_list *tmplst;

	int c = 0;
	tmp2 = shell->str[1];
	c += 1;
	tmplst = shell->asd;
	tmplst = tmplst->next;
	while(tmplst)
	{
		tmp = (char *)tmplst->content;
		if (ft_strcmp(tmp, tmp2))
		{
			ft_dstry_node(shell, c);
		}
		tmplst = tmplst->next;
		c++;
	}
}

void ft_dstry_node(t_shell *shell, int c)
{
	t_list *tmp;
	t_list *tmp2;
	tmp = shell->asd;
	tmp2 = shell->asd;

	while (c > 1 && tmp != NULL)
	{
		if (tmp->next != NULL)
			tmp = tmp->next;
		c--;
	}
	if (tmp->next->next != NULL)
		tmp2 = tmp->next->next;
	else
		tmp2 = NULL;
	if (tmp2 != NULL)
		tmp->next = tmp2;
	else
		tmp->next = NULL;
}

void	ft_export(t_shell *shell)
{
	if (!shell->ctrl)
	{
		ft_fill(shell);
		shell->ctrl++;
	}
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
