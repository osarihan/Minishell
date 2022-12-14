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

	char	**environ;
	char	*temp;
	t_list	*declare;
	t_list	*asd;
	t_list	*arg;
	t_list	*pipe_arg;
	int	ctrl;
	int	pipe;
	int	cmmp;
	int	exit_status;
	int	saved_stdout;
	char	*to_open;
	int	r_red;
	int	l_red;
	int	heredoc_cnt;

}	t_shell;

t_shell	*shell;

char	*check_env(char *desired_env);
char	*ft_strjoin2(char *s1, char *s2);
char    *ft_strjoin3(char *s1, char *s2);
//main
int		routine(void);
void	assigment(char **env);
//signal
void	sighandler(int signum);
void	ctrl_D(char *line);
//ft_strcmp
int		ft_strcmp(char *asd, char *sda);
int		ft_strcmp2(char *asd, char *sda);
int		ft_strcmp3(char *asd, char *sda);
//export
void	ft_export(t_list *list);
void	ft_fill(void);
void	ultimate_alpha_index_finder(void);
void	ultimate_alpha_index_finder_declared(void);
void	printf_alph_declared(void);
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
void cmnd_cut(int x);
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
char	**list_to_2D(t_list *list);
void ft_dstry_node2(t_list *iter, int c);
int lstcmp2(t_list *iter, char *str);
//run_cmd
void	run_cmd(t_list *list);
void	run_cmd_with_pipe(void);
//cmds
int		ft_env(void);
void	ft_pwd(void);
void	ft_echo(t_list *list);
void	ft_cd(t_list *list);
void	ft_exit(t_list *list);
void	other_cmnds(char **arg);
//pipe
void	pipe_f(void);
//utils
void	reset_stdin(void);
void	reset_stdout(void);
void	get_name(void);
void	to_lower(t_list *list, char *cmd);
//redirect
void	right_redirect(int index);
int		redirect_check(void);
void	run_cmd_with_red(void);
void	cut_redirect(int index);
int		where_is_redirect(char *str);
//heredoc
void    heredoc_prompt(int index);
void    run_heredoc(int i);
void    cut_heredoc(int index);
void    heredoc(void);
int 	heredoc_check(void);
int		heredoc_cnt(void);
int		heredoc_finder();
#endif
