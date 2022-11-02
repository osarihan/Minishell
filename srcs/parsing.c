#include "minishell.h"

int	find_size()
{
	int	i = 0;
	int	j = 0;
	int	res;

	while (shell->str[i])
	{
		j = 0;
		if (shell->str[i][j] == 34 || shell->str[i][j] == 39)
		{
			j++;
			while (shell->str[i][j] != 34 && shell->str[i][j] != 39)
			{
				res = j;
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


void	pars_fquote()
{
	int	i = 0;
	int	j;
	char *tmp;
	int t_i = 0;

	tmp = malloc(sizeof(char) * (find_size(shell->str) + 1));//for quote

	while (shell->str[i])
	{
		//printf("%s is parsing\n", shell->str[i]);
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
				shell->str[i] = tmp;
			}
			j++;
		}
		i++;
	}
}
