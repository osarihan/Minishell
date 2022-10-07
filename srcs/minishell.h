/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:24:56 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/07 16:10:10 by osarihan         ###   ########.fr       */
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

int	check_cmnd(char *str);
int	ft_strcmp(char *asd, char *sda);
char	*get_name(char *name);
int	ft_ls(char *str);
int	ft_cd(char *str);
int	ft_echo(char *str);
int	ft_pwd();
int ft_env(void);
int	ft_export(char *str);
typedef struct s_shell
{
	
}	t_shell;
#endif