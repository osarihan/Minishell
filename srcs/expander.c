#include "minishell.h"

void	expand(int	index)
{
	char	*content;
	char	*tmp;
	//tmp = malloc(10000);
	//ft_bzero(tmp, 10000);//trash cleaner
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = ft_calloc(10000, sizeof(char));
	content = ft_strdup(list_data(shell->arg, index));
	while (content[i])
	{
		if (content[i] == '$')
		{
			printf("TMP0:%s\n", tmp);
			tmp = ft_strjoin2(tmp, dollar_sign(ft_strdup(content), ++i));
			printf("TMP1:%s\n", tmp);
			while(content[i] != 32 && content[i] != '$' && content[i] != '\0')
				i++;
			while (++j < ft_strlen(tmp));
		}
		if (content[i] == '$')
			continue;
		tmp[j] = content[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(tmp);
	list_f_data(shell->arg, index)->content = ft_strdup(tmp);
	free(content);
}

int	quote_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE)
			return (D_QUOTE);
		else if (str[i] == S_QUOTE)
			return (S_QUOTE);
		i++;
	}
	return (0);
}

void	expander()
{
	t_list	*iter;
	char	*content;
	int		quote_status;
	int		index;

	index = 0;
	iter = shell->arg;
	while (iter != NULL)
	{
		content = ft_strdup(iter->content);
		quote_status = quote_check(content);
		if (quote_status == S_QUOTE)
			s_quote(index);
		else if (quote_status == D_QUOTE)
			d_quote(index);
		else
			expand(index);
		iter = iter->next;
		index++;
		free(content);
	}
}
