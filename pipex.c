/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mocherqu <mocherqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 17:24:08 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/27 17:20:04 by mocherqu         ###   ########.fr       */
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

void	ft_free_list(t_list *head)
{
	t_list	*tmp;

	tmp = head;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
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
		var->tmp2 = ft_split(argv[2], ' ');
		pipe1 = ft_lstnew(var->tmp2);
		var->tmp3 = ft_split(argv[3], ' ');
		ft_lstadd_back(&pipe1, ft_lstnew(var->tmp3));
		var->tab = (char **)pipe1->content;
		var->tmp = ft_substr(env[6], 5, ft_strlen(env[6]));
		var->path = ft_split(var->tmp, ':');
		free(var->tmp);
		var->str = var->path[0];
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
		var->fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0755);
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
			free_split(var->tab);
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
		// free(pipe1->content);
		// printf("%s\n", var->tmp2[0]);
		// printf("%s\n", pipe1->content[0]);
		// if (pipe1->content != NULL)
		// 	free_split(pipe1->content);
		printf("tmp[2] : %s\n", var->tmp2[0]);
		free_split(var->tmp2);
		free_split(var->tmp3);
		free_split(var->path);
		printf("OK\n");
		free(var);
		ft_free_list(pipe1);
	}
	else
		write(1, "Invalid number of arguments !\n", 31);
	return (0);
}