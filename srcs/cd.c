#include "minishell.h"

void	just_cd(int i, t_list *list)
{
	char	*str;
	char	*old_pwd;

	shell->temp = ft_strdup("PWD");
	old_pwd = ft_strjoin("OLDPWD=", check_env());
	ft_lstadd_back(&list, ft_lstnew(ft_strjoin("OLDPWD=", check_env())));
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

	shell->temp = ft_strdup("PWD");
	old_pwd = ft_strjoin("OLDPWD=", check_env());
	printf("old_pwd2:%s\n", old_pwd);
	getcwd(str, sizeof(str));
	printf("str:%s\n", str);
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

	i = 0;
	// shell->temp = ft_strdup("PWD");
	// old_pwd = ft_strjoin("OLDPWD=", check_env());
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
