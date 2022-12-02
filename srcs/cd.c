#include "minishell.h"

void	just_cd(int i, char *old_pwd)
{
	char	*str;
	shell->temp = ft_strdup("PWD");
	ft_lstadd_back(&shell->arg, ft_lstnew(ft_strjoin("OLDPWD=", check_env())));
	ft_export();
	str = ft_strjoin(getenv("HOME"), "/");
	chdir(str);
	list_f_data(shell->arg, i + 1)->content = ft_strjoin("PWD=", str);
	ft_export();
}

void	update_pwd(int i, char *old_pwd)
{
	char	str[256];
	getcwd(str, sizeof(str));
	list_f_data(shell->arg, i)->content = ft_strjoin("PWD=", str);
	ft_export();
	list_f_data(shell->arg, i)->content = ft_strjoin("OLDPWD=", old_pwd);
	ft_export();
}

void	ft_cd()
{
	int	i;
	char str[256];
	char *pwd = NULL;
	char *str3;
	char *old_pwd;

	char	*content;
	i = 0;
	content = list_data(shell->arg, i);
	if (list_data(shell->arg, i + 1) != NULL)
	{
		shell->temp = ft_strdup("PWD");
		old_pwd = ft_strjoin("OLDPWD=", check_env());
		pwd = ft_strjoin(getcwd(str, sizeof(str)), "/");
		i++;
		pwd = ft_strjoin(pwd, list_data(shell->arg, i));
		chdir(pwd);
		update_pwd(i, old_pwd);
	}
	else
		just_cd(i, old_pwd);
}
