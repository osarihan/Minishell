#include "minishell.h"

int	find_size()
{
	int	i = 0;
	int	j = 0;
	int	l = 0;
	int	res = 0;
	char *get;

	get = malloc(10000);//////////////////////////////////////////////////////////////////////////////////
	while (shell->str[i])
	{
		j = 0;
		if (shell->str[i][j] == 34 || shell->str[i][j] == 39)
		{
			j++;
			while (shell->str[i][j] != 34 && shell->str[i][j] != 39 && shell->str[i][j] != '\0')
			{
				if (shell->str[i][j] == '$')
				{
					j++;
					while (shell->str[i][j] != 34 && shell->str[i][j] != 32)
					{
						get[l] = shell->str[i][j];
						j++;
						l++;
					}
					get[l] = '\0';
					l = 0;
					if (getenv(get) != NULL)
						res += ft_strlen(getenv(get));
				}
				res++;
				j++;
			}
		}
		i++;
	}
	free(get);
	return (res);
}


char	*dollar_sign(char *str, int j)
{
	char	*tmp;
	char	*tmp2;
	int	dd_status = 0;
	int	i = 0;

	tmp = malloc(10000);
	tmp2 = tmp;
	if (str[j] == '$')
	{
		tmp2 = ft_itoa(getpid());
		while (++i < ft_strlen(tmp2));
		dd_status = 1;
		j++;
	}
	if (str[j] == '?')
	{
		tmp2[i] = '0';
		i++;
		j++;
	}
	while (str[j] != '\0' && str[j] != 32 && str[j] != 34)
	{
		tmp2[i] = str[j];
		i++;
		j++;
	}
	tmp2[i] = '\0';
	if (dd_status == 1)
	{
		free(tmp);
		return (tmp2);
	}
	if (getenv(tmp2) == NULL)
	{
		free(tmp);
		return(tmp2);
	}
	tmp2 = getenv(tmp2);
	free(tmp);
	return (tmp2);
}


char	*pars_fquote()
{
	int	i = 0;
	int	j;
	int	l = 0;
	char *tmp = NULL; //NULL vermezsek basta join atinca onune cop degerler gelir
	int t_i = 0;
	char *last_line;
	int	len = 0;

	tmp = malloc(find_size(shell->str) + 1);//for quote
	while (shell->str[i])
	{
		j = 0;
		while(shell->str[i][j])
		{
			if (shell->str[i][j] == 34)
			{
				j++;
				while (shell->str[i][j] != 34)
				{
					if (shell->str[i][j] == '$')
					{
						sleep(1);
						tmp	= ft_strjoin(tmp, dollar_sign(shell->str[i], j + 1));
						while (shell->str[i][j] != 32 && shell->str[i][j] != '\0' && shell->str[i][j] != 34)
							j++;
						while (++t_i < ft_strlen(tmp));//tmp index
					}
					else
					{
						tmp[t_i] = shell->str[i][j];
						t_i++;
						tmp[t_i] = '\0';
						j++;
					}
				}
				t_i = 0;
				len += ft_strlen(tmp);
				shell->str[i] = ft_strdup(tmp); // tmp bir pointer old. icin shell->str ye yeni yer actik eger bunu dup olmadan yapsaydik assagida tmp nin icini '\0' ile doldurdugumuzda str de degisecekti...
			}
			else if (shell->str[i][j] == 39)
			{
				j++;
				while (shell->str[i][j] != 39)
				{
					tmp[t_i] = shell->str[i][j];
					t_i++;
					j++;
				}
				tmp[t_i] = '\0';
				t_i = 0;
				len += ft_strlen(tmp);
				shell->str[i] = tmp;
			}
			j++;
			len++;
		}
		ft_memset(tmp, '\0', ft_strlen(tmp)); // tmp ile isimiz bitti icini bosaltiyoruz.
		i++;
	}
	i = 0;
	j = 0;
	l = 0;

	last_line = malloc(sizeof(char) * (len + 1));
	while (shell->str[i])
	{
		while (shell->str[i][j])
		{
			last_line[l] = shell->str[i][j];
			l++;
			j++;
		}
		last_line[l] = 32;
		l++;
		j = 0;
		i++;
	}
	last_line[l] = '\0';
	return(last_line);
}
