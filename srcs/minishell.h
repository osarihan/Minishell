/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:24:56 by osarihan          #+#    #+#             */
/*   Updated: 2022/11/30 14:24:05 by osarihan         ###   ########.fr       */
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
	t_list	*cmd;
	t_list	*arg;
	t_list	*token;
	int	ctrl;
	int	s_quote;
	int	d_quote;
	int	pipe;
	int	cmmp;
	int	len;
	int	exit_status;
	int	fd;
}	t_shell;

t_shell	*shell;

void	sighandler(int signum);
void	ctrl_D(char *line);
int		routine(void);
void	assigment(char **env);
int		is_cmd(char	*str);
//lexer
void here_doc(int i);
void 	lexer(void);
void	space_skip(void);
void	lexur(int cnt);
int		text_cmpr(void);
int		token_compr(void);
int	cmnd_take(void);
int	ft_strcmp(char *asd, char *sda);
#endif
