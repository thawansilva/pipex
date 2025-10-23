/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thawan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:29:38 by thawan            #+#    #+#             */
/*   Updated: 2025/10/23 17:05:02 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *filename, int stream)
{
	int	fd;

	fd = -1;
	if (stream == READ)
		fd = open(filename, O_RDONLY, 0777);
	else if (stream == WRITE)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (stream == APPEND)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
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

void	insert_input(int *pipe_fd, char *limiter)
{
	char	*str;

	close(pipe_fd[READ]);
	while (1)
	{
		ft_putstr_fd("\033[1m pipe heredoc> \033[0m", 1);
		str = get_next_line(0);
		if (str == NULL)
			break ;
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
		{
			free(str);
			break ;
		}
		write(pipe_fd[WRITE], str, ft_strlen(str));
		free(str);
	}
	close(pipe_fd[WRITE]);
}

void	handle_here_doc(int argc, char *limiter)
{
	int		pipe_fd[2];
	int		pid;

	if (argc < 6)
	{
		ft_putendl_fd("Not enough arguments", 2);
		exit(0);
	}
	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		print_error("pipex", 1);
	else if (pid == 0)
	{
		insert_input(pipe_fd, limiter);
		exit(0);
	}
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) < 0)
		print_error("pipex", 1);
	close(pipe_fd[READ]);
	wait(NULL);
}

void	handle_multiple_pipes(char **argv, int files[2])
{
	files[READ] = open_file(argv[1], READ);
	if (files[READ] < 0)
		print_error("pipex", 1);
	if (dup2(files[READ], STDIN_FILENO) < 0)
		print_error("pipex", 1);
	close(files[READ]);
	files[WRITE] = open_file(argv[2], WRITE);
}
