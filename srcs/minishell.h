/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oozcan <oozcan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:24:56 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/01 13:47:03 by oozcan           ###   ########.fr       */
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
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>

#include <signal.h>

typedef struct s_shell
{
	char **environ;
	char 	**str;
	char	**str_pipe;
	char	**temp;
	t_list	*asd;
	char	*tmp;
	int	ctrl;
	int	s_quote;
	int	d_quote;
	int	pipe;
	int cmmp;
}	t_shell;

t_shell	*shell;

char *to_lower(char *str);

int		check_cmnd(int i);
int		other_cmnds(char **arg);
char	*get_name(char *name);


void	ft_cd(char **arg, int i);
void	 ft_echo(char **str, int i);
void	ft_pwd(void);
int 	ft_env(void);
void	ft_unset(void);
void	ft_export(void);

char	*pars_fquote();

int		ft_strcmp(char *asd, char *sda);
int		ft_strcmp2(char *asd, char *sda);
int		ft_strcmp3(char *asd, char *sda);
void	ft_fill(void);
int		lstcmp(char *str);
void	ft_lstremover(void);
void	ft_dstry_node(int c);

int		quote_check(char *str);
void	shell_pipe_dup2(void);
void	pipe_counter(void);


void	ultimate_alpha_index_finder(void);
void	printf_alph(void) ;

#endif
