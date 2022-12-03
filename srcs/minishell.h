/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:24:56 by osarihan          #+#    #+#             */
/*   Updated: 2022/12/02 10:28:49 by osarihan         ###   ########.fr       */
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

#define S_QUOTE 39
#define D_QUOTE 34

typedef struct s_shell
{
	char	*line;
	char	*name;

	char **environ;
	char	*temp;
	t_list	*asd;
	t_list	*arg;
	t_list	*pipe_arg;
	int	ctrl;
	int	pipe;
	int	cmmp;
	int	exit_status;
}	t_shell;

t_shell	*shell;

void	sighandler(int signum);
void	ctrl_D(char *line);
int		routine(void);
void	assigment(char **env);
void	get_name(void);
int		is_cmd(char	*str);
char	*check_env(void);
char	**list_to_2D(t_list *list);
//ft_strcmp
int		ft_strcmp(char *asd, char *sda);
int		ft_strcmp2(char *asd, char *sda);
int		ft_strcmp3(char *asd, char *sda);
//export
void	ft_export(t_list *list);
void	ft_fill(void);
void	ultimate_alpha_index_finder(void);
void	printf_alph(void);
//unset
void	ft_unset(t_list *list);
//lexer
int		lexer(void);
void	space_skip(void);
void	lexur(int cnt);
int		text_cmpr(void);
int		token_compr(void);
int		cmnd_take(void);
int		ft_strcmp(char *asd, char *sda);
void 	cmnd_cut(int x);
//expander
void	expander(void);
char	*dollar_sign(char *str, int j);
void	d_quote(int	index);
void	s_quote(int	index);
//executor
void	executor(void);
//list
char	*list_data(t_list *root, int index);
t_list	*list_f_data(t_list *root, int index);
int		lstcmp(char *str);
void	ft_dstry_node(int c);
void	ft_lstremover(t_list *list);
//run_cmd
int		run_cmd(t_list *list);
void	run_cmd_with_pipe(void);
//cmds
int		ft_env(void);
void	ft_pwd(void);
void	ft_echo(t_list *list);
void	ft_cd(t_list *list);
int		other_cmnds(char **arg);
//pipe
void	pipe_f(void);

#endif
