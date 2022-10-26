/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:24:56 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/24 13:51:52 by osarihan         ###   ########.fr       */
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

typedef struct s_shell
{
	char 	**str;
	char	**str_pipe;
	char	**op;
	char	**cmd;

	int	pipe;
	int	id;
	char *name;
}	t_shell;

char *to_lower(char *str);

int		check_cmnd(t_shell *shell, int i);
int		other_cmnds(char **arg);
int		op_check(char **str, t_shell *shell);
int		ft_strcmp(char *asd, char *sda);
char	*get_name(char *name);
void	ft_cd(t_shell *shell, int i);
int		ft_echo(t_shell *shell, int i);
void	ft_pwd(void);
int 	ft_env(void);
int		ft_export(char *str);
void	pipe_counter(t_shell *shell);
void	shell_pipe_dup2(t_shell *shell);
int	check_cmnd_pipe(t_shell *shell, int i);

#endif
