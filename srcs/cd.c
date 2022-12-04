#include "minishell.h"

void	just_cd(int i, char *old_pwd, t_list *list)
{
	char	*str;
	shell->temp = ft_strdup("PWD");
	ft_lstadd_back(&list, ft_lstnew(ft_strjoin("OLDPWD=", check_env())));
	ft_export(list);
	str = ft_strjoin(getenv("HOME"), "/");
	chdir(str);
	list_f_data(list, i + 1)->content = ft_strjoin("PWD=", str);
	ft_export(list);
}

void	update_pwd(int i, char *old_pwd, t_list *list)
{
	char	str[256];
	getcwd(str, sizeof(str));
	list_f_data(list, i)->content = ft_strjoin("PWD=", str);
	ft_export(list);
	list_f_data(list, i)->content = ft_strjoin("OLDPWD=", old_pwd);
	ft_export(list);
}

void	ft_cd(t_list *list)
{
	int	i;
	char str[256];
	char *pwd = NULL;
	char *str3;
	char *old_pwd;

	char	*content;
	i = 0;
	content = list_data(list, i);
	if (list_data(list, i + 1) != NULL)
	{
		shell->temp = ft_strdup("PWD");
		old_pwd = ft_strjoin("OLDPWD=", check_env());
		pwd = ft_strjoin(getcwd(str, sizeof(str)), "/");
		i++;
		pwd = ft_strjoin2(pwd, list_data(list, i));
		chdir(pwd);
		update_pwd(i, old_pwd, list);
	}
	else
		just_cd(i, old_pwd, list);
	shell->exit_status = 0;
	free(content);
}
