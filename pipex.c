/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mocherqu <mocherqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 17:24:08 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/26 17:41:41 by mocherqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void free_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void free_split2(t_var *var)
{
	int i;

	i = 0;
	while (var->tab[i])
	{
		free(var->tab[i]);
		i++;
	}
	free(var->tab);
}

void ft_pipex(t_var *var)
{
	while (var->path[++var->i] && !var->j)
	{
		var->str = ft_strjoin(var->path[var->i], var->tab[0]);
		if (!access(var->str, F_OK))
		{
			var->tab[0] = ft_strdup(var->str);
			var->j = 1;
		}
		free(var->str);
	}
}

int main(int argc, char **argv, char *env[])
{
	t_list *pipe1;
	t_var *var;

	if (argc == 5)
	{
		var = (t_var *)malloc(sizeof(t_var));
		pipe1 = ft_lstnew(ft_split(argv[2], ' '));
		ft_lstadd_back(&pipe1, ft_lstnew(ft_split(argv[3], ' ')));
		var->tab = (char **)pipe1->content;
		var->path = ft_split(env[6], ':');
		var->str = var->path[0];
		var->path[0] = NULL;
		var->path[0] = ft_substr(var->str, 5, ft_strlen(var->str));
		free(var->str);
		var->i = -1;
		var->j = 0;
		ft_pipex(var);
		if (access(argv[1], F_OK))
		{
			perror("");
			exit(1);
		}
		var->fd = pipe(var->p);
		if (var->fd == -1)
		{
			perror("");
			exit(1);
		}
		var->fd = open(argv[4], O_RDWR | O_CREAT, 0755);
		var->fd2 = open(argv[1], O_RDONLY);
		if (var->fd == -1)
		{
			perror("");
			exit(1);
		}
		var->pid = fork();
		if (var->pid == 0)
		{
			var->pid2 = fork();
			if (var->pid2 == 0)
			{
				dup2(var->fd2, 0);
				dup2(var->p[1], 1);
				dup2(var->p[1], 2);
				if (execve(var->tab[0], var->tab, env) < 0)
				{
					perror("");
					exit(1);
				}
				exit(0);
			}

			var->i = -1;
			var->j = 0;
			var->tab = (char **)pipe1->next->content;
			ft_pipex(var);
			close(var->p[1]);
			dup2(var->p[0], 0);
			close(var->p[0]);
			dup2(var->fd, 1);
			if (execve(var->tab[0], var->tab, NULL) < 0)
			{
				perror("");
				exit(1);
			}
		}
		else
		{
			close(var->fd2);
			close(var->p[1]);
			close(var->p[0]);
			wait(0);
		}
		free(pipe1);
		free_split(var->tab);
		free(var);
		free_split(var->path);
	}
	else
		write(1, "Invalid number of arguments !\n", 31);
	return (0);
}