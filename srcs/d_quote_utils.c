/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:35:11 by oozcan            #+#    #+#             */
/*   Updated: 2022/12/22 15:48:48 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_env(int i, char *str)
{
	char	*ret;
	int		j;
	int		l_i;
	int		len;

	l_i = i;
	len = 0;
	while (str[l_i++])
		len++;
	ret = malloc(sizeof(char *) + (len + 1));
	j = 0;
	while (str[i++])
		ret[j++] = str[i];
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

char	*check_env(char *desired_env)
{
	t_list	*l_tmp;
	char	*env_name;
	size_t	i;

	i = 0;
	l_tmp = g_shell->asd;
	while (l_tmp != NULL)
	{
		env_name = take_before_equal(l_tmp->content);
		if (ft_strcmp(env_name, desired_env))
		{
			free(desired_env);
			while (i < ft_strlen(env_name))
				i++;
			free(env_name);
			return (ret_env(i, l_tmp->content));
		}
		l_tmp = l_tmp->next;
		free(env_name);
	}
	free(desired_env);
	return (NULL);
}
