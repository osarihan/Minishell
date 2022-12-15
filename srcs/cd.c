/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:16:55 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/15 16:25:43 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	just_cd(int i, t_list *list)
{
	char	*str;
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", check_env(ft_strdup("PWD")));
	ft_lstadd_back(&list, ft_lstnew(old_pwd));
	ft_export(list);
	str = ft_strjoin(getenv("HOME"), "/");
	chdir(str);
	list_f_data(list, i + 1)->content = ft_strjoin("PWD=", str);
	ft_export(list);
}

void	update_pwd(int i, t_list *list)
{
	char	str[256];
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", check_env(ft_strdup("PWD")));
	list_f_data(list, i)->content = ft_strdup(old_pwd);
	ft_export(list);
	getcwd(str, sizeof(str));
	list_f_data(list, i)->content = ft_strjoin("PWD=", str);
	ft_export(list);
}

void	ft_cd(t_list *list)
{
	int		i;
	char	str[256];
	char	*pwd;
	char	*str3;
	char	*old_pwd;

	pwd = NULL;
	i = 0;
	if (list_data(list, i + 1) != NULL)
	{
		pwd = ft_strjoin(getcwd(str, sizeof(str)), "/");
		i++;
		pwd = ft_strjoin(pwd, list_data(list, i));
		if (access(pwd, F_OK) == -1)
		{
			printf("cd: %s: No such file or directory\n", list_data(list, i));
			return ;
		}
		chdir(pwd);
		update_pwd(i, list);
	}
	else
		just_cd(i, list);
	shell->exit_status = 0;
}
