/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:24:56 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/28 19:48:09 by oozcan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <time.h>

// typedef struct	ss_list
// {
// 	char *data;
// 	struct ss_list *next;
// }				tt_list;

char **g_environ;

typedef struct s_shell
{
	char 	**str;
	char	**str_pipe;
	char	**env;
	char	**temp;
	t_list	*asd;
	//char	**op;
	int	pipe;
	int	*pid;
}	t_shell;

char *to_lower(char *str);

int		check_cmnd(t_shell *shell, int i);
int		other_cmnds(char **arg);
int		op_check(char **str, t_shell *shell);
int		ft_strcmp(char *asd, char *sda);
char	*get_name(char *name);
void	ft_cd(char **arg, int i);
void	 ft_echo(char **str, int i);
void	ft_pwd(void);
int 	ft_env(t_shell *shell);
void	ft_export(t_shell *shell);
void	pipe_counter(t_shell *shell);
void	shell_pipe_dup2(t_shell *shell);
void	ft_fill(t_shell *shell);

#endif
