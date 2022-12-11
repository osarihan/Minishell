#include "minishell.h"

void    right_redirect(int index)
{
	int fd;
	int pid;
	printf("AA\n");
	shell->to_open = list_data(shell->arg, index + 1);
	//open_file();
	cut_redirect(index);
	fd = open(shell->to_open, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return;
	dup2(fd, 1);
	close (fd);
	//executor();
	//reset_stdout();
}
int redirect_check(void)
{
	int i;
	t_list *iter;
	i = 0;
	iter = shell->arg;
	while (iter)
	{
		if (ft_strcmp(iter->content, "<") || ft_strcmp(iter->content, ">"))
		{
			if (ft_strcmp(iter->content, "<"))
				shell->l_red++;
			else if (ft_strcmp(iter->content, ">"))
				shell->r_red++;
			i++;
		}
		iter = iter->next;
	}
	return (i);
}
void    run_cmd_with_red()
{
	int stat;
	int index;
	stat = redirect_check();
	if (stat)
	{
		if (shell->l_red > 0)
			return;
		else if (shell->r_red > 0)
		{
			printf("slm31\n");
			index = where_is_redirect(">");
			//printf (">>>;;;%s\n", list_data(shell->arg, index));
			right_redirect(index);
			return;
		}
	}
}
////////////////
void    cut_redirect(int index)
{
	ft_dstry_node2(shell->arg, index);
	ft_dstry_node2(shell->arg, index);
	//printf("byby\n");
}
int where_is_redirect(char *str)
{
	int i;
	t_list *iter;
	iter = shell->arg;
	i = 0;
	while (iter)
	{
		if (ft_strcmp(iter->content, str))
			return(i);
		i++;
		iter = iter->next;
	}
	return (0);
}
