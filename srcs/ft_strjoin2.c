#include "minishell.h"

char    *ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	int     i;
	int     j;
	i = -1;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		s1 = (char *)ft_calloc(sizeof(char), 1);
	str = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char    *ft_strjoin3(char *s1, char *s2)
{
	char	*str;
	int     i;
	int     j;
	i = -1;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		s1 = (char *)ft_calloc(sizeof(char), 1);
	str = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
