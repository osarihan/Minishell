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
	char	*line;
	char	*name;

	char **environ;
	char 	**str;
	char	**str_pipe;
	char	*temp;
	t_list	*asd;
	int	ctrl;
	int	s_quote;
	int	d_quote;
	int	pipe;
	int	cmmp;
	int	len;
}	t_shell;

t_shell	*shell;

char *to_lower(char *str);

int		check_cmnd(int i);
int		other_cmnds(char **arg);
void	get_name(void);


void	ft_cd(char **arg, int i);
void	 ft_echo(char **str, int i);
void	ft_pwd(void);
int 	ft_env(void);
void	ft_unset(void);
void	ft_export(void);

char	*pars_fquote(void);
char	*pars(void);

char	**ft_split_mod(char const *s, char c);
int		ft_strcmp(char *asd, char *sda);
int		ft_strcmp2(char *asd, char *sda);
int		ft_strcmp3(char *asd, char *sda);
void	ft_fill(void);
int		lstcmp(char *str);
void	ft_lstremover(void);
void	ft_dstry_node(int c);

int		quote_check(char *str);
int		pipe_counter(void);
void	pipe_status(void);
void	shell_pipe_dup2(void);


void	ultimate_alpha_index_finder(void);
void	printf_alph(void) ;

char	*d_quote(int i, int j, int t_i, char *tmp);
char	*s_quote(int i, int j, int t_i, char *tmp);
char	*final_line(void);
char	*check_env(char *str);

#endif
