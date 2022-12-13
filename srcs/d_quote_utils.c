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

char	*question_mark(int i, int j, char *tmp, char *str)
{
	char	*ex_status;

	ex_status = ft_itoa(shell->exit_status);
	while (ex_status[i])
	{
		tmp[i] = ex_status[i];
		i++;
	}
	j++;
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34 && str[j] != '$' && str[j] != 39)
	{
		tmp[i] = str[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	free(ex_status);
	return (tmp);
}

char *ret_env(int i, char *str)
{
	char *ret;
	int j;
	int l_i;
	int len;

	l_i = i;
	len = 0;
	while (str[l_i++])
		len++;
	ret = malloc(sizeof(char *) + (len + 1));
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

char	*take_before_equal(char *content)
{
	int		i;
	char	*env_name;

	i = 0;
	while (content[i] != '=')
		i++;
	env_name = malloc((sizeof(char *) * i) + 1);
	i = 0;
	while (content[i] != '=')
	{
		env_name[i] = content[i];
		i++;
	}
	env_name[i] = '\0';
	return (env_name);
}

char *check_env(char *desired_env)
{
	t_list *l_tmp;
	char	*env_name;
	int i;

	i = 0;
	if (!shell->asd)
		ft_fill();
	l_tmp = shell->asd;
	while (l_tmp != NULL)
	{
		env_name = take_before_equal(l_tmp->content);
		if (ft_strcmp(env_name, desired_env))
		{
			free(desired_env);
			while (i++ < ft_strlen(env_name));
			free(env_name);
			return(ret_env(i, l_tmp->content));
		}
		l_tmp = l_tmp->next;
		free(env_name);
	}
	free(desired_env);
	return (NULL);
}

char	*dollar_sign(char *str, int j)
{
	char	*env;
	char	*tmp;
	char 	*ret;
	int	i;

	i = 0;
	tmp = malloc(size_finder(str, j) + 1);
	if (str[j] == D_QUOTE || ft_strlen(str) == 1)//tek dolar durumu && ft_strlen olan tirnaksiz tek dolar durumu
		return("$\0");
	if (str[j] == '?')
		return (question_mark(i, j, tmp, str));
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34 && str[j] != '$' && str[j] != 39)
	{
		tmp[i] = str[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	free(str);
	env = check_env(tmp);
	if (env == NULL)
		return ("");
	ret = ft_strdup(env);
	free(env);
	return (ret);
}
