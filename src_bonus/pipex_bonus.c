/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thawan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:29:38 by thawan            #+#    #+#             */
/*   Updated: 2025/10/20 14:01:00 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *filename, int stream)
{
	int	fd;

	fd = -1;
	if (stream == STDIN_FILENO)
		fd = open(filename, O_RDONLY, 0777);
	else if (stream == STDOUT_FILENO)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (fd);
}

void	process_pipe(char *cmd, char *envp[])
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) < 0)
		print_error("pipex", 1);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		if (dup2(pipe_fd[WRITE], STDOUT_FILENO) < 0)
			print_error("pipex", 1);
		execute_cmd(cmd, envp);
		close(pipe_fd[WRITE]);
		exit(0);
	}
	else
	{
		close(pipe_fd[WRITE]);
		if (dup2(pipe_fd[READ], STDIN_FILENO) < 0)
			print_error("pipex", 1);
		close(pipe_fd[READ]);
	}
}
