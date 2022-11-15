#include "minishell.h"

char *ret_env(int i, char *str)
{
	char *ret;
	int j;

	ret = malloc(10000);
	j = 0;
	while (str[i])
	{
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char *check_env(char *str)
{
	t_list *l_tmp;
	char	*tmp;
	char	*tmp2;
	int i = 0;

	if (!shell->asd)
		ft_fill();
	l_tmp = shell->asd;
	while (l_tmp != NULL)
	{
		tmp = ft_strdup(l_tmp->content);
		while (tmp[i] != '=')
		{
			tmp2[i] = tmp[i];
			i++;
		}
		tmp2[i] = '\0';
		if (ft_strcmp(tmp2, shell->temp))
			return (ret_env(i + 1, tmp));
		l_tmp = l_tmp->next;
		i = 0;
	}
	return (NULL);
}
