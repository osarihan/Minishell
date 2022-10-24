#include "minishell.h"

int	op_counter(char **str)
{
	int	i = 0;
	int	total = 0;

	while (str[i])
	{
		if ((ft_strchr(str[i], '&') && ft_strlen(str[i]) == 1) \
						|| (ft_strchr(str[i], '|') && ft_strlen(str[i]) == 1))
		{
			total++;
		}
		i++;
	}
	return (total);
}

void	pipe_counter(t_shell *shell)
{
	int i;
	int j;

	shell->pipe = 0;
	i = 0;
	j = 0;
	while (shell->str[i])
	{
		j = 0;
		while (shell->str[i][j])
		{
			if (shell->str[i][j] == '|')
				shell->pipe++;
			j++;
		}
		i++;
	}
}

// int	op_check(char **str, t_shell *shell)
// {
// 	int	i = 0;
// 	int	i_op = 0;
// 	int	total_op = 0;

// 	total_op = op_counter(str);
// 	if (total_op > 0)
// 		shell->op = malloc(sizeof(char **) * total_op);
// 	while (str[i])
// 	{
// 		if (ft_strchr(str[i], '|') && ft_strlen(str[i]) == 1)
// 		{
// 			//printf("pipe bulundu\n");
// 			shell->op[i_op] = "|";
// 			i_op++;
// 		}
// 		i++;
// 	}
// 	shell->i_op = i_op;
// 	//print
// 	// i = 0;
// 	// while (shell->op[i] != NULL)
// 	// {
// 	// 	printf("OP : %s\n", shell->op[i]);
// 	// 	i++;
// 	// }
// 	if (shell->i_op > 0)
// 		return (1);
// 	return (0);
// }
