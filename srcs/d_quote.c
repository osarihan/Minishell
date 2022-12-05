#include "minishell.h"

int	size_finder(char *str, int j)
{
	int	len;

	len = 0;
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34 && str[j] != '$')
	{
		j++;
		len++;
	}
	return (len);
}

char *ret_env(int i, char *str)
{
	char *ret;
	int j;

	int l_i = i;
	int len = 0;

	while (str[l_i])
	{
		l_i++;
		len++;
	}
	ret = malloc(sizeof(char *) + (len + 1));
	j = 0;
	while (str[i])
	{
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	free(str);
	return (ret);
}

char *check_env(void)
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
		i = 0;
		while (tmp[i] != '=')
			i++;
		tmp2 = malloc(sizeof(char *) * i + 1);
		i = 0;
		while (tmp[i] != '=')
		{
			tmp2[i] = tmp[i];
			i++;
		}
		tmp2[i] = '\0';
		if (ft_strcmp(tmp2, shell->temp))
		{
			//free(tmp2);
			return (ret_env(i + 1, tmp));
		}
		l_tmp = l_tmp->next;
		free(tmp2);
		free(tmp);
	}
	return (NULL);
}

char	*dollar_sign(char *str, int j)
{
	char	*tmp2;
	char	*ex_status;
	int	i = 0;

	tmp2 = malloc(size_finder(str, j) + 1);
	if (str[j] == D_QUOTE || ft_strlen(str) == 1)//tek dolar durumu && ft_strlen olan tirnaksiz tek dolar durumu
		return("$\0");
	if (str[j] == '?')
	{
		ex_status = ft_itoa(shell->exit_status);
		while (ex_status[i])
		{
			tmp2[i] = ex_status[i];
			i++;
		}
		j++;
		while (str[j] != '\0' && str[j] != 32 && str[j] != 34 && str[j] != '$' && str[j] != 39)
		{
			tmp2[i] = str[j];
			j++;
			i++;
		}
		tmp2[i] = '\0';
		free(ex_status);
		return(tmp2);
	}
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34 && str[j] != '$' && str[j] != 39)
	{
		tmp2[i] = str[j];
		i++;
		j++;
	}
	tmp2[i] = '\0';
	shell->temp = ft_strdup(tmp2);
	free(tmp2);
	//free(str);
	if (check_env())
		return (check_env());
	return ("");
}

void	d_quote(int	index)
{
	char	*content;
	char	*tmp;
	tmp = malloc(10000);///////////////////////////////////
	ft_bzero(tmp, 10000);
	char	*rtn_dollar;
	char	*iter_tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	content = list_data(shell->arg, index);
	i = 0;
	while (content[i])
	{
		if (content[i] == D_QUOTE)
			i++;
		else if (content[i] == '$')
		{
			i++;
			rtn_dollar = dollar_sign(content, i);
			iter_tmp = rtn_dollar;
			while(content[i] != 32 && content[i] != '$' && content[i] != '\0' && content[i] != D_QUOTE && content[i] != S_QUOTE)
				i++;
			while (*rtn_dollar)
			{
				tmp[j] = (*rtn_dollar);
				rtn_dollar++;
				j++;
			}
			tmp[j] = '\0';
		}
		else
		{
			tmp[j] = content[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	list_f_data(shell->arg, index)->content = ft_strdup(tmp);
	free(tmp);
	//free(content);
	//free(iter_tmp);
}

// void	d_quote(int	index)
// {
// 	char	*content;
// 	char	*tmp;
// 	tmp = malloc(10000);///////////////////////////////////
// 	ft_bzero(tmp, 10000);
// 	char	*rtn_dollar;
// 	char	*iter_tmp;
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	content = list_data(shell->arg, index);
// 	printf("CON:%s\n", content);
// 	i = 0;
// 	while (content[i])
// 	{
// 		if (content[i] == D_QUOTE)
// 			i++;
// 		if (content[i] == '$')
// 		{
// 			tmp = ft_strjoin(tmp, dollar_sign(content, ++i));
// 			printf("rtn:%s\n", rtn_dollar);
// 			while(content[i] != 32 && content[i] != '$' && content[i] != '\0' && content[i] != D_QUOTE && content[i] != S_QUOTE)
// 			{
// 				printf("CON[I]:%c\n", content[i]);
// 				i++;
// 			}
// 			while (++j < ft_strlen(tmp));
// 			if (content[i] == '$')
// 				continue;
// 		}
// 		else
// 		{
// 			tmp[j] = content[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	tmp[j] = '\0';
// 	printf("tmpfirst::%s\n", tmp);
// 	list_f_data(shell->arg, index)->content = ft_strdup(tmp);
// 	printf("tmplast::%s\n", tmp);
// 	//free(tmp);
// 	//free(content);
// 	//free(iter_tmp);
// }
