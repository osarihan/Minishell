#include "minishell.h"

int	find_size()
{
	int	i = 0;
	int	j = 0;
	int	l = 0;
	int	res = 0;
	char *get;

	get = malloc(1000);//////////////////////////////////////////////////////////////////////////////////
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
					res += ft_strlen(getenv(get));
				}
				res++;
				j++;
			}
		}
		i++;
	}
	return (res);
}

char	*dollar_sign(char *str, int j, char *tmp, int t_i)
{
	char *tmp2;
	int	i = 0;

	while (str[j] != '\0' && str[j] != 32 && str[j] != 34)
	{
		tmp2[i] = str[j];
		i++;
		j++;
	}
	tmp2[i] = '\0';
	tmp2 = getenv(tmp2);
	i = 0;
	while (tmp2[i])
	{
		tmp[t_i] = tmp2[i];
		i++;
		t_i++;
	}
	tmp[t_i] = '\0';
	return (tmp);
}


char	*pars_fquote()
{
	int	i = 0;
	int	j;
	int	l = 0;
	char *tmp;
	int t_i = 0;
	char *last_line;
	int	len = 0;

	int	k = 0;

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
						tmp	= dollar_sign(shell->str[i], j + 1, tmp, t_i);
						while (shell->str[i][j] != 32 && shell->str[i][j] != '\0' && shell->str[i][j] != 34)
							j++;
						while(tmp[t_i]) // tmp nin index ini atilan deger kadar ilerletmek icin
							t_i++;
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
				printf("TMP:%s	shell->str[%d]:%s\n", tmp, i, shell->str[i]);
				len += ft_strlen(tmp);
				shell->str[i] = tmp;

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
		}
		//printf("SHELL->STR[%d]:%s\n", i,shell->str[i]);
		i++;
	}
	i = 0;
	j = 0;
	l = 0;

	last_line = malloc(sizeof(char) * (len + 1));
	while (shell->str[i])
	{
		//printf("SHELL STR[%d]:%s\n", i,shell->str[i]);
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
