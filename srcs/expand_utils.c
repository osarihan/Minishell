#include "minishell.h"

char	*dollar_sign(char *str, int j)
{
	char	*tmp2;
	int	i = 0;

	tmp2 = malloc(10000);
	if (str[j] == 34 || ft_strlen(str) == 1)//tek dolar durumu && ft_strlen olan tirnaksiz tek dolar durumu
		return("$");
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

char b_a_d_quote(int i, int j, int t_i, char *tmp)
{

}

char	*d_quote(int i, int j, int t_i, char *tmp)
{
	int len = 0;
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
		else if (shell->str[i][j] == 39)//d_quote icinde tek tirnak
		{
			j++;
			t_i--;
			while (shell->str[i][j] != 39 && shell->str[i][j] != '\0')
			{
				tmp[t_i] = shell->str[i][j];
				t_i++;
				j++;
			}
			t_i++;
			j++;
		}
		else
		{
			len = ft_strlen(tmp);
			if (shell->str[i][j])
			{
				tmp[len] = shell->str[i][j];//dolardan sorasini yazmasi icin
				len++;
				j++;
			}
		}
	}
	if (shell->str[i][j + 1] > 32)//d_quote dan sonrasinda herhangi bisi varsa onu da tmp e ekliyoruz.
	{
		j++;//d_quote
		len = ft_strlen(tmp);
		while (shell->str[i][j] != '\0')
		{
			tmp[len] = shell->str[i][j];
			len++;
			j++;
		}
		tmp[len] = '\0';
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
	ft_strlcpy(shell->str[i], tmp, (ft_strlen(tmp) + 1));
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
