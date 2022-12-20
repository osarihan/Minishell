/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:16:55 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/20 18:11:19 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	just_cd(int i, t_list *list)
{
	char	*str;
	char	*old_pwd;
	char	*content;

	old_pwd = ft_strjoin("OLDPWD=", check_env(ft_strdup("PWD")));
	ft_lstadd_back(&list, ft_lstnew(old_pwd));
	ft_export(list);
	str = ft_strjoin(getenv("HOME"), "/");
	chdir(str);
	content = ft_strjoin("PWD=", str);
	list_f_data(list, i + 1)->content = ft_strdup(content);
	ft_export(list);
	free(content);
}

void	update_pwd(int i, t_list *list)
{
	char	str[256];
	char	*old_pwd;
	char	*content;
	t_list	*tmp;

	old_pwd = ft_strjoin("OLDPWD=", check_env(ft_strdup("PWD")));
	tmp = list_f_data(list, i);
	free(tmp->content);
	tmp->content = old_pwd;
	ft_export(list);
	free(old_pwd);
	getcwd(str, sizeof(str));
	content = ft_strjoin("PWD=", str);
	list_f_data(list, i)->content = content;
	ft_export(list);
}

void	ft_cd(t_list *list)
{
	char	str[256];
	char	*pwd;

	int (i) = 0;
	g_shell->cd = 1;
	pwd = NULL;
	if (list_data(list, i + 1) != NULL)
	{
		pwd = ft_strjoin(getcwd(str, sizeof(str)), "/");
		i++;
		pwd = ft_strjoin2(pwd, list_data(list, i));
		if (access(pwd, F_OK) == -1)
		{
			printf("cd: %s: No such file or directory\n", list_data(list, i));
			free(pwd);
			return ;
		}
		chdir(pwd);
		update_pwd(i, list);
		free(pwd);
	}
	else
		just_cd(i, list);
	g_shell->cd = 0;
	g_shell->exit_status = 0;
}
