#include "minishell.h"

void	s_quote(int index)
{
	char	*content;
	char	*tmp;
	tmp = malloc(10000);///////////////////////////////////////////
	int		i;
	int		j;

	j = 0;
	i = 0;
	content = list_data(shell->arg, index);
	while (content[i])
	{
		if (content[i] == S_QUOTE)
			i++;
		tmp[j] = content[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	list_f_data(shell->arg, index)->content = ft_strdup(tmp);// for free
	free(tmp);
}
