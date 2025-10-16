/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:18:23 by thaperei          #+#    #+#             */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *filename, int stream)
{
	int	fd;

	fd = -1;
	if (stream == STDIN)
		fd = open(filename, O_RDONLY, 0777);
	else if (stream == STDOUT)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (access(filename, R_OK | W_OK) != 0 || fd < 0)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[READ]);
	fd = open_file(argv[1], STDIN);
	if (fd < 0)
	{
		close(pipe_fd[WRITE]);
		error_msg(strerror(errno));
	}
	dup2(fd, STDIN);
	dup2(pipe_fd[WRITE], STDOUT);
	close(fd);
	close(pipe_fd[WRITE]);
	execute_command(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[WRITE]);
	fd = open_file(argv[4], STDOUT);
	if (fd < 0)
	{
		close(pipe_fd[READ]);
		error_msg(strerror(errno));
	}
	dup2(fd, STDOUT);
	dup2(pipe_fd[READ], STDIN);
	close(fd);
	close(pipe_fd[READ]);
	wait(NULL);
	execute_command(argv[3], envp);
}

void	pipex(char **argv, char **envp)
{
	int		pipe_fd[2];
	int		pid_1;

	if (!envp && !argv)
		return ;
	if (pipe(pipe_fd) < 0)
		error_msg(strerror(errno));
	pid_1 = fork();
	if (pid_1 < 0)
		error_msg(strerror(errno));
	else if(pid_1 == 0)
		child_process(argv, envp, pipe_fd);
	parent_process(argv, envp, pipe_fd);
}

int main(int argc, char **argv, char **envp)
{
	if (argc - 1 != 4)
		error_msg("Usage: ./pipex file1 'cmd1' 'cmd2' file2");
	if (access(argv[1], F_OK) < 0)
		error_msg(strerror(errno));
	pipex(argv, envp);
	return (0);
}
