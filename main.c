/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:52:54 by darakely          #+#    #+#             */
/*   Updated: 2022/12/16 21:27:23 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro.h"

int	ft_strlen(char *str)
{
	if (!str)
		return (0);
	int i = -1;
	while (str[++i]);
	return (i);
}

void	ft_putstr(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_cd(char **argv)
{
	if (!argv[1] || argv[2])
	{
		ft_putstr("error: cd: bad arguments\n");
		return ;
	}
	if (chdir(argv[1]) != 0)
	{
		ft_putstr("error: cd: cannot change directory to ");
		ft_putstr(argv[1]);
		ft_putstr("\n");
	}
}

char	**check_pipe(char **argv)
{
	if (!argv)
		return (0);
	int i = -1;
	while (argv[++i])
		if (strcmp(argv[i], "|") == 0)
			return (argv + i + 1);
	return (0);
}

void	exec_one_cmd(char **argv, char **env)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		ft_putstr("error: fatal\n");
		exit(1);
	}
	else if (pid == 0)
	{
		execve(argv[0], argv, env);
		ft_putstr("error: cannot execute ");
		ft_putstr(argv[0]);
		ft_putstr("\n");
		exit(1);
	}
	waitpid(0, 0, 0);
}

void	get_parent(char ***argv, int *count, int fd[2], int input)
{
	if (dup2(fd[0], input) < 0)
	{
		ft_putstr("error: fatal\n");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	*argv = check_pipe(*argv);
	(*count)++;
}

void	get_child(char **argv, char **env, int fd[2], int input)
{
	if (dup2(input, 0) < 0 || (check_pipe(argv) != 0 && dup2(fd[1], 1) < 0))
	{
		ft_putstr("error: fatal\n");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	close(input);
	int i = -1;
	while (argv[++i])
		if (strcmp(argv[i], "|") == 0)
			break ;
	argv[i] = 0;
	exec_one_cmd(argv, env);
	exit(0);
}

void	exec_cmds(char **argv, char **env)
{
	int		fd[2];
	int		count_pipe = 0;
	pid_t	pid;
	int		input = dup(0);
	if (input == -1)
	{
		ft_putstr("error: fatal\n");
		exit(1);
	}
	while (argv)
	{
		if (pipe(fd) < 0)
		{
			ft_putstr("error: fatal\n");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			ft_putstr("error: fatal\n");
			exit(1);
		}
		if (pid == 0)
			get_child(argv, env, fd, input);
		else
			get_parent(&argv, &count_pipe, fd, input);
	}
	close(input);
	while (count_pipe-- > 0)
		waitpid(0, 0, 0);
}

void	get_exec(char **argv, char **env)
{
	if (strcmp(argv[0], "cd") == 0)
		ft_cd(argv);
	else if (check_pipe(argv) == 0)
		exec_one_cmd(argv, env);
	else
		exec_cmds(argv, env);
}

int main(int argc, char **argv, char **env)
{
	if (argc < 2)
		return (0);
	int i = 1, j = 1;
	while (argv[i])
	{
		if (strcmp(argv[i], ";") == 0)
		{
			argv[i] = 0;
			get_exec(argv + j, env);
			i++;
			while (argv[i] && strcmp(argv[i], ";") == 0)
				i++;
			j = i;
		}
		else
			i++;
	}
	get_exec(argv + j, env);
}