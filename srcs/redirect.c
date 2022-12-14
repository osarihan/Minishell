#include "minishell.h"

void    right_redirect(int index)
{
	int fd;
	int pid;
	shell->to_open = list_data(shell->arg, index + 1);
	cut_redirect(index);
	fd = open(shell->to_open, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return;
	dup2(fd, 1);
	close (fd);
}
void    left_redirect(int index)
{
	int fd;
	int pid;
	shell->to_open = list_data(shell->arg, index + 1);
	cut_redirect(index);
	fd = open(shell->to_open, O_RDWR, 0777);
	if (fd < 0)
		return;
	dup2(fd, 0);
	close(fd);
}
void    double_right_redirect(int index)
{
	int fd;
	int pid;
	shell->to_open = list_data(shell->arg, index + 1);
	cut_redirect(index);
	fd = open(shell->to_open, O_RDWR | O_APPEND, 0777);
	if (fd < 0)
		return;
	dup2(fd, 1);
	close (fd);
}
int redirect_check(void)
{
	int i;
	t_list *iter;
	i = 0;
	if (shell->arg == NULL)
		return (0);
	iter = shell->arg;
	while (iter)
	{
		if (ft_strcmp(iter->content, "<") || ft_strcmp(iter->content, ">") || ft_strcmp(iter->content, ">>") || ft_strcmp(iter->content, "<<"))
		{
			if (ft_strcmp(iter->content, "<"))
				shell->l_red++;
			else if (ft_strcmp(iter->content, ">"))
				shell->r_red++;
			else if (ft_strcmp(iter->content, ">>"))
				shell->dr_red++;
			else if (ft_strcmp(iter->content, "<<"))
				shell->dl_red++;
			i++;
		}
		iter = iter->next;
	}
	return (i);
}
int which_red(char *content)
{
	if (ft_strcmp(content, ">"))
		return(1);
	else if (ft_strcmp(content, ">>"))
		return (2);
	else if (ft_strcmp(content, "<"))
		return (3);
	else if (ft_strcmp(content, "<<"))
		return (4);
}
void redirect_decider(int stat, int index)
{
	if (stat == 1)
		right_redirect(index);
	else if (stat == 2)
		double_right_redirect(index);
	else if (stat == 3)
		left_redirect(index);
	else if (stat == 4)
		run_heredoc(index);
}
void    cut_redirect(int index)
{
	ft_dstry_node2(shell->arg, index);
	ft_dstry_node2(shell->arg, index);
}
