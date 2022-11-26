#include "minishell.h"

char	*expand()
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->str[i])
	{
		while (shell->str[i][j])
		{
			if (shell->str[i][j] == '$')
			{
				j++;
				//ft_strlcpy(shell->str[i], dollar_sign(shell->str[i], j), ft_strlen(dollar_sign(shell->str[i], j)));
				printf("%s\n", shell->str[i]);
				shell->str[i] = dollar_sign(shell->str[i], j);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return("");
}

int	find_size()
{
	int	i = 0;
	int	j = 0;
	int	l = 0;
	int	res = 0;
	char *get;

	get = malloc(size_finder(shell->str[i], j) + 1);
	while (shell->str[i])
	{
		j = 0;
		if (shell->str[i][j] == 34)
		{
			j++;
			while (shell->str[i][j] != 34 && shell->str[i][j] != 39 && shell->str[i][j] != '\0')
			{
				if (shell->str[i][j] == '$')
				{
					if (shell->str[i][j + 1] == 34)//"$" tek dolar durumu
					{
						get[l] = '$';//free hatasi almamak icin
						res++;
						break;
					}
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

//'"$mete"'
//quote

char	*expand_fquote()
{
	int	i = 0;
	int	j;
	char *tmp = NULL; //NULL vermezsek basta join atinca onune cop degerler gelir
	int t_i = 0;

	tmp = malloc(find_size() + 1);//for quote
	while (shell->str[i])
	{
		j = 0;
		while(shell->str[i][j])
		{
			if (shell->str[i][j] == 34)
				tmp = d_quote(i, ++j, t_i, tmp);
			else if (shell->str[i][j] == 39)
			{
				tmp = s_quote(i, ++j, t_i, tmp);
				while (shell->str[i][j] != 39)
					j++;
			}
			j++;
			shell->len++;
		}
		ft_memset(tmp, '\0', ft_strlen(tmp)); // tmp ile isimiz bitti icini bosaltiyoruz.
		i++;
	}
	free(tmp);
	return(final_line());
}
