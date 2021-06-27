/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mocherqu <mocherqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 17:24:29 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/27 13:53:22 by mocherqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"


typedef struct s_pipe
{
	char			**cmd;
	struct s_pipe	*next;
}	t_pipe;

typedef struct	s_var
{
	char c;
	char *str;
	int i;
	int j;
	int fd;
	int fd2;
	int p[2];
	char **tab;
	char **path;
	char *tmp;
	char **tmp2;
	char **tmp3;
	pid_t pid;
	pid_t pid2;
}	t_var;


# endif