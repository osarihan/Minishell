#include "minishell.h"

static int	count_strings(char const *s, char c)
{
	int	act_pos;
	int	str_count;

	act_pos = 0;
	str_count = 0;
	if (s[act_pos] == c)
		str_count--;
	while (s[act_pos] != '\0')
	{
		if (s[act_pos] == c && s[act_pos + 1] != c && s[act_pos + 1] != '\0')
			str_count++;
		act_pos++;
	}
	str_count++;
	return (str_count);
}

static char	*malloc_strings(const char *s, char c)
{
	char	*word;
	int		i;
	int j = 0;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == 39)
			return(quote(s, 39));
		if (s[i] == 34)
			return(quote(s, 34));//after quote string is not working
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_mod(char const *s, char c)
{
	int		words;
	char	**tab;
	int	quote = 1;
	int		i;
	int j = 0;

	if (!s)
		return (NULL);
	words = count_strings(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			tab[i] = malloc_strings(s, c);
			if (tab[i][0] == 39)
			{
				s++;
				while (*s != 39)
					s++;
			}
			else if (tab[i][0] == 34)
			{
				s++;
				while (shell->d_quote != quote)////////////
				{
					j = ft_strlen(tab[i]);
					if (*s == 34)
						quote++;
					s++;
				}
				//after quote "xyz"dfs
				while (*s != c && *s)
				{
					tab[i][j] = *s;
					j++;
					s++;
				}
				tab[i][j] = '\0';
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
