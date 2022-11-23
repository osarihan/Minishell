#include "minishell.h"

char	*dollar_sign(char *str, int j)
{
	char	*tmp2;
	int	i = 0;

	tmp2 = malloc(10000);
	if (str[j] == '$')
	{
		tmp2 = ft_itoa(getpid());
		while (++i < ft_strlen(tmp2));
		j++;
	}
	if (str[j] == '?')
	{
		tmp2[i] = '0';
		i++;
		j++;
	}
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34 && str[j] != '$')
	{
		tmp2[i] = str[j];
		i++;
		j++;
	}
	tmp2[i] = '\0';
	shell->temp = tmp2;
	if (check_env(ft_strdup(tmp2)))
		return (check_env(ft_strdup(tmp2)));
	return ("");
}

char	*d_quote(int i, int j, int t_i, char *tmp)
{
	while (shell->str[i][j] != 34 && shell->str[i][j] != '\0')
	{
		if (shell->str[i][j] == '$')
		{
			j++;
			tmp = ft_strjoin(tmp, dollar_sign(shell->str[i], j));
			while (shell->str[i][j] != 32 && shell->str[i][j] != '\0' && shell->str[i][j] != 34 && shell->str[i][j] != '$')
				j++;
			while (t_i++ < ft_strlen(tmp));//tmp index
		}
		else
		{
			if (shell->str[i][j])
			{
				tmp[t_i - 1] = shell->str[i][j];
				t_i++;
				j++;
			}
		}
	}
	shell->len += ft_strlen(tmp);// tmp bir pointer old. icin shell->str ye yeni yer actik eger bunu dup olmadan yapsaydik assagida tmp nin icini '\0' ile doldurdugumuzda str de degisecekti...
	ft_strlcpy(shell->str[i], tmp, (ft_strlen(tmp) + 1));
	return (tmp);
}

char	*s_quote(int i, int j, int t_i, char *tmp)
{
	while (shell->str[i][j] != 39)
	{
		tmp[t_i] = shell->str[i][j];
		t_i++;
		j++;
	}
	tmp[t_i] = '\0';
	shell->len += ft_strlen(tmp);
	shell->str[i] = ft_strdup(tmp);// tmp bir pointer old. icin shell->str ye yeni yer actik eger bunu dup olmadan yapsaydik assagida tmp nin icini '\0' ile doldurdugumuzda str de degisecekti...
	return (tmp);
}

char	*final_line()
{
	char	*f_line;
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = 0;
	f_line = malloc(sizeof(char) * (shell->len + 1));
	while (shell->str[i])
	{
		while (shell->str[i][j])
		{
			f_line[l] = shell->str[i][j];
			l++;
			j++;
		}
		f_line[l] = 32;
		l++;
		j = 0;
		i++;
	}
	f_line[l] = '\0';
	return (f_line);
}
