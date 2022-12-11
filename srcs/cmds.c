#include "minishell.h"

int ft_env(void)
{
	t_list *tmp;

	if (!shell->ctrl)
	{
		ft_fill();
		shell->ctrl++;
	}
	tmp = shell->asd;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	shell->exit_status = 0;
	return (1);
}

void	ft_pwd(void)
{
	t_list *l_tmp;
	char	*tmp;
	char	*tmp2;
	int i = 0;
	int	j = 0;

	if (!shell->asd)
		ft_fill();
	l_tmp = shell->asd;
	tmp2 = malloc(ft_strlen("PWD") + 1);
	while (l_tmp != NULL)
	{
		tmp = l_tmp->content;
		while (tmp[i] != '=' && i < 3)
		{
			tmp2[i] = tmp[i];
			i++;
		}
		tmp2[i] = '\0';
		if (ft_strcmp(tmp2, "PWD"))
		{
			printf("%s\n", &tmp[++i]);
			free(tmp2);
			return ;
		}
		l_tmp = l_tmp->next;
		i = 0;
	}
	shell->exit_status = 0;
}

void	 ft_echo(t_list *list)
{
	char	*content;
	int	i;

	i = 1;
	if (list_data(list, i) == NULL)
		printf("\n");
	else
	{
		content = list_data(list, i);
		while (content != NULL)
		{
			if (ft_strcmp(content, "-n") && list_data(list, i + 1) == NULL && i == 1)
				break;
			if (ft_strcmp(content, "-n") && list_data(list, i + 1) != NULL)
			{
				printf("%s", list_data(list, i + 1));
				i++;
			}
			else if (list_data(list, i + 1) == NULL)
				printf("%s\n", content);
			else
				printf("%s ", content);
			i++;
			content = list_data(list, i);
		}
	}
	shell->exit_status = 0;
}

void	ft_exit(t_list *list)
{
	if (list->next != NULL)
	{
		list = list->next;
		shell->exit_status = ft_atoi(list->content);
	}
	exit(shell->exit_status);
}
