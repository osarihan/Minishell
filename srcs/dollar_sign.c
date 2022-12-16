/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:13:20 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/16 18:14:34 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	ex_status = ft_itoa(g_shell->exit_status);
	while (ex_status[i])
	{
		tmp[i] = ex_status[i];
		i++;
	}
	j++;
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34 \
			&& str[j] != '$' && str[j] != 39)
	{
		tmp[i] = str[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	free(ex_status);
	return (tmp);
}

char	*dollar_sign(char *str, int j)
{
	char	*env;
	char	*tmp;
	char	*ret;

	int (i) = 0;
	tmp = malloc(size_finder(str, j) + 1);
	if (str[j] == D_QUOTE || ft_strlen(str) == 1)
		return ("$\0");
	if (str[j] == '?')
		return (question_mark(i, j, tmp, str));
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34 \
			&& str[j] != '$' && str[j] != 39)
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
