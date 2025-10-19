/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:00:45 by thaperei          #+#    #+#             */
/*   Updated: 2025/10/19 11:55:09 by thawan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_file(char *filename, int stream)
{
	int	fd;

	fd = -1;
	if (stream == STDIN_FILENO)
		fd = open(filename, O_RDONLY, 0777);
	else if (stream == STDOUT_FILENO)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (fd);
}

static void	execute_first_command(char **argv, char **envp, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[READ]);
	fd = open_file(argv[1], STDIN_FILENO);
	if (fd < 0)
		print_error("pipex", 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		print_error("pipex", 1);
	if (dup2(pipe_fd[WRITE], STDOUT_FILENO) < 0)
		print_error("pipex", 1);
	close(fd);
	close(pipe_fd[WRITE]);
	execute_command(argv[2], envp);
}

static void	execute_second_command(char **argv, char **envp, int *pipe_fd)
{
	int	fd;

	close(pipe_fd[WRITE]);
	fd = open_file(argv[4], STDOUT_FILENO);
	if (fd < 0)
		print_error("pipex", 1);
	if (dup2(fd, STDOUT) < 0)
		print_error("pipex", 1);
	if (dup2(pipe_fd[READ], STDIN_FILENO) < 0)
		print_error("pipex", 1);
	close(fd);
	close(pipe_fd[READ]);
	execute_command(argv[3], envp);
}

void	init_pipex(char **argv, char **envp)
{
	int		pipe_fd[2];
	int		pid;

	if (!envp && !argv)
		return ;
	if (pipe(pipe_fd) < 0)
		print_error("pipex", 1);
	pid = fork();
	if (pid < 0)
		print_error("pipex", 1);
	else if (pid == 0)
		execute_first_command(argv, envp, pipe_fd);
	execute_second_command(argv, envp, pipe_fd);
	wait(NULL);
}
