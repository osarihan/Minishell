#include "minishell.h"

// void manuel(void)
// {
//  char *temp;
//  temp = ft_strdup(list_data(shell->arg, i));
//  char *catf[] = {temp, NULL};
//  path = ft_strjoin("/bin/", list_data(shell->arg, i));
//  execve(path, catf, NULL);
//  exit(0);
// }
void    heredoc_prompt(int index)
{
	char *to_write;
	int fd;
	char *tmp;
	char *eof;
	char *path;
	//shell->temp = "PATH";
	//path = check_env();
	//path = ft_strjoin(path, ft_strjoin("/", ".heredoc"));
	eof = list_data(shell->arg, index + 1);
	printf("eof?? %s\n", eof);
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return ;
	while (true)
	{
		to_write = readline(">");
		if (ft_strcmp(to_write, eof))
		{
			close(fd);
			return;
		}
		else
		{
			ft_putstr_fd(to_write, fd);
			ft_putstr_fd("\n", fd);
		}
		free(to_write);
	}
	close(fd);
	return;
}
void    run_heredoc(int i)
{
	int fd;
	int pid;
	char *temp;
	char *path;
	pid = fork();
	if (pid == 0)
	{
		fd = open(".heredoc", O_RDWR, 0777);
		if (fd < 0)
			return ;
		dup2(fd, 0);
		close(fd);
		// temp = ft_strdup(list_data(shell->arg, i));
		// // char *catf[] = {temp, NULL};
		// // path = ft_strjoin("/bin/", list_data(shell->arg, i));
		// // execve(path, catf, NULL);
		//executor();
		run_cmd(shell->arg);
		exit(0);
	}
	wait(NULL);
	waitpid(pid, NULL, -1);
}
//NU3NLL9F
void    cut_heredoc(int index)
{
	// printf("%s\n", shell->arg->content);
	 // printf("%s\n", shell->arg->next->content);
	// printf("%s\n", shell->arg->next->next->content);
	ft_dstry_node2(shell->arg, index);
	ft_dstry_node2(shell->arg, index);
}
void	heredoc(void)
{
	t_list  *iter;
	int i = 0;
	int index;
	index = heredoc_finder();
	iter = shell->arg;
	// while (iter != NULL)
	// {
	//  if (!lstcmp2(iter, "<<"))
	//  {
	//      iter = iter->next;
	//      i++;
	//      // if (lstcmp2(iter, "<<") == 1)
	//      //  i -= 2;
	//      continue;
	//  }
	//  else
	//      break;
	// }
	heredoc_prompt(index);
	cut_heredoc(index);
	if (shell->heredoc_cnt == 1)
	{
		run_heredoc(index);
		shell->heredoc_cnt--;
	}
	else
		shell->heredoc_cnt--;
	if (shell->heredoc_cnt == 0)
	{
		return;
	}
	if (!lstcmp2(iter, "<<"))
		heredoc();
}
int heredoc_check(void)
{
	int i = 0;
	while (shell->arg)
	{
		if (!lstcmp2(shell->arg, "<<"))
		{
			printf ("heredoca gitt\n");
			shell->heredoc_cnt = heredoc_cnt();
			heredoc();
			return (1);
		}
		else
			return(0);
	}
	return (0);
}
